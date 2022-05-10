#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//makra pre vyfarbovanie textu
#define red "\033[1;31m"
#define red_b "\033[1;41m"
#define yellow_b "\033[1;43m"
#define green_b "\033[1;42m"
#define reset "\033[0m"

//hra je spravena jednoduchsie ako original wordle, no stale zachytava podstatu a princip
//hladane slovo je vzdy len malymi pismenami, preto ak zadate velke, bude vam to brat ze sa pismeno nenachadza v slove
//hladane slova neobsahuju ziadne pismeno dva krat, takze take ani hadat nemusite
//testovane aj v replite, fungovalo tak ako ma 
int main() {
    //legenda
    printf(red_b"   "reset":pismeno sa nenachadza v slove\n");
    printf(yellow_b"   "reset":pismeno sa nachadza v slove, ale na inom mieste\n");
    printf(green_b"   "reset":pismeno sa nachadza na spravnom mieste\n");

    //pole so slovami(na kazde pismeno abecedy je jedno slovo)
    char* slova[]={ "actor", "bench", "chain", "draft", "earth", "force", "guest", "heavy", "index", "joint","kebab", "laugh", "mayor", "north", "ocean", "prime", "quick", "roger", "sharp", "tight", "usage", "vital", "women","xenia", "youth", "zumba"};

    //tu ziskame pocet stringov v poli a nasledne nahodne vyberieme string
    int lenght=sizeof(slova)/sizeof(slova[0]);
    int k;
    srand((unsigned)time(NULL));
    //k=index nahodne vybraneho stringu
    k = rand() % lenght;

    //nas vstup
    char vstup[6];
    int win_flag=0;
    //flagy na zistenie ci sa v hladanom slove nachadzaju pismena slova ktore sme my zadali
    int flag_g,flag_y;
    int i=0,j,q;
    while(1) {

            //i nam rata pokusy
            i+=1;
            if(i<=6) {
                printf("%d. pokus\n", i);
            }

            //tu zadavame vstup
            scanf("%s", vstup);

            if(strcmp(vstup,"Koniec")==0){
            return 0;
            }
            //spravny format vstupu je 5 pismen, ak zadate viac alebo menej, musite zadat novy
            while(strlen(vstup)!=5){
                if(strlen(vstup)!=5){
                    printf("Zadany vstup musi obsahovat 5 pismen!\n");
                    scanf("%s", vstup);
                }
            }

            //win_flag "flaguje" ze ste uhadli slovo
            if (strcmp(vstup, slova[k]) == 0) {
                win_flag=1;
            }

            //ak ste ho uhadli vyhrali ste a hra konci
            if(win_flag==1){
                printf(green_b "%s" reset,slova[k]);
                printf(red "\nVyhrali ste!\n");
                printf(reset "\nNapiste slovo Koniec a ukoncite hru\n");
                scanf("%s",vstup);
                if(strcmp(vstup,"Koniec")==0){
                    return 0;
                }
            }
            //ak ste ho neuhadli, vyfarbia sa pismena na zaklade toho, ci sa v slove nachadzaju alebo nie
            //resp ci na spravnom alebo zlom mieste
            if(win_flag==0) {

                //porovnava pismena rovnakych indexov, resp na rovnakom mieste
                //ak sa pismena zhoduju, vyfarbi sa pismeno na zeleno
                for (j = 0; j < 5; j++) {
                    flag_g = 0;
                    flag_y = 0;
                    if (slova[k][j] == vstup[j] && vstup[j] != '\0') {
                        flag_g = 1;
                        printf(green_b "%c" reset" ", vstup[j]);
                    }
                    //inak porovnava pismeno j-teho indexu naseho slova s pismenom q-teho indexu hladaneho slova
                    //inymi slovami, pozrie na prve(dalej druhe, tretie...) pismeno naseho vstupu
                    //a porovna ho so vsetkymi pismenami hladaneho slova
                    //ak sa tam nachadza, vyfarbi sa na zlto
                    else {
                        for (q = 0; q <= 5; q++) {
                            if (vstup[j] == slova[k][q] && vstup[j] != '\0') {
                                flag_y = 1;
                                printf(yellow_b "%c" reset " ", vstup[j]);
                            }
                        }
                    }
                    //ak sa tam pismeno nenachadza, vyfarbi sa na cerveno
                    if (flag_y != 1 && flag_g != 1) {
                        printf(red_b "%c" reset " ", vstup[j]);
                    }
                }
                printf("\n");
                //ak sme ani na 6. pokus neuhadli slovo, vypise sa nam hladane slovo a hra konci
                if(i==6){
                    printf("Koniec pokusov!");
                    printf("\nHladane slovo bolo " green_b "%s",slova[k]);
                    printf(reset "\nNapiste slovo Koniec a ukoncite hru\n");
                }
            }
    }
}
