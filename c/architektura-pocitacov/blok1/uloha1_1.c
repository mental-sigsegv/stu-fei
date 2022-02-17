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

int main() {
    int num = 76723905;
    char chr = 'z';

    int intChr = chr; 
    
    printf("\nCharacter: '%c'\nDec: %d\nHex: %X\nBin: ", chr, chr, chr);
    toBin(intChr);
    printf("\n\nNumber: '%d' \nDec: %d\nHex: %x\nBin: ", num, num, num);
    toBin(num);
}