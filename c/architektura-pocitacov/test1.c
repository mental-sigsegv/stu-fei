#include <stdio.h>

int main() {
    int arr[100] = {0}, i = 0, num = 712;
    while (num > 0) {
        arr[i] = num%2;
        i++;
        num = num/2;
    }

    for (int n=i-1; n >= 0; n--) {
        printf("%d", arr[n]);
    }

}