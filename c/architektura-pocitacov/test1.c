#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>


int main() {
   char name[] = "Name";
   char arr[] = "Martin";
   
   printf("|%-*s|%*s|", 10, name, 20, arr);

   return 0;
}