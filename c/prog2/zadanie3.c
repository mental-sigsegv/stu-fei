#include <stdio.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char line[1001] = {'0'};
    line[1001] = '\0';

    int safe_break = 0;  // !delete later
    while (1) {
        fgets(line, 1000, stdin);
        if (line[0] == '\n') {
            break;
        }
        printf("%s", line);

        if (safe_break > 20) {
            break;
        } else {
            safe_break++;
        }
    }
    
    return 0;
}
