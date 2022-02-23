#include <stdio.h>
#include <math.h>
#include <float.h>

double fact(int k) {
    double tmp = 1;
    for (int i = 2; i <= k; i++) {
        tmp *= i;
    }

    return tmp;
}
int main() {
    for (int i = 1; i <= 50; i++) {
        printf("%2d %lf\n", i, fact(i));
    }
}