#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main() {
    char* a = "ahoj ako sa mas";
    char* prefix = "ak";
    char* ptr = a;
    ptr = ptr + 5;
    printf("%s\n", ptr);
    printf("%d", strncmp(ptr, prefix, strlen(prefix)));
    return 0;
}
