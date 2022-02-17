#include <stdio.h>

unsigned long long  toBin(int x) {  
    
    unsigned long long result=0, i=1;
    while (x > 0) {
        result += i*(x%2);
        x = x/2;
        i = i * 10;
    }
    return result;
}

int main() {
    int num = 2;  // max num 1 048 575
    char chr = 'A';

    int intChar = chr; 
    
    printf("---------------------------------------");
    printf("\nCharacter: '%c'\nBin: %llu\nDec: %d\nHex: %x\n", chr, toBin(intChar), chr, chr);

    printf("---------------------------------------");
    printf("\nNumber: '%d'\nBin: %llu\nDec: %d\nHex: %x", num, toBin(num), num, num);
}