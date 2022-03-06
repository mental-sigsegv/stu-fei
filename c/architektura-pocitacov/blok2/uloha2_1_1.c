#include <stdio.h>

static int result, x, y;

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

int main() {
    add_nums_asm(123, 32);

    return 0;
}
