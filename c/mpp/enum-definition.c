#include <stdio.h>

enum designFlags {
	ITALICS = 1,
	BOLD = 2,
	UNDERLINE = 4
} button;


int main()
{
    // In binary
    // ITALICS =    00000001
    // BOLD =       00000010
    // UNDERLINE =  00000100 

    int myDesign = BOLD | UNDERLINE; 

    return 0;
}


