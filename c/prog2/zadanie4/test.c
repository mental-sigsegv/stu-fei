#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    char* num = "38.3asdasd";

    printf("%f", atof(num));
    return 0;
}