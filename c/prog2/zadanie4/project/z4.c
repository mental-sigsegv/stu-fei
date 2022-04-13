#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "config.h"
// #include "functions.c"


static int fw_NAME=0, fw_ITEM=0, fw_LAT=0, fw_LON=0, fi_NAME=0, fi_PRICE=0, FORMAT=0; 
static char *fw_NAMEs, *fw_ITEMs, *fi_NAMEs;
static char *fw_LONf, *fw_LATf;
static int validWarehouse[DB_NUM];

int isNumeric(char* str) {
    while (*str != '\0') {
        if (!((('0' <= *str) && (*str <= '9')) || (*str == '.')))  {
            return 0;
        }
        str++;
    }
    return 1;
}

void default_print(){
    int count=1;
    for (int i = 0; i < DB_NUM; i++) {
        if (validWarehouse[i] == 1) {
            for (int j=0; j < db[i].n; j++) {
                if (fi_NAME == 1) {
                    if (strcmp(fi_NAMEs, db[i].items[j].name) == 0) {
                        printf("%d. %s %d : %s %.3lf %.3lf %d\n", count, db[i].items[j].name, db[i].items[j].price, db[i].name, db[i].gps.lat, db[i].gps.lon, db[i].n);
                        count++;
                    }
                } else {
                    printf("%d. %s %d : %s %.3lf %.3lf %d\n", count, db[i].items[j].name, db[i].items[j].price, db[i].name, db[i].gps.lat, db[i].gps.lon, db[i].n);
                    count++;
                }
                
            }
        }
    }
}

void formated_print() {
    int count;
    for (int i = 0; i < DB_NUM; i++) {
        if (validWarehouse[i] == 1) {
            count = 1;
            printf("%s %.3lf %.3lf %d :\n", db[i].name, db[i].gps.lat, db[i].gps.lon, db[i].n);
            for (int j=0; j < db[i].n; j++) {
                printf("%d. %s %d\n", count, db[i].items[j].name, db[i].items[j].price);
                count++;
            }
        }
    }
}

void fw_byName(char* name) {
    for (int i = 0; i < DB_NUM; i++) {
        if (strcmp(name, db[i].name) != 0) {
            validWarehouse[i] = 0;
        }
    }
}

void fw_byItem(char* name) {
    for (int i = 0; i < DB_NUM; i++) {
        validWarehouse[i] = 0;
        for (int j=0; j < db[i].n; j++) {
            if (strcmp(name, db[i].items[j].name) == 0) {
                validWarehouse[i] = 1;
                break;
            }
        }
    }
}

void fw_byGps(GPS myPos) {
    double minDistance = distance(myPos, db[0].gps);
    double currentDistance;
    int warehouseIndex=0;


    for (int i = 0; i < DB_NUM; i++) {
        validWarehouse[i] = 0;
        currentDistance = distance(myPos, db[i].gps);
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            warehouseIndex = i;
        }
    }
    validWarehouse[warehouseIndex] = 1;
}

int main(int argc, char *argv[]){
    int opt;
      // Valid warehouse for print
	char* optstring = ":w:i:n:e:t:p:W";
    GPS GPSposition;

    for (int i = 0; i < DB_NUM; i++) {
        validWarehouse[i] = 1;
    }


    while ((opt = getopt(argc, argv, optstring)) != -1) {
        
        switch (opt) {
            case 'w':
                fw_NAME = 1;
                fw_NAMEs = optarg;
                break;
            case 'i':
                fw_ITEM = 1;
                fw_ITEMs = optarg;
                break;
            case 'n':
                fw_LAT = 1;
                fw_LATf = optarg;
                break;
            case 'e':
                fw_LON = 1;
                fw_LONf = optarg;
                break;
            case 't':
            	fi_NAME = 1;
                fi_NAMEs = optarg;
            	break;
            case 'p':
            	fi_PRICE = 1;
                break;
            case 'W':
                FORMAT = 1;
                break;
            case ':':
                printf("return 2, missing argument");  // TODO REMOVE
                return 2;
            default: /* '?' alebo ':' */   
                // printf("%d ", opt);
                // for (int l = 1; l <= (int)strlen(optstring); l=l+2) {
                //     // printf("%d ", optstring[l]);
                //     if (optstring[l] ==  optopt) {
                //         printf("req. arg");
                //         return 2;
                //     }
                // }
                printf("return 1, wrong switch");  // TODO REMOVE
                return 1;
        }
    }

    // Return 3, one of the flags are 0
    if ((fw_LON || fw_LAT) && (fw_LON != fw_LAT)) {
            printf("return 3, missing -n / -e");  // TODO REMOVE
            return 3;
    } 
    
    // Return 4  // ? optimize
    if ((fw_LON == 1) && (fw_LAT == 1)) {
        if (isNumeric(fw_LONf)) {
            GPSposition.lon = atof(fw_LONf);
        } else {
            printf("return 4");  // TODO remove
            return 4;
        }
        if ((GPSposition.lon < LON_MIN) || (GPSposition.lon > LON_MAX)) {
            printf("return 4, lon wrong interval");  // TODO remove
            return 4;
        }

        if (isNumeric(fw_LATf)) {
            GPSposition.lat = atof(fw_LATf);
        } else {
            printf("return 4");  // TODO remove
            return 4;
        }
        if ((GPSposition.lat < LAT_MIN) || (GPSposition.lat > LAT_MAX)) {
            printf("return 4, lat wrong interval");  // TODO remove
            return 4;
        }
    }

    // Filtering
    if (fw_NAME == 1) {
        fw_byName(fw_NAMEs);
    } else if (fw_ITEM == 1) {
        fw_byItem(fw_ITEMs);
    } else if ((fw_LON == 1) && (fw_LAT == 1)) {
        fw_byGps(GPSposition);
    }

    // TODO REMOVE
    // printf("\n");
    // for (int i = 0; i < DB_NUM; i++) {
    //     printf("%d ", validWarehouse[i]);
    // }

    // Print
    if (FORMAT == 1) {
        formated_print();
    } else {
        default_print();
    }
    
    
    return 0;
}