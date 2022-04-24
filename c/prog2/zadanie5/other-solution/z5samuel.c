#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "config.h"

int main(int argc, char *argv[]) {

    int opt, w=0, n=0, e=0, a=0, d=0;
    double G1, G2;
    char* optstring = ":w:n:e:ad",*pEnd, *pEnd1;
    char povinny_sklady[50];
    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'w':
                strcpy(povinny_sklady, optarg);
                w++;
                break;
            case 'n':
                G1 = strtod(optarg, &pEnd);
                n++;
                break;
            case 'e':
                G2 = strtod(optarg, &pEnd1);
                e++;
                break;
            case 'a':
                a++;
                break;
            case 'd':
                d++;
                break;
        }
    }

    FILE* fp;
    fp = fopen(WAREHOUSE_DB_FILE, "r");

    char str[100];
    double GPS_lat, GPS_lon;
    int capacity,s=0;
    char tovar[MAX_NAME + 1];
    char cena[MAX_NAME + 1];

    int pocet_skladov=0, pocet_tovarov=0;
    char cesta[MAX_NAME+7+4] ="";
//Zistenie počtu skladov v databáze
    while(fgets(str, 100, fp)) {
        pocet_skladov++;
    }
    WAREHOUSE *pole = malloc(pocet_skladov *sizeof(WAREHOUSE) );
//Vytvorenie dynamického poľa pre jednotlívé sklady
    fclose(fp);
    fp = fopen(WAREHOUSE_DB_FILE, "r");
//Načítanie údajov jednotlivých skladov
    while(fscanf(fp,"%s %lf %lf %d", str, &GPS_lat, &GPS_lon, &capacity)!= EOF) {
        strcpy(pole[s].name, str);
        pole[s].gps.lat=GPS_lat;
        pole[s].gps.lon=GPS_lon;
        pole[s].capacity=capacity;
        s++;
    }
//VÝPIS SKLADOV
    for(int i=0; i<pocet_skladov; i++){
        printf("%s %.3lf %.3lf %d\n", pole[i].name, pole[i].gps.lat, pole[i].gps.lon, pole[i].capacity);
    }
    fclose(fp);

//Nastavenie dlzky pola pri tovaroch
    for(int i=0; i< pocet_skladov; i++){
        pocet_tovarov=0;
        strcpy(cesta, "");
        strcat(cesta,ITEMS_FOLDER);
        strcat(cesta, PATH_SEPARATOR);
        strcat(cesta,pole[i].name);
        strcat(cesta, ".txt");
        fp = fopen(cesta,"r");
        if(fp != NULL) {
            while (fgets(str, 100, fp)) {
                pocet_tovarov++;
            }
            pole[i].n=pocet_tovarov;
            if (pole[i].n != 0) {
                pole[i].items = malloc(pole[i].n*sizeof(ITEM));
            }
            fclose(fp);
        }
        else {
            pole[i].n=pocet_tovarov;
        }
    }

//Nacitanie tovarov a cien
    for(int i=0; i<pocet_skladov; i++) {
        strcpy(cesta, "");
        strcat(cesta, ITEMS_FOLDER);
        strcat(cesta, PATH_SEPARATOR);
        strcat(cesta, pole[i].name);
        strcat(cesta, ".txt");
        s = 0;
        fp = fopen(cesta, "r");
        if(fp != NULL) {
            while (fscanf(fp, "%s %s", tovar, cena) == 2) {
                int x=0;
                int y=0;
                for(int j=0; j< (int)strlen(tovar); j++){
                    if(isdigit(tovar[j])!=0){
                        x++;
                    }
                }
                if(x!=0){
                    pole[i].n=-1;
                    break;
                }
                for(int j=0; j< (int)strlen(cena); j++){
                    if(isalpha(cena[j])!=0){
                        y++;
                    }
                }
                if(y!=0){
                    pole[i].n=-1;
                    break;
                }
                strcpy(pole[i].items[s].name, tovar);
                pole[i].items[s].price = atoi(cena);
                s++;
            }
            fclose(fp);
        }

        if(s!=pole[i].n){
            pole[i].n=-1;
        }

    }

//Usporiadanie vsetkych tovarov podla abecedy
    char pomocny[MAX_NAME];
    int pomocny_ceny;

//Prepinac w- PODLA NAZVU SKLADU
    if(w!=0) {
        for(int i=0; i<pocet_skladov; i++){
            if(strcmp(pole[i].name, povinny_sklady)==0){
                if(pole[i].n==0){
                    fprintf(stderr, "FILE_ERROR %s.txt\n", pole[i].name);
                }
                else if(pole[i].n>pole[i].capacity){
                    fprintf(stderr, "CAPACITY_ERROR %s.txt\n", pole[i].name);
                }
                else if (pole[i].n==-1){
                    fprintf(stderr, "FORMAT_ERROR %s.txt\n", pole[i].name);
                }
                else {
                    if (a == 0 && d == 0) {
                        for (int k = 0; k < pole[i].n; k++) {
                            for (int j = 0; j < pole[i].n - 1 - k; j++) {
                                if (strcmp(pole[i].items[j].name, pole[i].items[j + 1].name)>0) {
                                    //swap array[j] and array[j+1]
                                    strcpy(pomocny, pole[i].items[j].name);
                                    pomocny_ceny = pole[i].items[j].price;
                                    strcpy(pole[i].items[j].name, pole[i].items[j + 1].name);
                                    pole[i].items[j].price = pole[i].items[j + 1].price;
                                    strcpy(pole[i].items[j + 1].name, pomocny);
                                    pole[i].items[j + 1].price = pomocny_ceny;
                                }
                            }
                        }
                        printf("%s %.3lf %.3lf %d :\n", pole[i].name, pole[i].gps.lat, pole[i].gps.lon,
                               pole[i].capacity);
                        for (int j = 0; j < pole[i].n; j++) {
                            printf("%d. %s %d\n", j + 1, pole[i].items[j].name, pole[i].items[j].price);
                        }
                    }
                    if (a == 1) {
                        for (int k = 0; k < pole[i].n; k++) {
                            for (int j = 0; j < pole[i].n - 1 - k; j++) {
                                if (pole[i].items[j].price > pole[i].items[j + 1].price) {
                                    //swap array[j] and array[j+1]
                                    strcpy(pomocny, pole[i].items[j].name);
                                    pomocny_ceny = pole[i].items[j].price;
                                    strcpy(pole[i].items[j].name, pole[i].items[j + 1].name);
                                    pole[i].items[j].price = pole[i].items[j + 1].price;
                                    strcpy(pole[i].items[j + 1].name, pomocny);
                                    pole[i].items[j + 1].price = pomocny_ceny;
                                }
                            }
                        }
                        printf("%s %.3lf %.3lf %d :\n", pole[i].name, pole[i].gps.lat, pole[i].gps.lon,
                               pole[i].capacity);
                        for (int j = 0; j < pole[i].n; j++) {
                            printf("%d. %s %d\n", j + 1, pole[i].items[j].name, pole[i].items[j].price);
                        }
                    }

                    if (d == 1) {
                        for (int k = 0; k < pole[i].n; k++) {
                            for (int j = 0; j < pole[i].n - 1 - k; j++) {
                                if (pole[i].items[j].price < pole[i].items[j + 1].price) {
                                    //swap array[j] and array[j+1]
                                    strcpy(pomocny, pole[i].items[j].name);
                                    pomocny_ceny = pole[i].items[j].price;
                                    strcpy(pole[i].items[j].name, pole[i].items[j + 1].name);
                                    pole[i].items[j].price = pole[i].items[j + 1].price;
                                    strcpy(pole[i].items[j + 1].name, pomocny);
                                    pole[i].items[j + 1].price = pomocny_ceny;
                                }
                            }
                        }
                        printf("%s %.3lf %.3lf %d :\n", pole[i].name, pole[i].gps.lat, pole[i].gps.lon,
                               pole[i].capacity);
                        for (int j = 0; j < pole[i].n; j++) {
                            printf("%d. %s %d\n", j + 1, pole[i].items[j].name, pole[i].items[j].price);
                        }
                    }
                }
            }
        }
    }

//PREPINADE n,e - NAJKRATSIA VZDIALENOST
    double vzdialenost;
    if(n!=0 && e!=0){
        double najkratsia_vzdialenost=1000000000;
        int sklad_cislo;
        GPS gps1 = {G1,G2};
        for(int i=0; i<pocet_skladov; i++) {
            vzdialenost = distance(pole[i].gps, gps1);
            if(vzdialenost<najkratsia_vzdialenost){
                najkratsia_vzdialenost=vzdialenost;
                sklad_cislo=i;
            }
        }
        if(pole[sklad_cislo].n==0){
            fprintf(stderr, "FILE_ERROR %s.txt\n", pole[sklad_cislo].name);
        }
        else if(pole[sklad_cislo].n>pole[sklad_cislo].capacity){
            fprintf(stderr, "CAPACITY_ERROR %s.txt\n", pole[sklad_cislo].name);
        }
        else if (pole[sklad_cislo].n==-1){
            fprintf(stderr, "FORMAT_ERROR %s.txt\n", pole[sklad_cislo].name);
        }
        else {
            if (a == 0 && d == 0) {
                for (int k = 0; k < pole[sklad_cislo].n; k++) {
                    for (int j = 0; j < pole[sklad_cislo].n - 1 - k; j++) {
                        if (strcmp(pole[sklad_cislo].items[j].name, pole[sklad_cislo].items[j + 1].name)>0) {
                            //swap array[j] and array[j+1]
                            strcpy(pomocny, pole[sklad_cislo].items[j].name);
                            pomocny_ceny = pole[sklad_cislo].items[j].price;
                            strcpy(pole[sklad_cislo].items[j].name, pole[sklad_cislo].items[j + 1].name);
                            pole[sklad_cislo].items[j].price = pole[sklad_cislo].items[j + 1].price;
                            strcpy(pole[sklad_cislo].items[j + 1].name, pomocny);
                            pole[sklad_cislo].items[j + 1].price = pomocny_ceny;
                        }
                    }
                }
                printf("%s %.3lf %.3lf %d :\n", pole[sklad_cislo].name, pole[sklad_cislo].gps.lat,
                       pole[sklad_cislo].gps.lon, pole[sklad_cislo].capacity);
                for (int i = 0; i < pole[sklad_cislo].n; i++) {
                    printf("%d. %s %d\n", i + 1, pole[sklad_cislo].items[i].name, pole[sklad_cislo].items[i].price);
                }
            }
            if (a == 1) {
                for (int k = 0; k < pole[sklad_cislo].n; k++) {
                    for (int j = 0; j < pole[sklad_cislo].n - 1 - k; j++) {
                        if (pole[sklad_cislo].items[j].price > pole[sklad_cislo].items[j + 1].price) {
                            //swap array[j] and array[j+1]
                            strcpy(pomocny, pole[sklad_cislo].items[j].name);
                            pomocny_ceny = pole[sklad_cislo].items[j].price;
                            strcpy(pole[sklad_cislo].items[j].name, pole[sklad_cislo].items[j + 1].name);
                            pole[sklad_cislo].items[j].price = pole[sklad_cislo].items[j + 1].price;
                            strcpy(pole[sklad_cislo].items[j + 1].name, pomocny);
                            pole[sklad_cislo].items[j + 1].price = pomocny_ceny;
                        }
                    }
                }
                printf("%s %.3lf %.3lf %d :\n", pole[sklad_cislo].name, pole[sklad_cislo].gps.lat,
                       pole[sklad_cislo].gps.lon, pole[sklad_cislo].capacity);
                for (int j = 0; j < pole[sklad_cislo].n; j++) {
                    printf("%d. %s %d\n", j + 1, pole[sklad_cislo].items[j].name, pole[sklad_cislo].items[j].price);
                }
            }
            if(d==1){
                for (int k = 0; k < pole[sklad_cislo].n; k++) {
                    for (int j = 0; j < pole[sklad_cislo].n - 1 - k; j++) {
                        if (pole[sklad_cislo].items[j].price < pole[sklad_cislo].items[j + 1].price) {
                            //swap array[j] and array[j+1]
                            strcpy(pomocny, pole[sklad_cislo].items[j].name);
                            pomocny_ceny=pole[sklad_cislo].items[j].price;
                            strcpy(pole[sklad_cislo].items[j].name, pole[sklad_cislo].items[j + 1].name);
                            pole[sklad_cislo].items[j].price=pole[sklad_cislo].items[j + 1].price;
                            strcpy(pole[sklad_cislo].items[j + 1].name, pomocny);
                            pole[sklad_cislo].items[j + 1].price=pomocny_ceny;
                        }
                    }
                }
                printf("%s %.3lf %.3lf %d :\n", pole[sklad_cislo].name, pole[sklad_cislo].gps.lat, pole[sklad_cislo].gps.lon, pole[sklad_cislo].capacity);
                for (int j = 0; j < pole[sklad_cislo].n; j++) {
                    printf("%d. %s %d\n", j + 1, pole[sklad_cislo].items[j].name, pole[sklad_cislo].items[j].price);
                }
            }
        }
    }

//AK NIEJE ZADANI ZIADEN PREPINAC SKLADOV
    if(w==0 && n==0 && e==0){
        for(int i=0; i<pocet_skladov; i++){
            if(pole[i].n==0){
                fprintf(stderr, "FILE_ERROR %s.txt\n", pole[i].name);
            }
            else if(pole[i].n>pole[i].capacity){
                fprintf(stderr, "CAPACITY_ERROR %s.txt\n", pole[i].name);
            }
            else if (pole[i].n==-1){
                fprintf(stderr, "FORMAT_ERROR %s.txt\n", pole[i].name);
            }
            else{
                if(a==0 && d==0) {
                    for (int k = 0; k < pole[i].n; k++) {
                        for (int j = 0; j < pole[i].n - 1 - k; j++) {
                            if (strcmp(pole[i].items[j].name, pole[i].items[j + 1].name)>0) {
                                strcpy(pomocny, pole[i].items[j].name);
                                pomocny_ceny = pole[i].items[j].price;
                                strcpy(pole[i].items[j].name, pole[i].items[j + 1].name);
                                pole[i].items[j].price = pole[i].items[j + 1].price;
                                strcpy(pole[i].items[j + 1].name, pomocny);
                                pole[i].items[j + 1].price = pomocny_ceny;
                            }
                        }
                    }
                    printf("%s %.3lf %.3lf %d :\n", pole[i].name, pole[i].gps.lat, pole[i].gps.lon, pole[i].capacity);
                    for (int j = 0; j < pole[i].n; j++) {
                        printf("%d. %s %d\n", j + 1, pole[i].items[j].name, pole[i].items[j].price);
                    }
                }
                if (a == 1) {
                    for (int k = 0; k < pole[i].n; k++) {
                        for (int j = 0; j < pole[i].n - 1 - k; j++) {
                            if (pole[i].items[j].price > pole[i].items[j + 1].price) {
                                strcpy(pomocny, pole[i].items[j].name);
                                pomocny_ceny = pole[i].items[j].price;
                                strcpy(pole[i].items[j].name, pole[i].items[j + 1].name);
                                pole[i].items[j].price = pole[i].items[j + 1].price;
                                strcpy(pole[i].items[j + 1].name, pomocny);
                                pole[i].items[j + 1].price = pomocny_ceny;
                            }
                        }
                    }
                    printf("%s %.3lf %.3lf %d :\n", pole[i].name, pole[i].gps.lat, pole[i].gps.lon,
                           pole[i].capacity);
                    for (int j = 0; j < pole[i].n; j++) {
                        printf("%d. %s %d\n", j + 1, pole[i].items[j].name, pole[i].items[j].price);
                    }
                }
                if (d == 1) {
                    for (int k = 0; k < pole[i].n; k++) {
                        for (int j = 0; j < pole[i].n - 1 - k; j++) {
                            if (pole[i].items[j].price < pole[i].items[j + 1].price) {
                                strcpy(pomocny, pole[i].items[j].name);
                                pomocny_ceny = pole[i].items[j].price;
                                strcpy(pole[i].items[j].name, pole[i].items[j + 1].name);
                                pole[i].items[j].price = pole[i].items[j + 1].price;
                                strcpy(pole[i].items[j + 1].name, pomocny);
                                pole[i].items[j + 1].price = pomocny_ceny;
                            }
                        }
                    }
                    printf("%s %.3lf %.3lf %d :\n", pole[i].name, pole[i].gps.lat, pole[i].gps.lon,
                           pole[i].capacity);
                    for (int j = 0; j < pole[i].n; j++) {
                        printf("%d. %s %d\n", j + 1, pole[i].items[j].name, pole[i].items[j].price);
                    }
                }
            }
        }
    }

    for (int i = 0; i < pocet_skladov; i++) {
        if (pole[i].n != 0) {
            free(pole[i].items);
        }
    }

    free(pole);
    return 0;
}