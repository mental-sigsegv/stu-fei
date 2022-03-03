#include <stdio.h>

static int result, x, y;

void addNumbers() {
    x = 34; y = 72;
    asm(".intel_syntax noprefix \n"   // Prepneme z AT&T syntaxe na na Intel 
       "movabs eax, x\n"
       "mov ebx, eax\n"
       "movabs eax, y\n"
       "add eax, ebx\n"
       "movabs result, eax\n"

       ".att_syntax            \n"); // Dame vsetko do povodneho stavu

    printf("%d + %d = %d", x, y, result);
}

int main() {
    addNumbers();

    return 0;
}
