#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int hexToDec(char* hexstring) {
    int number = (int)strtol(hexstring, NULL, 16);  //https://pubs.opengroup.org/onlinepubs/7908799/xsh/strtol.html
    return number;
}

void intelHex(void) {
    char* data;
    // scanf("%s", data);

    gets(data);

    int l = strlen(data), count = 0, mine;
    char sum_check[3] = {data[l-2], data[l-1]};
    char tmp[3];

    for (int i = 1; i < l-2; i+=2)
    {
        tmp[0] = data[i];
        tmp[1] = data[i+1];

        count += hexToDec(tmp);
        // printf("%d ", hexToDec(tmp));
    }

    mine = 255 - count%256 + 1;
    printf("mine:      %X\nsum_check: %s", mine, sum_check);
}

int main() {
    intelHex();
    return 0;
}