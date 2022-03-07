#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>

static int num = 2;

int main() {
   asm(".intel_syntax noprefix\n"

      ".att_syntax\n");

   printf("%d", num);
   return 0;
}