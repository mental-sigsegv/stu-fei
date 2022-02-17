#include <stdio.h>
#include <math.h>

int fact(int k) {
    int tmp = 1;
    for (int i = 1; i <= k; i++) {
        tmp *= i;
    }
    return tmp;
}

int main() {
    // cos
    double arr[20];
    double x = 0.1;
    arr[0] = 1;

    for (int n = 1; n < 20; n++) {
        arr[n] = arr[n-1] + ((pow(-1, n))*(pow(x, 2*n)))/fact(2*n);
    }

    printf("%lf", arr[1]);
}

