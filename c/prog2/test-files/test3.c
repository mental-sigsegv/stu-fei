#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>



int main() {
    for (int i = 0; i < 10; i++) {
        switch(i) {
            case 3:
                printf("tri\n");
                break;
            case 5:
                printf("pat\n");
                break;
            default: 
                printf("Ine cislo, konretne %d\n", i);
        }
    }
    return 0; 
}
