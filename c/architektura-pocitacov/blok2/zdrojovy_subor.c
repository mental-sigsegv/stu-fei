/* BLOK 2 */

#include "hlavickovy_subor.h"
#include <stdio.h>   // input, output
#include <stdlib.h>
#include <windows.h>  // for HANDLE

static int result, x, y;  // 2.1.1
static int g_var;  // 2.1.2
char proccesor_name[12];  // 2.1.4

/* 2.1.5
GREEN  = 2
BLUE   = 3
RED    = 4
PURPLE = 5
YELLOW = 6
WHITE  = 7
*/


void add_nums_asm(int n1, int n2) {
    x = n1; y = n2;
    asm(".intel_syntax noprefix\n"

       "movabs eax, x\n"
       "mov ebx, eax\n"
       "movabs eax, y\n"
       "add eax, ebx\n"
       "movabs result, eax\n"

       ".att_syntax\n");

    printf("%d + %d = %d", x, y, result);
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
    asm(".intel_syntax noprefix\n"
        
        "mov eax, 0x0\n"
        "cpuid\n"
        
        "mov eax, ebx\n"
        "movabs proccesor_name, eax\n"

        "mov eax, edx\n"
        "movabs [proccesor_name+4], eax\n"

        "mov eax, ecx\n"
        "movabs [proccesor_name+8], eax\n"
        ".att_syntax\n");
    
    
    for (int i = 0; i < 12; i++) {
        printf("%c", proccesor_name[i]);
    }
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


int main()
{
    // add_nums_asm(678, -78);  // 2.1.1 [1b]
    // multiply_by2_asm(89);  // 2.1.2 [1b]
    // get_processor_name_asm();  // 2.1.4 [2b]
    // colorful_numbers();  // 2.5.1 [1b]
    return 0;
}
