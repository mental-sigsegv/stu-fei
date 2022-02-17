#include <stdio.h>

void fibonaci(int k) {
    int arr[k];
    arr[0] = 1;
    arr[1] = 1;

    for (int i = 2; i < k; i++) {
        arr[i] = arr[i-1] + arr[i-2];
    }

    for (int i = 0; i < k; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {
    fibonaci(1);
}