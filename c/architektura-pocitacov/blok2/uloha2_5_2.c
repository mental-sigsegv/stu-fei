#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


void table() {
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 255; i++) {
        printf("%c ", i);
    }
}

int main() {
    table();
    // getchar();
    return 0;
}
