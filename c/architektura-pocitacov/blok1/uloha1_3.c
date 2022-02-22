#include <stdio.h>

void fibonaci(int k) {
    int arr[k];
    arr[0] = 1;
    arr[1] = 1;

    int i = 1; 

    printf("%d %d ", arr[0], arr[1]);
    while (1) {
        i++;
        arr[i]=arr[i-1]+arr[i-2];
        if (arr[i] > k) {
            break;
        }
        printf("%d ", arr[i]);
    }
}

int main() {
    fibonaci(143);
}