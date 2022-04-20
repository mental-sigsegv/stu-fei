// Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>  // For terminal
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>

char server_reply[4096];

void decipher_caesar(char* cipher, int rotate) {
    char letter;
    for (int l=0; l<(int)strlen(cipher); l++) {
        letter = cipher[l];
        if (('a' <= letter) && (letter <= 'z')) {
            server_reply[l] = ((letter + rotate)%'a')%26+'a';
        } else if (('A' <= letter) && (letter <= 'Z')) {
            server_reply[l] = ((letter + rotate)%'A')%26+'A';
        } else {
            server_reply[l] = cipher[l];
        }
    }
}

int main() {
    char* textCipher = "abcdefgh--xyz|ABCDEFGH--XYZ";
    decipher_caesar(textCipher, -5);

    printf("%s\n%s\n", textCipher, server_reply);
    return 0;
}
