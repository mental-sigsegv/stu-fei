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
#define _hlb 194
#define _hlt 193
#define _hltb 197

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define reset "\e[0m"

#define TABLE_COLOR YEL
#define TEXT_COLOR GRN

int maxOfFour(char** arr) {
    int max = 0;
    for (int i = 0; i < 4; i++) {
        if ((int)strlen(arr[i]) > max) {
            max = strlen(arr[i]);
        }
    }
    return max;
}

void tabulka(char* name, char* height, char* weight, char* phone, int consoleX, int consoleY) {
    // Set variables
    char* userData[] = {name, height, weight, phone};
    char* tableData[] = {"Meno", "Vyska", "Hmotnost", "Tel. cislo"};

    // char* userData[5] = {name, height, weight, phone, name};
    // char* tableData[5] = {"1", "2", "3", "4", "5"};

    char tableHeader[] = "Zaznam";
    int headerLength = strlen(tableHeader);
    int numberOfItems = sizeof(userData)/8;

    int y = numberOfItems*2+1, x1 = maxOfFour(tableData)+1, x2 = maxOfFour(userData)+1;

    // Set console
    setlocale(LC_ALL, "en_US.cp437");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD point = {consoleX, consoleY};

    COORD size = {800, 800};
    SetConsoleScreenBufferSize(hConsole, size);
    // Print header of table
    SetConsoleCursorPosition(hConsole, point);
    for (int i = 0; i < (x1+x2-headerLength+3-1); i++) {
        if (i == (x1+x2-headerLength+3)/2) {
            printf(TEXT_COLOR " %s ", tableHeader);
        } else if (i == 0) {
            printf(TABLE_COLOR "%c", _ltc);
        } else if (i == (x1+x2-headerLength+3-1-1)) {
            printf(TABLE_COLOR "%c", _rtc);
        } else {
            printf(TABLE_COLOR "%c", _hl);
        }
    }
    printf(reset "\n"); 
    // Print table
    for (int i = 0; i < y; i++) {
        point.Y++;
        SetConsoleCursorPosition(hConsole, point);
        if (i%2 == 0) {
            
            printf(TABLE_COLOR);
            for (int j = 0; j < (x1 + x2 + 3); j++) {
                if ((i == 0) && (j == 0)) {
                    putchar(_vlr);  // vertical line right
                } else if ((i == 0) && (j == (x1 + 1))) {
                    putchar(_hlb);  // horizontal line bottom
                } else if ((i == 0) && (j == (x1 + x2 + 3 -1))) {  
                    putchar(_vll);  // vertical line left
                } else if ((i == (y - 1)) && (j == (x1 + x2 + 3 -1))) {
                    putchar(_rbc);  // right bottom corner
                } else if ((i == (y - 1)) && (j == x1 + 1)) {
                    putchar(_hlt);  // horizontal line top
                } else if ((i == (y - 1)) && (j == 0)) {
                    putchar(_lbc);  // left bottom corner
                } else if (j == 0) {
                    putchar(_vlr);  // vertical line right
                } else if (j == (x1 + x2 + 3 -1)) {
                    putchar(_vll);  // vertical line left
                } else if (j == (x1 + 1)) {
                    putchar(_hltb);  // horizontal line top bottom
                } else {
                    putchar(_hl);
                }
            }

            printf(reset "\n");
        } else {
            printf(TABLE_COLOR "%c" TEXT_COLOR "%-*s" TABLE_COLOR "%c" TEXT_COLOR "%*s" TABLE_COLOR "%c\n", _vl, x1, tableData[i/2], _vl, x2, userData[i/2], _vl);
        }
    }
    scanf("?");
}

int main() {
    tabulka("ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ Martin Klacik", "666 cm", "666 kg", "0429 233 4236676", 50, 50);
    return 0;
}
