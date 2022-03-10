#include <stdio.h>
#include <stdlib.h>

void edit(int arr[], int i) {
    arr[i/2] = i;
}

int main() {
    int n[8] = {0,1,2,3,4,5,6,7};
    edit(n, 12);
    edit(n, 6);
    for (int i = 0; i < 8; i++) {
        printf("%d ", n[i]);
    }
    
    return 0;
}
