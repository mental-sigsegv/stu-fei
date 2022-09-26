#include <stdio.h>

void foo(void) {
    printf("Hello World!");
}

int main()
{
    int number = 10;
    char letter = 'a';
    float decimal = 3.4f;
    double bigger_decimal = 3.4;
    void *empty;

    printf("%d %c %f %lf", number, letter, decimal, bigger_decimal);

    return 0;
}


