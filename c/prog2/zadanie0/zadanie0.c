#include <stdio.h>

int isPrime(int num) {
    if (num == 2 || num == 3) {
        return 1;
    } else if (num%2 == 0 || num%3 == 0) {
        return 0;
    } else {
        for (int i = 5; i<num; i = i + 2) {
            if (num%i==0) {
                return 0;
            }
        }
    }
    return 1;
}

void primeFactors(int a, int m) {
    int count = 0;
    for (int i = 2; i <= a; i++) {
        if (a%i == 0 && isPrime(i)) {
            count++;
            if (count > m) {
                break;
            }
            printf("%d\n", i);
            a = a / i;
        }
    }
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a > 1) {
        primeFactors(a, b);
    } else {
        printf("ERROR");
    }

    return 0;
}
