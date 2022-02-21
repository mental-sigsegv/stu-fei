#include <stdio.h>
#include <math.h>
#include <stdlib.h>


float degToRad(int deg) {
    float pi = 2*acos(0.0);  // arccos(0) vracia pi/2  double - 15 decimal places
    return (deg%360)*pi/180;  // %360 kvoli periodite, *pi/180 preraba stupne na radiany
}

double fact(int k) {
    double tmp = 1;
    for (int i = 2; i <= k; i++) {
        tmp *= i;
    }

    return tmp;
}

float cosine(float radians, float epsilon) {
    int n=1;
    float lib_cos = cos(radians);
    double arr[20];
    arr[0] = 1.0;

    do {
        arr[n] = arr[n-1] + ((pow(-1, n))*(pow(radians, 2*n)))/fact(2*n);
        printf("%d %.20lf\n", n, arr[n]);
        printf("%d %.20lf\n", ()>=epsilon);  // TODO: min max via a > b ? a-b : b-a;
        n++;
    } while ((arr[n-1] != arr[n-2]));

    printf("\nlib cos  %.20f\n", lib_cos);
    printf("mine cos %.20f", arr[n-1]);

    return 0.0;
}

int main() {
    int deg = 137;
    float rad = degToRad(deg);
    printf("\rrad %f\n", rad);
    cosine(rad, 0.00001);

    // cos
    // int k = 40;
    // int degree = 34534676;
    // float arr[k];
    // double x = degToRad(degree);
    
    // printf("Deg:      %d\n", degree);
    // arr[0] = 1;


    // for (int n = 1; n < k; n++) {
    //     arr[n] = arr[n-1] + ((pow(-1, n))*(pow(x, 2*n)))/fact(2*n);
    // }

    // printf("Cos:      %.20lf\n", cos(x));
    // printf("Mine cos: %.20lf\n", arr[k-1]);
    // // printf("%d", cos(x) == arr[k-1]);

    return 0;
}

