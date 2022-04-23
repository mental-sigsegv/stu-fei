#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "config.h"

static int fw_NAME=0, fw_LAT=0, fw_LON=0, o_ASC=0, o_DES=0, DB_NUM=0; 
static char *fw_NAMEs;
static char *fw_LONf, *fw_LATf;

static char items_path[MAX_NAME];

void get_item_path(WAREHOUSE* wh) {
    strcpy(items_path, ITEMS_FOLDER);
    strcat(items_path, PATH_SEPARATOR);
    strcat(items_path, wh->name);
    strcat(items_path, ".txt");
}

int get_num_of_lines(char* file) {
    FILE *fp;
    int count=0;

    fp=fopen(file, "r");
    while (EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp,"%*c"))) {
        ++count;
    }
    fclose(fp);
    return count;
}

int valid_capacity(WAREHOUSE* wh) {
    int numOfItems=0;
    get_item_path(wh);
    numOfItems = get_num_of_lines(items_path);

    if (numOfItems > wh->capacity) {
        return 0;
    }
    wh->n = numOfItems;
    return 1;
}

int valid_txt(WAREHOUSE* wh) {
    FILE *w_items;
    get_item_path(wh);
    w_items=fopen(items_path, "r");
    if (w_items == NULL) {
        return 0;
    }
    fclose(w_items);
    return 1;
}

int valid_format(WAREHOUSE* wh) {
    FILE *w_items;
    get_item_path(wh);
    w_items=fopen(items_path, "r");
    char itemName[MAX_NAME];
    int itemPrice;
    for (int i = 0; i < wh->n; i++) {
        if((fscanf(w_items, "%s %d\n", itemName, &itemPrice))!=2) {
            fclose(w_items);
            return 0;
        }
    }
    fclose(w_items);
    return 1;
}

void allocate_items(WAREHOUSE* wh) {
    FILE *w_items;
    get_item_path(wh);
    w_items=fopen(items_path, "r");
    wh->items = (ITEM*)malloc(sizeof(ITEM)*wh->n);
    for (int i = 0; i < wh->n; i++) {
        fscanf(w_items, "%s %d", wh->items[i].name, &wh->items[i].price);
    }
    fclose(w_items);
}

void filter_name(WAREHOUSE **wh, short list[], char* name) {
    for (int i = 0; i < DB_NUM; i++) {
        if (list[i] == 1) {
            if (strcmp(wh[i]->name, name) != 0) {
                list[i] = 0;
            }
        }
    }
}

void sort_by_name(WAREHOUSE* wh) {
    ITEM temp;
    int change=0;

    while (1) {
        change = 0;
        for (int i = 0; i < (wh->n)-1; i++) {
            if (strcmp(wh->items[i].name, wh->items[i+1].name) > 0) {
                temp = wh->items[i];
                wh->items[i] = wh->items[i+1];
                wh->items[i+1] = temp;
                change++;
            }
        }

        if (change == 0) {
            break;
        }
    }
}

void sort_by_asc(WAREHOUSE* wh) {
    ITEM temp;
    int change=0;
    while (1) {
        change = 0;
        for (int i = 0; i < (wh->n)-1; i++) {
            if (wh->items[i].price > wh->items[i+1].price) {
                temp = wh->items[i];
                wh->items[i] = wh->items[i+1];
                wh->items[i+1] = temp;
                change++;
            }
        }

        if (change == 0) {
            break;
        }
    }
}

void sort_by_des(WAREHOUSE* wh) {
    ITEM temp;
    int change=0;
    while (1) {
        change = 0;
        for (int i = 0; i < (wh->n)-1; i++) {
            if (wh->items[i].price < wh->items[i+1].price) {
                temp = wh->items[i];
                wh->items[i] = wh->items[i+1];
                wh->items[i+1] = temp;
                change++;
            }
        }

        if (change == 0) {
            break;
        }
    }
}

void filter_gps(WAREHOUSE **wh, short list[], GPS myPos) {
    double minDistance = distance(myPos, wh[0]->gps);
    double currentDistance;
    int warehouseIndex=0;

    for (int i = 0; i < DB_NUM; i++) {
        list[i] = 0;
        currentDistance = distance(myPos, wh[i]->gps);
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            warehouseIndex = i;
        }
    }
    list[warehouseIndex] = 1;
}

int main(int argc, char *argv[]){
    int opt;
	char* optstring = ":w:n:e:ad";

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'w':
                fw_NAME = 1;
                fw_NAMEs = optarg;
                break;
            case 'n':
                fw_LAT = 1;
                fw_LATf = optarg;
                break;
            case 'e':
                fw_LON = 1;
                fw_LONf = optarg;
                break;
            case 'a':
                o_ASC = 1;
            	break;
            case 'd':
                o_DES = 1;
                break;
            case ':':
                return 2;
            default: 
                return 1;
        }
    }
     
    FILE *w_db;
    
    // Get number of warehouses
    DB_NUM = get_num_of_lines(WAREHOUSE_DB_FILE);

    // Variables
    WAREHOUSE *WAREHOUSES[DB_NUM];
    short validWarehouse[DB_NUM]; 

    // Set warehouses as available to be printed
    for (int i=0; i< DB_NUM; i++) {
        validWarehouse[i] = 1;
    }

    // Store warehouses (DB_NUM) struck into array
    w_db=fopen(WAREHOUSE_DB_FILE, "r");
    int k=0;
    while (1) {
        WAREHOUSE *wh = (WAREHOUSE*)malloc(sizeof(WAREHOUSE));
        if (fscanf(w_db, "%s %lf %lf %d\n", wh->name, &(wh->gps.lat), &(wh->gps.lon), &(wh->capacity)) == EOF) {
            free(wh);
            break;
        }
        WAREHOUSES[k] = wh;
        k++;
    }
    
    // Filter warehouses
    if (fw_NAME == 1) {
        filter_name(WAREHOUSES, validWarehouse, fw_NAMEs);
    } else if ((fw_LON == 1) && (fw_LAT == 1)) {
        GPS gps_data;
        gps_data.lat = atof(fw_LATf);
        gps_data.lon = atof(fw_LONf);
        filter_gps(WAREHOUSES, validWarehouse, gps_data);
    }

    // Print warehouses, stderr, allocate items for wh
    for (int i = 0; i < DB_NUM; i++) {
        WAREHOUSE *wh = WAREHOUSES[i];
        fprintf(stdout, "%s %.3lf %.3lf %d\n", wh->name, wh->gps.lat, wh->gps.lon, wh->capacity);
        if (validWarehouse[i] == 1) {
            if (valid_txt(wh) == 0) {  // ! taking too much memory?
                validWarehouse[i] = 0;
                fprintf(stderr, "FILE_ERROR %s.txt\n", wh->name);
            } else if (valid_capacity(wh) == 0) {  // ! taking too much memory?
                validWarehouse[i] = 0;
                fprintf(stderr, "CAPACITY_ERROR %s.txt\n", wh->name);
            } else if (valid_format(wh) == 0) {  // ! taking too much memory?
                validWarehouse[i] = 0;
                fprintf(stderr, "FORMAT_ERROR %s.txt\n", wh->name);
            } else {
                allocate_items(wh);
            }
        }
    }

    // Print items
    WAREHOUSE *wh;
    for (int i = 0; i < DB_NUM; i++) {
        if (validWarehouse[i] == 1) {
            wh = WAREHOUSES[i];
            printf("%s %.3lf %.3lf %d :\n", wh->name, wh->gps.lat, wh->gps.lon, wh->capacity);
            
            if (o_ASC == 1) {
                sort_by_asc(wh);
            } else if (o_DES == 1) {
                sort_by_des(wh);
            } else {
                sort_by_name(wh);
            }
            
            for (int j=0; j < wh->n; j++) {
                printf("%d. %s %d\n", j+1, wh->items[j].name, wh->items[j].price);
            }
           
        }
    }


    // Free malloc warehouses and items
    for (int i = 0; i < DB_NUM; i++) {
        if (validWarehouse[i] == 1) {
            free(WAREHOUSES[i]->items);
        }
        free(WAREHOUSES[i]);
    }
    
    fclose(w_db);
    return 0;
}