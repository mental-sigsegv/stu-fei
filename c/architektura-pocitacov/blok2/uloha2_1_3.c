#include <stdio.h>

static int g_int;

void num_toHex_asm(int num) {
    g_int = num;
    asm(".intel_syntax noprefix\n"
        "movabs eax, g_int\n"
        "mov ebx, 10\n"
        "cmp ebx, eax\n"
        "jg l1\n"
        "add eax, 55\n"
        "l1: movabs g_int, eax\n"
        ".att_syntax\n");
    
    printf("%d %x %c", g_int, g_int, g_int);
}

int main()
{
    num_toHex_asm(15);
    return 0;
}
