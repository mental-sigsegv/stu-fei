#include <stdio.h>
#include <string.h>


char* lemon[128] = {"\e[0;32m              N0x0                                              ", "\e[0;32m             W0loK                                              ", "\e[0;32m            NxcOW                                              ", "\e[0;32m            KooK                                               ", "\e[0;32m             0coK                                               ", "\e[0;32m             KolxX           WX00OkxdddxO0XW                    ", "\e[0;32m             W0dodOKW    NKOxoc:;;;;;;,,,;:ok0N                 ", "\e[0;32m              WOdOKOkkkkxo::::::::;,,,,,,,,,,;cdOXW             ", "\e[0;33m               XdxN \e[0;32mNKKx:;;;,,;;;::;:;;,,,,,,,,,,:oOX           ", "\e[0;33m             WN0ddON   \e[0;32mXd;;;;;,,,,,;;;;;;;;,,,,,,,,,:d0W        ", "\e[0;33m           WXOxdxxdx0N  \e[0;32mXd:;::;;;;;;;;,,;;:::;;,,,,,,,:d0W      ", "\e[0;33m        WXKOxxxxxxdddkKN  \e[0;32mXxc::::::;;;::;;,;;:;;;;;,,,,,,:xX     ", "\e[0;33m      NKOxxxxkkkkxxxxxxkOKX  \e[0;32m0dccccc:::::::;;;:;;;;::::;;;;:oX    ", "\e[0;33m    WKkxxkkkOOkkkkkkxxxxxxk0   \e[0;32mX0dllccccc::cc::::::;;;:c::::::dN   ", "\e[0;33m   XOxxkkOOOOOOOOOkkkkxxxxddkX   \e[0;32mNKOkdllllccccc::::::;;;:ccc::cOW  ", "\e[0;33m  XkxkkkOO0\e[0;37mKKK\e[0;33m00OOOkkkkxxxddoxK       \e[0;32mWNXKOkxxdoollcclllcclloolccoK  ", "\e[0;33m XkxxkOOO0\e[0;37mKXXK\e[0;33m0K0OOOkkkxxxxddoxX            \e[0;32mWWNXKK00OOO00KXXXKOxoxX ", "\e[0;33mW0dxxkOO00\e[0;37mKXXK\e[0;33m000OOkkkxxxxxdooo0W                 \e[0;32mKK00OOO00KXX       ", "\e[0;33mXkdxxkO000\e[0;37mKKKK\e[0;33m000OOkkkxxddddoolkNW                    \e[0;32mWN00N      ", "\e[0;33mKddxxkkOO0\e[0;37mKKK\e[0;33m00OOOkkkxxxddooolckXN                              ", "\e[0;33mKdddxxkkkOOOOOOOkkkxxxxxddoollckNW                              ", "\e[0;33mXxooddxxxkkkkkkkkxxxxdddddollccOW                               ", "\e[0;33mWOooooddxxxxxxkxxxxddddooolcccdX                                ", "\e[0;33m Nkolooooddddddddddoooollccccl0W                                ", "\e[0;33m  NOollllooooooooollllccccccdKW                                 ", "\e[0;33m   WXkocclllllllllccccccclx0W                                   ", "\e[0;33m      N0kocc:ccccccc:cox0N                                      ", "\e[0;33m         N0klcccccccoON                                         ", "\e[0;33m            NOdllodON                                           ", "\e[0;33m              WXXXW\e[0m                                             ", "                                                                "};

void print_lemon() {
    for (int i = 0; i < 31; i++) {
        printf("%s\n", lemon[i]);
    }
}

int main() {
    print_lemon();
    return 0;
}
