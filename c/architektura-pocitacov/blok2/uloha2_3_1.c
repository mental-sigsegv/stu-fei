#include <stdio.h>

int main() {
    FILE *f_input = fopen("./input.html", "r");
    FILE *f_output = fopen("./output.html", "w");
    int x;

    while((x = fgetc(f_input)) != EOF) {
        
        switch(x) {
            case 165: 
                x = 188; break;
            case 169:
                x = 138; break;
            case 171:
                x = 141; break;
            case 174:
                x = 142; break;
            case 181:
                x = 190; break;
            case 185:
                x = 154; break;
            case 187:
                x = 157; break;
            case 190:
                x = 158; break;
        }
        fprintf(f_output, "%c", x);
    }
    
    fclose(f_input);
    fclose(f_output);
    return 0;
}
