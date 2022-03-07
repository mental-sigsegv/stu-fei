#include <stdio.h>

char proccesor_name[12];

void getProccesorName() {
    asm(".intel_syntax noprefix\n"
        "cpuid\n"
        "mov eax, 0x0\n"

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


int main()
{
    getProccesorName();
    
    return 0;
}
