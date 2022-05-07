#include <stdio.h>

#define TEST "\e[=4h"

int main()
{
    printf("Hello World!\n");
    printf(TEST "Hello World!\n");
    return 0;
}
