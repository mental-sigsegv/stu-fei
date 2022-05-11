/* Dobrý deň! Program by mal celý fungovať správne :)
 * Pôvodne bol písaný a testovaný vo windowse s gcc kompilátorom ale dúfam,
 * že pôjde normálne spustiť aj inde.
 * Je v ňom až 8 slov na uhádnutie, obsahuje aj výpis pravidiel hry a štatistiku, ktorá sa
 * vypíše na konci hry. Nejaké rady na zlepšenie sú určite vítané! ♥
 * */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//farby:
void reset() {
    printf("\033[0m");
}

void green() {
    printf("\033[32m");
}

void yellow() {
    printf("\033[33m");
}

void rules(){       //pravidlá hry, vačšina je priamo z oficiálnej wordle stránky:

    printf("\n─────────────────────────────\n");
    printf("\n         HOW TO PLAY\n\n");
    printf("Guess the WORDLE in six tries.\n");
    printf("Each guess must be a five-letter word. Hit the enter button to submit.\n");
    printf("Type the word in lowercase letters.\n");
    printf("After each guess, the color of the tiles will change \n"
           "to show how close your guess was to the word.\n\n");
    printf("Examples\n\n");
    printf("┌───┬───┬───┬───┬───┐\n");
    printf("│ ");
    green();
    printf("W");
    reset();
    printf(" │ E │ A │ R │ Y │\n");
    printf("└───┴───┴───┴───┴───┘\n");
    printf("The letter W is in the word and in the correct spot\n");
    printf("┌───┬───┬───┬───┬───┐\n");
    printf("│ P │ ");
    yellow();
    printf("I");
    reset();
    printf(" │ L │ L │ S │\n");
    printf("└───┴───┴───┴───┴───┘\n");
    printf("The letter I is in the word but in the wrong spot\n");
    printf("\n─────────────────────────────\n");

}

void border(int a){

    if (a == 1){
        printf("┌───┬───┬───┬───┬───┐\n");
        printf("│ ");
    }
    else{
        printf("\n└───┴───┴───┴───┴───┘\n");
    }

}

void print_game(char game[6][5], char word[]){      //výpis
    int m,n,o;
    int count, rank;
    for (m = 0; m < 6;m++){

        border(1);
        for(n = 0; n < 5; n++){
            if (game[m][n] == word[n]) {            //písmenko na správnej pozícii
                green();
            }
            else if(strchr(word, game[m][n]) != NULL){
                count = 1;                          //správne písmeno na zlej pozícii
                rank = 1;
                for(o = 0; o<5; o++){               //celý tento for cyklus je tu na
                   if (game[m][o] == game[m][n]){   //takéto prípady:
                       if(o <= n){                  //správne slovo - apple
                           rank +=1;                //vstup z klávesnice - aaaaa (budeme sa tváriť že je to slovo)
                       }                            //iba prvé "a" sa vypíše zelené
                   }                                //zbytok zostane obyčajný bez farebného výpisu
                   if (word[o] == game[m][n]){
                       count +=1;
                   }
                   if (word[o] == game[m][o]){
                       count -=1;
                   }

                }

                if ((rank!=0)&&(count!=0)){
                    if (rank <= count){
                        yellow();
                    }
                }
            }
            printf("%c", toupper( game[m][n]));
            reset();
            printf(" │ ");
        }
        border(2);
    }

}

void end_stats(int stats[], int w, int i){              //štatistika ktorá sa vypíše na konci hry
    int s, t;
    double sum = 0;
    char c = '%';
    printf("\n─────────────────────────────\n");
    printf("\n         STATISTICS\n\n");
    printf("Played: %7d\n", i);                         //koľko slov hráč hádal
    if ( i == 0){       //toto je tu na to aby pri win % výpise nepísalo hlúposti
        i +=1;          //kvôli deleniu 0 v prípade že hráč nehádal vôbec
    }
    printf("Win %c: %8.3lf\n", c, 100.0*((double)w/(double)i));
    printf("\n    GUESS DISTRIBUTION\n");
    for (s = 0; s < 6; s ++){               //vypíše koľko slov bolo uhádnutých na ktorý pokus
        sum += (s+1)*stats[s];
        reset();
        printf("\n%d ", (s+1));
        green();
        for (t = 0; t < stats[s]; t ++){
            printf("█");
        }
    }
    reset();
    printf("\n\nAverage amount of guesses: %.3lf\n", (sum/(double)i));
    printf("\n─────────────────────────────\n");
}

int main() {

    //slová na uhádnutie:
    char words[8][5] = {"stray" ,"charm","venom", "light",
                        "haven","slump","awake","voice"};
    // v klasickom wordle sa síce háda iba jedno slovo denne
    // ale pre lepšie testovanie je ich v tomto programe 8


    char input[5];
    int i, j, k, l;                     //attempt - počíta pokusy na úhadnutie 1 slova
    int attempt, correct, win = 0;      //correct - počet znakov na správnych pozíciách
                                        //win - počet správne uhádnutých slov

    int guesses[] = {0,0,0,0,0,0}; //predstavuje počet slov uhádnutých na 1-6 pokus

    for(i = 0; i < 8; i ++){
        char game[6][5] = {{' ',' ',' ',' ',' '},   //"herná plocha" pre výpis
                           {' ',' ',' ',' ',' '},
                           {' ',' ',' ',' ',' '},
                           {' ',' ',' ',' ',' '},
                           {' ',' ',' ',' ',' '},
                           {' ',' ',' ',' ',' '}};

        char riddle[6];         //aktuálne slovo ktoré treba uhádnuť
        attempt = 0;

        for(k = 0; k <5; k++){
            riddle[k] = words[i][k];
        }
        riddle[5] = '\0';

        print_game(game, riddle);

        while(1){
            printf("\nType RULES to see the rules of the game\n");
            printf("Type END to end the game and show statistics\n\n");
            scanf(" %s", input);
            if (strcmp(input, "END") == 0){
                printf("YOU EXITED THE GAME\n");
                end_stats(guesses, win, i);
                return 0;
            }
            else if (strcmp(input, "RULES") == 0){
                rules();
                print_game(game, riddle);
            }
            else if (strlen(input) != 5){
                printf("The word you put in is of incorrect length\n");
            }
            else{
                j = 0;
                correct = 0;

                while (input[j] != '\0'){
                    game[attempt][j] = input[j];
                    if (input[j] == riddle[j]) {
                        correct += 1;
                    }
                    j += 1;
                }
                print_game(game, riddle);
                attempt += 1;

                if (correct == 5){
                    printf("Congratulations! You guessed the correct word. \n\n");
                    guesses[attempt - 1] += 1;
                    win +=1;
                    break;
                }
                else if(attempt == 6){
                    printf("Unfortunately, you ran out of attempts.");
                    printf("The correct word was ");
                    for(l = 0; l < 5; l ++){
                        printf("%c", toupper(riddle[l]));
                    }
                    printf("\n\n");
                    break;
                }

            }

        }
    }

    printf("You guessed all the words!\n");
    end_stats(guesses, win, i);

    return 0;
}
