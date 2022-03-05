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

void colorfulNumbers() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < 51; i++)
    {
        switch (i) {
            case 0:
                SetConsoleTextAttribute(hConsole, 2); break;
            case 15:
                SetConsoleTextAttribute(hConsole, 4); break;
            case 30:
                SetConsoleTextAttribute(hConsole, 3); break;
            case 45:
                SetConsoleTextAttribute(hConsole, 6); break;
        }
        
        Sleep(100);
        printf("%03d\n", i);
    }
}

int main()
{
    colorfulNumbers();

    return 0;
}
