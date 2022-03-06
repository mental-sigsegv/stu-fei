#include <stdio.h>

static int g_var;

void multiply_by2_asm(int x) {
    g_var = x;
    asm(".intel_syntax noprefix\n"
        "movabs eax, g_var\n"
        "shl eax\n"
        "movabs g_var, eax\n"
        ".att_syntax\n");

    printf("%d\n", g_var);
}

int main()
{
    multiply_by2_asm(-10);
    return 0;
}
