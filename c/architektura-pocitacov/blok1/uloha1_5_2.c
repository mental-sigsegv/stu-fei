#include <stdio.h>
#include <math.h>
#include <limits.h>

float degToRad(int deg) {
    // const float PI = 2*acos(0.0);  // arccos(0) vracia pi/2 - ak by nebola M_PI 
    return (deg%360)*M_PI/180;  // %360 kvoli periodite, *pi/180 preraba stupne na radiany
}

double fact(int k) {
    double tmp = 1;
    for (int i = 2; i <= k; i++) {
        tmp *= i;
    }

    return tmp;
}

float cosine(int degree, float epsilon) {
    float radians = degToRad(degree);
    int n=1;
    float lib_cos = cos(radians);
    double arr[20];
    arr[0] = 1.0;

    do {
        arr[n] = arr[n-1] + ((pow(-1, n))*(pow(radians, 2*n)))/fact(2*n);
        printf("%2d. %.20lf\n", n, arr[n]);  // taylorov rad
        n++;
    } while ((arr[n-1] != arr[n-2]) && ((arr[n-1] > arr[n-2] ? arr[n-1]-arr[n-2] : arr[n-2]-arr[n-1]) >= epsilon));

    printf("\nlib cos  %.20f\n", lib_cos);
    printf("mine cos %.20f\n", arr[n-1]);

    return 0.0;
}

int main() {
    // printf("%d\n", INT_MAX);  // checknut, ci int je 2 / 4 byte
    int deg;  // int kvoli operatoru % (dalo by sa to osetrit pomocou fmod function z math.h)
    float epsilon;

    /*
    Copy paste examples
    36123 0.00000000000001
    -234565 0.000001

    2131 0.0000001
    -2356 0.000000001

    0 0.00000001
    203 1.0e-20
    */

    scanf("%d %f", &deg, &epsilon);
    // epsilon = __FLT_EPSILON__;
    
    printf("\ndegree %d\n", deg);
    printf("epsilon %.20f\n", epsilon);

    cosine(deg, epsilon);

    getchar();   // system("pause");
    return 0;
}

