#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


int main() {
    for (int i = 0; i < 255; i++) {
        printf("%3d %c ", i, i);
    }

    return 0;
}
