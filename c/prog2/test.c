#include <stdio.h>
#include <stdlib.h>


void edit_arr(int *arr_en, int *arr_ex) {
    int tmp = arr_en[1];
    arr_en[1] = arr_en[2];
    arr_en[2] = tmp;

    tmp = arr_ex[1];
    arr_ex[1] = arr_ex[2];
    arr_ex[2] = tmp;

}

int main() {
    int enter[] = {1, 7, 5};
    int exit[] = {10, 6, 8};

    for (int i = 0; i < 3; i++) {
        printf("[%d,%d]\n", enter[i], exit[i]);
    }
    printf("\n");

    edit_arr(enter, exit);

    for (int i = 0; i < 3; i++) {
        printf("[%d,%d]\n", enter[i], exit[i]);
    }

    return 0;
}
