#include <stdio.h>

void foo() {
    // do something
}

int main()
{
    int value = 10;
    
    int array1[8] = {2, 4, 6, 8, 10, 12, 14, 16};
    int array2[] = {2, 4, 6, 8, 10, 12, 14, 16};

    int matrix[5][5];

    char text[10] = "Hello";

    char *p_array = text;
    int *p_value = &value;

    foo();

    return 0;
}
