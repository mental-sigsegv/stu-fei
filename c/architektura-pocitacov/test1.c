#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>

static int iVysledok, iCislo;

int main() {
    asm(".intel_syntax noprefix \n"   // Prepneme z AT&T syntaxe na na Intel 
   
       "movabs eax, iCislo        \n"   // iCislo -> EAX
       "inc eax                \n"   // EAX ++ 
       "movabs iVysledok,eax     \n"   // EAX  -> iVysledok  

       ".att_syntax            \n");
    
    printf("%d\n%d", iVysledok, iCislo);
}