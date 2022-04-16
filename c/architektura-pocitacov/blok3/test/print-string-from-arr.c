#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char message[4096];
    strcpy(message, "You sent the correct remainder, now reprogram your software so that your messages will be displayed on the left side of the screen and mine on the right side of the screen If you need advice check the documentation for excercise 2.5.2. MAKE SURE OF THIS - your messages must end before the half of the screen, mine start after it. No word can be divided across lines. After finishing reconnect and send me this code 333222111.\n");
    
    printf("%s", (message+10));
    return 0;
}
