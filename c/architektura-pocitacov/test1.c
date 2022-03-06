#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>

int main() {
   asm(".intel_syntax noprefix \n"
      "movabs eax, x\n"
      ".att_syntax\n");
}