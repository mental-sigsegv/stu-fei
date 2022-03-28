#include <stdio.h>

int main( void )
{
    char s[20] = "AAAAAAAAAAAAAAAAAA";

    char *p = s;

    
    p = p + 10;
    *p = 'X';

    printf("%s", s);

    return 0;
}