#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main () {
    char message[4096];
    strcpy(message, "You sent the correct remainder, now reprogram your software so that your messages will be displayed on the left side of the screen and mine on the right side of the screen If you need advice check the documentation for excercise 2.5.2. MAKE SURE OF THIS - your messages must end before the half of the screen, mine start after it. No word can be divided across lines. After finishing reconnect and send me this code 333222111.");

    
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int sizeOfTerminal = w.ws_col;

    int letter=0;
    int lastLetter=-1;
    int spaceIndex=0;
    while (letter <= (int)strlen(message)) {
        for (int i=sizeOfTerminal/2 + letter; i >= letter; i--) {
            if ((message[i] == ' ') || (message[i] == '\0')) {
                spaceIndex = i;
                break;
            }
        }
        printf("%*.*s\n", sizeOfTerminal, spaceIndex-letter, message+letter);
        if (lastLetter == letter) {
            break;
        }
        lastLetter = letter;
        letter = spaceIndex;
        // printf("%d\n", letter);
    }

    
    return 0;  // make sure your main returns int
}