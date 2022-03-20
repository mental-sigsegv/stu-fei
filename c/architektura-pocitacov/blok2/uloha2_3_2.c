#include <stdio.h>

void uloha2_3_2() {
    // Znak = (Znak XOR Cislo) XOR Cislo
    FILE *f_input = fopen("./koniec_poviedky.txt", "rb");
    FILE *f_output = fopen("./koniec_poviedky_decoded.html", "w");
    int x;

    while((x = fgetc(f_input)) != EOF) {
        x = x ^ 27;
        fprintf(f_output, "%c", x);
    }
    
    fclose(f_input);
    fclose(f_output);
}

int main() {
    uloha2_3_2();  
    return 0;
}
