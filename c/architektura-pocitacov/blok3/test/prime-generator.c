#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

int is_prime(int num) {
    if ((num == 2) || (num == 3)) {
        return 1;
    } else if ((num%2 == 0) || (num == 1)) {
        return 0;
    }
    for (int i = 3; i <= (int)sqrt(num)+1; i=i+2) {
        if (num%i == 0) {
            return 0;
        }
    }
    return 1;
}

void generate_primes(char* text) {
    for (int i = 0; i <= (int)strlen(text); i++) {
        if (is_prime(i) == 1) {
            printf("%c", text[i-1]);
        }
    }
    printf("\n");
}

int main() {
    generate_primes("XLOZGP.R.ACLHCOGAGTER");
    return 0;
}
