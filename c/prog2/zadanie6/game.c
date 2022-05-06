// Includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>


// Ansi colors - source https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
// Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

// Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

// Special
#define ITALIC "\e[3m"
#define RESET "\e[0m"

// You can change those, if you want
#define ROWS 6
#define COLUMNS 5

// Wordle in fancy text with ansi colors
// source - https://www.coolgenerator.com/ascii-text-generator
char* wordle[128] = {"\e[4;32m██\e[0;33m╗    \e[4;32m██\e[0;33m╗ \e[4;32m██████\e[0;33m╗ \e[4;32m██████\e[0;33m╗ \e[4;32m██████\e[0;33m╗ \e[4;32m██\e[0;33m╗     \e[4;32m███████\e[0;33m╗", "\e[4;32m██\e[0;33m║    \e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m╔═══\e[4;32m██\e[0;33m╗\e[4;32m██\e[0;33m╔══\e[4;32m██\e[0;33m╗\e[4;32m██\e[0;33m╔══\e[4;32m██\e[0;33m╗\e[4;32m██\e[0;33m║     \e[4;32m██\e[0;33m╔════╝", "\e[4;32m██\e[0;33m║ \e[4;32m█\e[0;33m╗ \e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m║   \e[4;32m██\e[0;33m║\e[4;32m██████\e[0;33m╔╝\e[4;32m██\e[0;33m║  \e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m║     \e[4;32m█████\e[0;33m╗  ", "\e[4;32m██\e[0;33m║\e[4;32m███\e[0;33m╗\e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m║   \e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m╔══\e[4;32m██\e[0;33m╗\e[4;32m██\e[0;33m║  \e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m║     \e[4;32m██\e[0;33m╔══╝  ", "\e[0;33m╚\e[4;32m███\e[0;33m╔\e[4;32m███\e[0;33m╔╝╚\e[4;32m██████\e[0;33m╔╝\e[4;32m██\e[0;33m║  \e[4;32m██\e[0;33m║\e[4;32m██████\e[0;33m╔╝\e[4;32m███████\e[0;33m╗\e[4;32m███████\e[0;33m╗", "\e[0;33m ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝"};

void clear_terminal() {
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J\0";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

int letter_in_key(char letter, char *key) {
    for (int l=0; l<(int)strlen(key); l++) {
        if (letter == key[l]) {
            return 1;
        }
    }
    return 0;
}

void generate_table(char** userInput, char* key) {
    // Table ROWSxCOLUMNS
    char letter, keyLetter;
    for (int row=0; row<=ROWS*2; row++) {
        if (row%2 == 1) {  // print letters
            printf("%2d. |", row/2);
            for (int column=0; column<COLUMNS*2; column++) {
                if (column%2 == 0) {
                    letter = toupper(userInput[row/2][column/2]);
                    keyLetter = toupper(key[column/2]);
                    if (letter == keyLetter) {  // Green letter
                        printf(GRN "%c" , letter);
                    } else if (letter_in_key(letter, key) == 1) {  // Yellow letter
                        printf(YEL "%c" , letter);
                    } else {
                        printf("%c", letter);  // White letter
                    }
                    
                } else {
                    printf(RESET "|");  // Reset color before next letter
                }
            }
        } else {  // print lines between words
            printf("    ");
            for (int column=0; column<=COLUMNS*2; column++) {
                printf("%c", "+-"[column%2]);
            }
        }
        printf("\n");
    }
}

// Function to print fancy 'wordle' text
void print_wordle() {
    printf("\n"); 

    // Printing each line
    for (int i = 0; i < 6; i++) {
        printf("%s\n", wordle[i]);
    }

    // Printing creator of this creation
    printf("%s%sby anonymous %sFEI STU%s%sdent%s\n", RESET, ITALIC, BWHT, RESET, ITALIC, RESET);
}

// Main
int main() {
    char* array[ROWS];

    // Create empty string for dynaminc setting of columns
    char emptyString[COLUMNS];
    for (int c=0; c<COLUMNS; c++) {
        emptyString[c] = ' ';
    }

    // Fill array
    for (int r=0; r < ROWS; r++) {
        array[r] = emptyString;
        array[r] = "adcbe";
    }

    // clear_terminal();
    // print_wordle();

    // printf("\nPress %sENTER%s to continue...\n", ITALIC, RESET);
    // getchar();
    // clear_terminal();

    // printf("Good job, let's play!\n");
    generate_table(array, "ABCDE");
    // getchar();

    return 0;
}
