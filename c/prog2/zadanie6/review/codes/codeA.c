#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

char* random_word();        // deklaracie funkcii
void game();
int error_handling(char string[]);

void green(){       // nastavenie prislusnej farby textu
    printf("\033[1;32m");
}

void yellow(){
    printf("\033[1;33m");
}

void reset(){
    printf("\033[0m");
}


int main() {        // volanie hlavnej funkcie v maine
    game();
    return 0;
}


char* random_word(){        // funkcia na vygenerovanie pseudo-nahodneho slova
    char *database[] = {"sigma", "grind", "based", "hello", "about", "later",       // databaza slov
                        "tears", "worse", "roast", "toast", "media", "cream",
                        "snake", "adieu", "salet", "salad", "smart", "taste"};

    srand(time(NULL));
    int n = rand() % 16;        // vyber pseudo-nahodneho slova
    return database[n];
}

void game(){        // funkcia samotnej hry
    int i, j, k;
    char word[6];
    char guess_word[6];

    strcpy(word, random_word());        // do word pridelime pseudo-nahodne slovo z databazy
    word[5] = '\0';
    guess_word[5] = '\0';

    for(i = 0; i < 6; i++){     // 6 pokusov

        printf("Round %d: \n", i + 1);
        printf("Enter a 5-letter word: \n");
        scanf("%s", guess_word);        // naskenujeme hadane slovo
        printf("Your word: %s\n", guess_word);

        if(strcmp(word, guess_word) == 0){      // ak uhadnes, win
            printf("You won!");
            break;
        }

        if(error_handling(guess_word) == 1){        // skontrolujeme ci je dlzka slova 5 znakov
            printf("Word must contain exactly 5 letters\n");
        }
        else{
            for(j = 0; j < 5; j++){
                for(k = 0; k < 5; k++){     // porovname jednotlive element a nastavime farbu
                    if((guess_word[j] == word[k]) && j == k){       // zelena, ak sme uhadli pozicie aj spravne pismena
                        green();
                        break;
                    }
                    if((guess_word[j] == word[k]) && j != k){       // zlta, spravne pismena, no nespravne pozicie
                        yellow();
                        break;
                    }
                }

                printf("%c", guess_word[j]);        // printujeme po jednotlivych charoch
                reset();
            }
        }
        printf("\n");
        memset(guess_word, 0, strlen(guess_word));      // pravdepodobne zbytocnost :-)
    }

    printf("The word was: %s", word);
}

int error_handling(char string[]){      // jednoducha funkcia na osetrenie spravnej dlzky hadaneho slova(5 znakov)
    if(strlen(string) != 5){
        return 1;
    }
    return 0;
}
