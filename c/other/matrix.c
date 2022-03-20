#include <stdio.h>

int main()
{
    int num, k=11;
    for (int i = 1; i < k; i++) {
        for (int j = 1; j < k; j++) {
            if ((i == j) && ((i*j) % k == 1)) {
                num = 2;
            } else if ((i*j) % k == 1){
                num = 1;
            } else {
                num = 0;
            }
            printf("%d ", num);
        }
        printf("\n");
    }
    return 0;
}
