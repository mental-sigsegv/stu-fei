#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("Start of debugging...\n");
    for (int i = 1; i < 20; i++) {
        printf("%2.d. Hello World!\n", i);
        // break;
    }
    
    return 0;
}
