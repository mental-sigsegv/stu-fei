#include <stdio.h>
#include <math.h>


double degToRad(int deg) {
    double pi = 2*acos(0.0);  // arccos(0) vracia pi/2
    return (deg%360)*pi/180;
}

double fact(int k) {
    double tmp = 1;
    for (int i = 1; i <= k; i++) {
        tmp *= i;
    }
    return tmp;
}

int main() {
    // cos
    int k = 30;
    int degree = 5372+180;
    double arr[k];
    double x = degToRad(degree);
    
    printf("Deg:      %d\n", degree);
    arr[0] = 1;

    for (int n = 1; n < k; n++) {
        arr[n] = arr[n-1] + ((pow(-1, n))*(pow(x, 2*n)))/fact(2*n);
    }

    printf("Cos:      %.20lf\n", cos(x));
    printf("Mine cos: %.20lf\n", arr[k-1]);
    // printf("%d", cos(x) == arr[k-1]);

    return 0;
}

