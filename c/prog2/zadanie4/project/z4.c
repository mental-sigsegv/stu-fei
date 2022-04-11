#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"


static int fw_NAME=0, fw_ITEM=0, fw_LAT=0, fw_LON=0, fi_NAME=0, fi_PRICE=0, FORMAT=0; 

int main(int argc, char *argv[]){
    int opt;
	char* optstring = ":w:i:n:e:t:p:W";
    // char* 

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
                break;
            case 'e':
                fw_LON = 1;
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
            default: /* '?' alebo ':' */   
                // printf("%d ", opt);
                for (int l = 1; l <= (int)strlen(optstring); l=l+2) {
                    // printf("%d ", optstring[l]);
                    if (optstring[l] ==  optopt) {
                        printf("req. arg");
                        return 2;
                    }
                }
                printf("wrong switch");
                return 1;
        }
    }

    if ((fw_LON || fw_LAT) && (fw_LON != fw_LAT)) {
            printf("return 3");
            return 3;
    } else if ()

    return 0;
}