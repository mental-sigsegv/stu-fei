#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <windows.h>


int main() {
    setlocale(LC_ALL, "en_US.cp437");

    for (int c = 0; c < 256; c++) {
        printf("%3d %c |", c, c);
        if (c%15 == 0) {
            printf("\n");
        }
    }
    return 0;
}
