/* BLOK 2 */

#include "hlavickovy_subor.h"
#include <stdio.h>   // input, output
#include <stdlib.h>
#include <windows.h>  // for HANDLE
#include <locale.h>
#include <limits.h>

static int g_result, g_x, g_y;  // 2.1.1
static int g_var;  // 2.1.2
static int g_int;  // 2.1.3
char g_proccesor_name[13];  // 2.1.4


/* 2.1.5
GREEN  = 2
BLUE   = 3
RED    = 4
PURPLE = 5
YELLOW = 6
WHITE  = 7
*/

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


void add_nums_asm(int n1, int n2) {
    g_x = n1; g_y = n2;
    asm(".intel_syntax noprefix\n"

       "movabs eax, g_x\n"
       "mov ebx, eax\n"
       "movabs eax, g_y\n"
       "add eax, ebx\n"
       "movabs g_result, eax\n"

       ".att_syntax\n");

    printf("%d + %d = %d", g_x, g_y, g_result);
}

void multiply_by2_asm(int x) {
    g_var = x;
    asm(".intel_syntax noprefix\n"
        "movabs eax, g_var\n"
        "shl eax\n"
        "movabs g_var, eax\n"
        ".att_syntax\n");

    printf("%d\n", g_var);
}

void get_processor_name_asm() {
    // show in memory -exec x/32b memory
    g_proccesor_name[12] = '\0';  // added null at the end
    asm(".intel_syntax noprefix\n"
        
        "mov eax, 0x0\n"
        "cpuid\n"
        
        "mov eax, ebx\n"
        "movabs g_proccesor_name, eax\n"

        "mov eax, edx\n"
        "movabs [g_proccesor_name+4], eax\n"

        "mov eax, ecx\n"
        "movabs [g_proccesor_name+8], eax\n"
        ".att_syntax\n");
    
    
    for (int i = 0; i < 12; i++) {
        printf("%c", g_proccesor_name[i]);
    }

    // printf("%s\n", g_proccesor_name);
    // getchar();  // for debugging
}

void colorful_numbers() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < 51; i++) {
        switch (i) {
            case 0:
                SetConsoleTextAttribute(hConsole, 2); break;
            case 15:
                SetConsoleTextAttribute(hConsole, 4); break;
            case 30:
                SetConsoleTextAttribute(hConsole, 3); break;
            case 45:
                SetConsoleTextAttribute(hConsole, 6); break;
        }
        
        Sleep(100);
        printf("%03d\n", i); 
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void uloha2_2() {
    char text[] = "Hello World!";
    char *p;
    p = text;  // &text[0]

    printf("text: %s\n", text);
    printf("pointer: %p\n", p);
    p++;  // inc pointer
    *p = 'G';
    printf("text: %s\n", text);
    // p += INT_MAX;  // cause STATUS_ACCESS_VIOLATION
    *p = 'G';
}

void num_to_ascii_asm(int num) {
    g_int = num;
    asm(".intel_syntax noprefix\n"
        "movabs eax, g_int\n"
        "mov ebx, 10\n"
        "cmp ebx, eax\n"
        "jg l1\n"
        "add eax, 7\n"
        "l1: add eax, 48\n"
        "movabs g_int, eax\n"
        ".att_syntax\n");
    
    printf("input: %d\nint: %d\nhex: %x\nascii: %c", num, g_int, g_int, g_int);
}

void uloha2_3_1() {
    FILE *f_input = fopen("./input.html", "r");
    FILE *f_output = fopen("./output.html", "w");
    int x;

    while((x = fgetc(f_input)) != EOF) {
        
        switch(x) {
            case 165: 
                x = 188; break;
            case 169:
                x = 138; break;
            case 171:
                x = 141; break;
            case 174:
                x = 142; break;
            case 181:
                x = 190; break;
            case 185:
                x = 154; break;
            case 187:
                x = 157; break;
            case 190:
                x = 158; break;
        }
        fprintf(f_output, "%c", x);
    }
    
    fclose(f_input);
    fclose(f_output);
}

void uloha2_3_2() {
    // Znak = (Znak XOR Cislo) XOR Cislo
    FILE *f_input = fopen("./koniec_poviedky.txt", "rb");  // read from .txt, .html didnt work
    FILE *f_output = fopen("./koniec_poviedky_decoded.html", "w");
    int x;

    while((x = fgetc(f_input)) != EOF) {
        x = x ^ 27;
        fprintf(f_output, "%c", x);
    }
    
    fclose(f_input);
    fclose(f_output);
}

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
    char* tableData[] = {"KlacikKlacikKlacikKlacikKlacikMeno", "Vyska", "Hmotnost", "Tel. cislo"};

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
    getchar();
}

int main() {
    // Assembler
    // add_nums_asm(89, 23);  // 2.1.1 [1b]
    // multiply_by2_asm(45);  // 2.1.2 [1b]
    // num_to_ascii_asm(23);  // 2.1.3 [3b]
    // get_processor_name_asm();  // 2.1.4 [2b]

    // colorful_numbers();  // 2.5.1 [1b]
    // uloha2_2();  // 2.2 [3b]
    // uloha2_3_1();  // 2.3.1 [2b] 
    // uloha2_3_2();  // 2.3.2 [1b]
    tabulka("KlacikKlacikKlacikKlacikKlacikKlacikMartin Klacik", "666 cm", "666 kg", "0429 233 426", 100, 100);  // 2.5.2 [3b]
    return 0;
}
