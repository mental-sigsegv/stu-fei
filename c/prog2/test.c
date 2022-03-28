#include <stdio.h>
#include <stdlib.h>


void edit_arr(int* arr) {
    arr[2] = 10;
    return;
}

int main() {
    int arr[]= {1,2,3,4};

    edit_arr(arr);

    for (int i = 0; i < 4; i++)
    {
        printf("%d%c", arr[i], (i==3)?'\n':' ');
    }
    
}
