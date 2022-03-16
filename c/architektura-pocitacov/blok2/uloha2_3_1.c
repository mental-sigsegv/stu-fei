#include <stdio.h>

int main() {
    FILE *f = fopen("./input.html", "r");
    int x;

    while((x = fgetc(f)) != EOF) {
        
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

        printf("%d ", x);
    }
    fclose(f);
    return 0;
}
