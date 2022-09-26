#include <stdio.h>

int gValue = 0;

void inc_gValue() {
    gValue++;
}

void inc_value(int value) {
    value++;
    printf("%d\n", value);  // 2
}

int main() {
    inc_gValue();
    printf("%d\n", gValue);  // 1

    inc_value(gValue);
    printf("%d\n", gValue);  // 1

    return 0;
}
