#include <stdio.h>
#include <limits.h>

int main() {
    // Zadanie 1
    printf("James Bond \\ \"Agent 007\" \\ # 150%% zaruka # /\nSpol. s rucenim neomezenym");

    // Zadanie 2
    char letter;
    scanf("%c", &letter);
    printf("%c (ASCII  %d)", letter+1, letter+1);

    // Zadanie 3
    int num;
    scanf("%d", &num);
    printf("%Xh", num);
    return 0;

    // Zadanie 4
    int price;
    printf("Zadajte cenu bez dane: ");
    scanf("%d", &price);
    printf("Cena po zdaneni je %.2f", (price*1.25));

    // Zadanie 5
    int a, b;
    scanf("%d", &a);
    scanf("%d", &b);
    printf("%d", (a*b));

    // Zadanie 6
    int a = 2, b = 2, c = 1, d = 0, e = 4;
    printf("%d", (a++ / ++c * --e));  // 3
    printf("%d", (--b * c++ - a));  // -1 
    printf("%d", (-b - --c));  // -2
    printf("%d", (++a - --e));  // 0
    printf("%d", (e / --a * b++ / c++));  // 8
    printf("%d", (a %= b = d = 1 + e / 2));  // 2

    // Zadanie 7
    float num;
    printf("Float number: ");
    scanf("%f", &num);
    int result = (int)(num);
    printf("%d", result);

    // Zadanie 8
    char first, second, third;
    scanf("%c", &first);
    scanf("%c", &second);
    scanf("%c", &third);
    printf("%c%c%c", first+32, second+32, third+32);

    // Zadanie 9
    char first, second, third;
    scanf("%c", &first);
    scanf("%c", &second);
    scanf("%c", &third);
    printf("%c%c%c", third-32, second-32, first-32);

    // Zadanie 10
    unsigned int ui_num = UINT_MAX;
    signed int si_num = (ui_num-1)/2;
    printf("Max unsigned integer value: %u\n", ui_num);
    printf("Max signed integer value: %d\n", si_num);

    // Zadanie 11
    short int shrti_num = SHRT_MAX;
    long int li_num = LONG_MAX;
    printf("Max short integer value: %d\n", shrti_num);
    printf("Max long integer value: %ld", li_num);

    // Zadanie 12
    int a = 10, b = 3;
    float c = 3.0;
    printf("%d\n", (a/b));
    printf("%f\n", (a/c));
    printf("%d\n", (a%b));

    // Zadanie 13
    int a, b, c;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    printf("Average: %.2f\n", (a+b+c)/3.0);

    // Zadanie 14
    printf("\a");
}
