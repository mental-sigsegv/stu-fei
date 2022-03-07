/* BLOK 1 */

#include "hlavickovy_subor.h"
#include <stdio.h>   // input, output
#include <math.h>    // cosine, PI value
#include <string.h>  // strlen
#include <stdlib.h>  // strtol


void fibonaci(int k) {
    int arr[100], i = 1;
    arr[0] = 1;
    arr[1] = 1;

    printf("%d %d ", arr[0], arr[1]);
    while (1) {
        i++;
        arr[i]=arr[i-1]+arr[i-2];
        if (arr[i] > k) {
            break;
        }
        printf("%d ", arr[i]);
    }
}

float degToRad(int deg) {
    // const float PI = 2*acos(0.0);  // arccos(0) vracia pi/2 - ak by nebola M_PI 
    return (deg%360)*M_PI/180;  // %360 kvoli periodite, *pi/180 preraba stupne na radiany
}

double fact(int k) {
    double tmp = 1;
    for (int i = 2; i <= k; i++) {
        tmp *= i;
    }

    return tmp;
}

void cosine(int degree, float epsilon) {
    float radians = degToRad(degree), lib_cos = cos(radians);
    int n = 1;
    double arr[50];

    arr[0] = 1.0;

    do {
        arr[n] = arr[n-1] + ((pow(-1, n))*(pow(radians, 2*n)))/fact(2*n);
        // printf("%2d. %.20lf\n", n, arr[n]);  // taylorov rad
        n++;
    } while ((arr[n-1] != arr[n-2]) && ((arr[n-1] > arr[n-2] ? arr[n-1]-arr[n-2] : arr[n-2]-arr[n-1]) >= epsilon));

    printf("library cos %.20f\n", lib_cos);
    printf("mine cos    %.20f\n", arr[n-1]);
}


int hexToDec(char* hexstring) {
    int number = (int)strtol(hexstring, NULL, 16);  // https://www.tutorialspoint.com/c_standard_library/c_function_strtol.htm
    return number;
}

void intelHex(char* data) {
    int l = strlen(data), count = 0, mine = 0;
    
    char sum_check[3] = {data[l-2], data[l-1], '\0'};
    char tmp_string[3];

    for (int i = 1; i < l-2; i+=2)
    {
        tmp_string[0] = data[i];
        tmp_string[1] = data[i+1];

        count += hexToDec(tmp_string);
        // printf("%d ", hexToDec(tmp));
    }

    mine = 255 - count%256 + 1;
    printf("mine:      %X\nsum_check: %s", mine, sum_check);
}

int main() {
    // fibonaci(14400);  // uloha 1.3 (1 int argument pre funkciu fibonaci) [2b]
    // cosine(-10005, 1.0e-20);  // uloha 1.5 (1. int argument, 2. float epsilon) [4b]
    intelHex(":100030000C9445000C9445000C9445000C944500xx");  // uloha 1.6 (1. argument string) [4b]

    return 0;
}