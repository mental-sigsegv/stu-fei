#include <stdio.h>

void toBin(int x) {  
    int arr[100], i = 0, num = x;
    while (num > 0) {
        arr[i] = num%2;
        i++;
        num = num/2;
    }
    for (int n=i-1; n >= 0; n--) {
        printf("%d", arr[n]);
        if (n%4 == 0) {
            printf(" ");
        }
    }
}

void uloha1(int chr) {
    int intChr = chr; 
    printf("\nCharacter: '%c'\nDec: %d\nHex: %X\nBin: ", chr, chr, chr);
    toBin(intChr);
}

int main() {
    uloha1('X');
}