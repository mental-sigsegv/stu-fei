#include <stdio.h>

int main(int argc, char const *argv[])
{
    // printf("%s\n", argv[0]);
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    return 0;
}
