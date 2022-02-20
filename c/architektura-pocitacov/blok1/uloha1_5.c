#include <stdio.h>
#include <math.h>


double degToRad(int deg) {
    return (deg%180)/(double)180;
}

int fact(int k) {
    int tmp = 1;
    for (int i = 1; i <= k; i++) {
        tmp *= i;
    }
    return tmp;
}

int main() {
    // cos
    long int k = 12;
    int degree = 100;
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

