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
// static int validWarehouse[DB_NUM], PRICE;

int main(int argc, char *argv[]){
    int opt;
	char* optstring = ":w:n:e:ad";
    // GPS GPSposition;

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
     
    FILE *fp, *w_db, *db_of_w;
    
    // Get number of warehouses
    fp=fopen(WAREHOUSE_DB_FILE, "r");
    int lines =0;
    while (EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp,"%*c"))) {
        ++DB_NUM;
    }
    fclose(fp);

    // Go through warehouse_db
    WAREHOUSE *WAREHOUSES[DB_NUM]; 
    w_db=fopen(WAREHOUSE_DB_FILE, "r");
    int k=0;
    while (1) {
        WAREHOUSE *wh = (WAREHOUSE*)malloc(sizeof(WAREHOUSE));
        if (fscanf(w_db, "%s %lf %lf %d\n", wh->name, &(wh->gps.lon), &(wh->gps.lat), &(wh->capacity)) == EOF) {
            free(wh);
            break;
        }
        WAREHOUSES[k] = wh;
        k++;
        // free(wh);
    }
    
    for (int i = 0; i < DB_NUM; i++) {
        WAREHOUSE *wh = WAREHOUSES[i];
        printf("%s %.3lf %.3lf %d\n", wh->name, wh->gps.lat, wh->gps.lat, wh->capacity);
        free(WAREHOUSES[i]);
    }
    
    fclose(w_db);
    return 0;
}