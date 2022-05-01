#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "config.h"

int w, n, e, a, d;
char* optargsavename;
char* optargsavewarehouseitem;
char* optargsavewarehouselat;
char* optargsavewarehouselon;
char* optargsaveitem;
char* optargsavemaxprice;
int optargsavemaxpriceint;
char* itemname;
int* itemprice;

int howmanylines (char* filename) {
    FILE *fp = fopen(filename,"r");

    char a;
    int count = 0;

    for (a = getc(fp); a != EOF; a = getc(fp)) {
        if (a == '\n') {
            count = count + 1;
        }
    }

    fclose(fp);
    return count;
}

void swap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swapname(char* xp, char* yp) {
    char temp[128];
    strcpy(temp, xp);
    strcpy(xp, yp);
    strcpy(yp, temp);

}

int get_size(const char* file_name)
{
    FILE *file = fopen(file_name, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

int getopt(int argc, char *const argv[], const char *optstring);

int main(int argc, char *argv[]){

	int opt;
	char* optstring = ":w:n:e:ad";

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'w':
                w = 1;
                optargsavename = optarg;
                break;
            case 'n':
                n = 1;
                optargsavewarehouselat = optarg;
            	break;
            case 'e':
                e = 1;
                optargsavewarehouselon = optarg;
                break;
            case 'a':
                a = 1;
                break;
            case 'd':
                d = 1;
                break;
            case ':':
                return 2;
            default: /* '?' alebo ':' */
                return 1;
        }
    }

    int DB_NUM = howmanylines(WAREHOUSE_DB_FILE);

    WAREHOUSE DB[DB_NUM];

    int validWH[DB_NUM];

    for (int i = 0; i < DB_NUM; i++) {
        validWH[i] = 1;
    }
    
    FILE *fp = fopen(WAREHOUSE_DB_FILE,"r");

    int i = 0;

    while (fscanf(fp, "%s %lf %lf %d\n", DB[i].name, &DB[i].gps.lat, &DB[i].gps.lon, &DB[i].capacity) != EOF) {
        DB[i].items = NULL;
        i++;
    }
    
    for (int i = 0; i < DB_NUM; i++) {
        fprintf(stdout, "%s %.3lf %.3lf %d\n", DB[i].name, DB[i].gps.lat, DB[i].gps.lon, DB[i].capacity);
    }
    
    if (w == 1) {
        for (int i = 0; i < DB_NUM; i++) {
            if (strcmp(DB[i].name, optargsavename) == 0) { 
                validWH[i] = 1;
            }
            else {
                validWH[i] = 0;
            }
        }
    }

    else if ((n == 1) && (e == 1)) {
        GPS fromuser;
        fromuser.lat = atof(optargsavewarehouselat);
        fromuser.lon = atof(optargsavewarehouselon);

        double closewarehouse = distance(fromuser, DB[0].gps);
        double distancefromuserandwarehouse = 0;

        for (int i = 0; i < DB_NUM; i++) {
            distancefromuserandwarehouse = distance(fromuser, DB[i].gps);
            if (closewarehouse >= distancefromuserandwarehouse) {
                closewarehouse = distancefromuserandwarehouse;
                for (int j = 0; j < DB_NUM; j++) {
                    validWH[j] = 0;
                }
                validWH[i] = 1;
            }
        }
    }

    // for (int i = 0; i < DB_NUM; i++) {
    //     fprintf(stdout, "%s %.3lf %.3lf %d :\n", DB[i].name, DB[i].gps.lat, DB[i].gps.lon, DB[i].capacity);
    // }

    char str[200];
    
    for (int i = 0; i < DB_NUM; i++) {
        sprintf(str, "%s%s%s.txt", ITEMS_FOLDER, PATH_SEPARATOR, DB[i].name);
        
        char iname[128];
        int iprice;
        
        if (validWH[i] == 1) {
            FILE *fi = fopen(str, "r");
            if(fi == NULL) {
                fprintf(stderr, "FILE_ERROR %s.txt\n", DB[i].name);
                validWH[i] = 0;
            }
            else {
                if (howmanylines(str) > DB[i].capacity) {
                    fprintf(stderr, "CAPACITY_ERROR %s.txt\n", DB[i].name);
                    validWH[i] = 0;
                }

                int formaterror = 0;
                
                for (int j = 0; j < howmanylines(str); j++) {
                    if ((fscanf(fi, "%s %d\n", &iname[128], &iprice)) != 2) {
                        formaterror++;
                    }
                }

                if (formaterror >= 1) {
                    fprintf(stderr, "FORMAT_ERROR %s.txt\n", DB[i].name);
                    validWH[i] = 0;
                }

                fclose(fi);
            }
        }

        if (validWH[i] == 1) {
            FILE *fo = fopen(str,"r");

            DB[i].n = howmanylines(str);
            DB[i].items = malloc(sizeof(ITEM)*DB[i].n); 
            // fprintf(stdout ,"%d\n", DB[i].n);

            int j = 0;

            while (!feof(fo)){
                fscanf(fo, "%s %d\n",DB[i].items[j].name, &DB[i].items[j].price);
                j++;
            }
            fclose(fo);
        }

    
    }

    if ( a == 1) {
        for (int i = 0; i < DB_NUM; i++) {
            if (validWH[i]) {
                for (int j = 0; j < DB[i].n - 1; j++) {
                    for (int k = 0; k < DB[i].n - j - 1; k++) {
                        if (DB[i].items[k].price > DB[i].items[k + 1].price) {
                            swap(&DB[i].items[k].price, &DB[i].items[k + 1].price);
                            swapname(DB[i].items[k].name, DB[i].items[k + 1].name);
                        }
                    }
                }
            }
        }
    }
    
    else if ( d == 1) {
        for (int i = 0; i < DB_NUM; i++) {
            if (validWH[i]) {
                for (int j = 0; j < DB[i].n - 1; j++) {
                    for (int k = 0; k < DB[i].n - j - 1; k++) {
                        if (DB[i].items[k].price < DB[i].items[k + 1].price) {
                            swap(&DB[i].items[k].price, &DB[i].items[k + 1].price);
                            swapname(DB[i].items[k].name, DB[i].items[k + 1].name);
                        }
                    }
                }
            }
        }
    }

    else {

        char tmp[128];

        for (int i = 0; i < DB_NUM; i++) {
            if (validWH[i] == 1) {
                for (int j = 0; j < DB[i].n - 1; j++) {
                    for (int k = 0; k < DB[i].n - j - 1; k++) {
                        if (strcmp(DB[i].items[k].name, DB[i].items[k+1].name) > 0) {
                            strcpy(tmp, DB[i].items[k].name);
                            swap(&DB[i].items[k].price, &DB[i].items[k+1].price);
                            strcpy(DB[i].items[k].name, DB[i].items[k+1].name);
                            strcpy(DB[i].items[k+1].name, tmp);
                        }
                    }
                }
            }
        }

    }

    int numberofitem = 1;

    for (int i = 0; i < DB_NUM; i++) {
        if (validWH[i] == 1) {
            fprintf(stdout, "%s %.3lf %.3lf %d :\n", DB[i].name, DB[i].gps.lat, DB[i].gps.lon, DB[i].capacity);
            numberofitem = 1;
            for (int j = 0; j < DB[i].n; j++) {
                fprintf(stdout,"%d. %s %d\n", numberofitem, DB[i].items[j].name, DB[i].items[j].price);
                numberofitem++;
            }
        }
    }

    for (int i = 0; i < DB_NUM; i++) {
        if (DB[i].items != NULL) {
            free(DB[i].items);
        }
    }

    fclose(fp);
	return 0;
}