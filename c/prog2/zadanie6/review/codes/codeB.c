#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*  Zdravím ťa! Som rád že budeš hodnotiť môj program, len nejaké pokyny na začiatok:

   - Podstatné veci su v zdrojaku okomentované, tie ostatné slúžia väčšinou len na vzhľad alebo ako pomôcky
   - Ak ti nebude správne ukazovať farby, treba program spustiť napríklad cez "https://www.onlinegdb.com/"
   - Slová sú po anglicky
   - Prosím zadávaj len veľké písmená
   - Najprv si hru zahraj, až potom sa prescrolluj nižšie, pretože si prezradíš aké slová som do hry vybral
   - Prajem prijemnú zábavu a úspešný zvyšok semestra :)  */


void reset() {                    // Inicializacia farieb
    printf("\033[0m");
}

void red() {
    printf("\033[31m");
}

void green() {
    printf("\033[32m");
}

void yellow() {
    printf("\033[33m");
}


int main() {

    srand(time(NULL));

    char slova[10][5]={ "PLANE", "ADULT", "CRAZY", "BEACH", "DANCE", "HORSE", "NIGHT", "PRICE", "WATCH", "DRINK" };     // Databaza slov
    char pokusy[6][5], pokus[5], slovo[5];
    int x = rand() % 10, y=0, z=0, z1=0, pismena[26], pismeno=0;             // funkcia rand na nahodne vybratie slova


    for(int i=0; i<6; i++){                     // Nulovanie poli
        for(int j=0; j<5; j++){
            pokusy[i][j] = 0;
        }
    }
    for(int i=0; i<26; i++) pismena[i] = 0;


    for(int i=0; i<6; i++){              // Cyklus reprezentujúci počet pokusov (koľko krát sa vypíše tabuľka)

        for(int j=0; j<50; j++) printf("-");

        printf("\n Zadaj slovo:");
        scanf("%s", pokus);
        for(int j=0; j<5; j++) pokusy[i][j] = pokus[j];     // Zapísanie aktualneho pokusu do pola vsetkych pokusov

        for(int j=0; j<50; j++) printf("-");
        printf("\n");

        for(int j=1; j<=13; j++){         // Vnútorný cyklus na tvorbu a výpis tabuľky

            for(int k=0; k<13; k++) printf(" ");

            if(j % 2 == 0){             // Každý druhý riadok tabuľky (do ktoreho sa zapisuju pismena)
                z = 0;
                for(int k=0; k<6; k++){             // 6 = Pocet policok na zapisanie pismen (+1 ukoncovacie)

                    pismeno = (int)pokusy[j/2 - 1][k] - 65;

                    if(k == 5){
                        printf("|");
                        break;
                    }
                    printf("| ");

                    y = 0;
                    for(int l=0; l<5; l++){                  // Ak sa nejake pismeno pokusu nachadza v hladanom slove
                        if(pokusy[j/2 - 1][k] == slova[x][l]) y=1;
                    }

                    if (pokusy[j/2 - 1][k] == slova[x][k]){       // Pismeno sa nachadza na spravnom mieste - green
                        green();
                        z++;
                        pismena[pismeno] = 1;
                    }
                    else if(y == 1){                  // Pismeno sa nachadza v slove ale je na zlej pozicii - yellow
                        yellow();
                        pismena[pismeno] = 1;
                    }
                    else{                           // Pismeno sa v slove nevyskytuje - reset
                        reset();
                        pismena[pismeno] = 2;
                    }

                    if(pokusy[j/2 - 1][k] == 0) printf("  ");   // Vypisanie slova prislusnou farbou
                    else printf("%c ", pokusy[j/2 - 1][k]);

                    reset();
                }
                if(z == 5) z1 = 1;
            }
            else{                   // Ostatne riadky tabulky (cisto kozmeticke veci)
                for(int k=0; k<6; k++){
                    if(k == 0) printf("+");
                    else if(k == 5){
                        printf("+");
                        break;
                    }
                    else printf("-");
                    printf("---");
                }
            }

            printf("\n");
        }

        if(z1 == 1){                                            // Pripad ze hrac uhadol v slovo
            printf("\n     Congratulations! You win!");
            break;
        }
        if(i == 5){                                             // Pripad ze hracovi dosli pokusy
            break;
        }

        for(int j=65; j<91; j++){                           // Vypisanie abecedy (ktore pismena boli pouzite)
            if(pismena[j-65] == 1) green();
            else if(pismena[j-65] == 2) red();
            else reset();
            printf("%c ", j);
        }

        reset();
        printf("\n");

    }

    if(z1 == 0){
        printf("\nThe word was: '");
        for(int i=0; i<5; i++){
            printf("%c", slova[x][i]);
        }
        printf("'.. Better luck next time!");
    }

    return 0;
}
