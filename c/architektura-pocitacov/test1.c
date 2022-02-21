#include <stdio.h>
#include <math.h>

double fact(int k) {
    double tmp = 1;
    for (int i = 1; i <= k; i++) {
        tmp *= i;
    }
    return tmp;
}

int main() {
    double pi = 2 * acos(0.0);
    double coppied_pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
    printf("%.100lf\n", pi);
    printf("%.100lf\n", coppied_pi);
    return 0;
}