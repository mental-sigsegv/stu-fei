#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "config.h"
// #include "functions.c"


static int fw_NAME=0, fw_ITEM=0, fw_LAT=0, fw_LON=0, fi_NAME=0, fi_PRICE=0, FORMAT=0; 
static char *LONG, *LAT;

int isNumeric(char* str) {
    while (*str != '\0') {
        if (!((('0' <= *str) && (*str <= '9')) || (*str == '.')))  {
            return 0;
        }
        str++;
    }
    return 1;
}

int main(int argc, char *argv[]){
    int opt;
	char* optstring = ":w:i:n:e:t:p:W";
    GPS GPSposition;

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        
        switch (opt) {
            case 'w':
                fw_NAME = 1;
                break;
            case 'i':
                fw_ITEM = 1;
                break;
            case 'n':
                fw_LAT = 1;
                LAT = optarg;
                break;
            case 'e':
                fw_LON = 1;
                LONG = optarg;
                break;
            case 't':
            	fi_NAME = 1;
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
        if (isNumeric(LONG)) {
            GPSposition.lon = atof(LONG);
        } else {
            printf("return 4");  // TODO remove
            return 4;
        }
        if ((GPSposition.lon < LON_MIN) || (GPSposition.lon > LON_MAX)) {
            printf("return 4, lon wrong interval");  // TODO remove
            return 4;
        }

        if (isNumeric(LAT)) {
            GPSposition.lat = atof(LAT);
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

    // Print

    printf("%s", db[0].name);
    
    return 0;
}