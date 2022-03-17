#include <stdio.h>
#include <limits.h>

void uloha2_2() {
    char text[] = "Hello World!";
    char *p;
    p = text;  // &text[0]

    printf("text: %s\n", text);
    printf("pointer: %p\n", p);
    p++;  // inc pointer
    *p = 'G';
    printf("text: %s\n", text);
    // p += INT_MAX;  // cause STATUS_ACCESS_VIOLATION
    *p = 'G';
}

int main() {
    uloha2_2();    
}