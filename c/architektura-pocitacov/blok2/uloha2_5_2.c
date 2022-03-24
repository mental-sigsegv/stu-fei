#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <windows.h>
#include <string.h>

#define _ltc 218
#define _lbc 192
#define _rbc 217
#define _rtc 191
#define _vl 179
#define _hl 196
#define _empty 32
#define _vll 180
#define _vlr 195
#define _vlt 194
#define _vlb 193
#define _vltb 197

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define reset "\e[0m"

int maxOfFour(char** arr) {
    int max = 0;
    for (int i = 0; i < 4; i++) {
        if ((int)strlen(arr[i]) > max) {
            max = strlen(arr[i]);
        }
    }
    return max;
}

void tabulka(char* name, char* height, char* weight, char* phone) {
    // Set variables
    char* user_data[4] = {name, height, weight, phone};
    int y = 10, lenght = maxOfFour(user_data);
    lenght += 10;
    int table[y][lenght];

    // Set console
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // system("clear");
    setlocale(LC_ALL, "en_US.cp437");
    
    // Store data in array
    for (int row = 0; row < y; ++row) {
        for (int column = 0; column < lenght; column++) {
            if ((column == 0) || (column == lenght-1)) {
                if ((row%2 == 1) && (column == 0)) {
                    table[row][column] =_vlr;
                } else if ((row%2 == 1) && (column == lenght-1)) {
                    table[row][column] =_vll;
                } else {
                    table[row][column] =_vl;
                }
            } else if ((row == 0) || (row%2 == 1)) {
                table[row][column] =_hl;
            } /*else {
                table[row][column] = _empty;
            }*/
        }
    }

    // Get corners
    table[0][0] = _ltc;
    table[y-1][0] = _lbc;
    table[0][lenght-1] = _rtc;
    table[y-1][lenght-1] = _rbc;

    // Set middle line
    int pos = 10;
    for (int i = 0; i < y; i++) {
        if (i == 0) {
            table[0][pos] = _vlt;
        } else if (i == y-1) {
            table[i][pos] = _vlb;
        } else if (i % 2 == 1) {
            table[i][pos] = _vltb; 
        } else {
            table[i][pos] = _vl;
        }
        
    }

    int n = (lenght-8)/2;
    for (int i = n; i < 8+n; i++) {
        table[0][i] = " Zaznam "[i-n];
    }
    

    // Print the table
    // SetConsoleTextAttribute(hConsole, 6);
    int chr = 0;
    for (int row = 0; row < y; ++row) {
        for (int column = 0; column < lenght; column++) {
            chr = table[row][column];
            if (chr < 128) {
                printf(GRN "%c" reset, chr);
            } else {
                printf(YEL "%c" reset, chr);
            }
        }
        putchar('\n');
    }

    SetConsoleTextAttribute(hConsole, 7);
    // scanf("?");
}

int main() {
    tabulka("Martin Klacik", "172 cm", "72 kg", "0429 233 423");

    
    // Display values
    // for (int c = 0; c < 256; c++) {
    //     printf("%3d %c |", c, c);
    //     if (c%15 == 0) {
    //         printf("\n");
    //     }
    // }
    // COORD point;
    // point.X = 30; point.Y = 30;                  // ina moznost zadania suradnice
    // SetConsoleCursorPosition(hConsole, point); 

    
    // for (int i = 0; i < x; i++) {
    //     putchar(_vl);
    //     for (int j = 0; j < y; j++) {
    //         if (i%(x-1-7) == 0) {
    //             putchar(_hl); 
    //         } else if (j%(y-1) == 0) {
    //             putchar(' '); 
    //         }  else {
    //             putchar('A');
    //         }
    //     }
    //     putchar(_vl);
    //     putchar('\n');
    //     point.Y++;
    //     SetConsoleCursorPosition(hConsole, point); 
    // }

    // scanf("?");
    return 0;
}
