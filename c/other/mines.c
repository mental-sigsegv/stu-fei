#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

/* 
GREEN  = 2
BLUE   = 3
RED    = 4
PURPLE = 5
YELLOW = 6
WHITE  = 7
*/

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < 11; i++)
    {
        switch (i) {
            case 0:
                SetConsoleTextAttribute(hConsole, 2); break;
            case 3:
                SetConsoleTextAttribute(hConsole, 4); break;
            case 8:
                SetConsoleTextAttribute(hConsole, 3); break;
        }
        
        printf("%03d\n", i);
    }

    getchar();
    return 0;
}
