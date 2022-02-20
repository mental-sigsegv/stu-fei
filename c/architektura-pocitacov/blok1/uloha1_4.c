#include <stdio.h>
#include <float.h>
#include <math.h>

int main() {
    float epsilon = __FLT_EPSILON__;
    printf("\n%.25f", epsilon);
    printf("\n%.25f", 1/pow(2, 30));
    return 0;
}