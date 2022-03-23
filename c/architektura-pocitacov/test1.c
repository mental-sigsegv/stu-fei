#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>

void print_values(char values[][]) {
   for (int i = 0; i < 3; i++) {
      printf("%c\n", *values[i]);
   }
}

int main() {
   char* arr[3][10] = {"asdasd", "asd", "sd"};
   print_values(&arr);
   return 0;
}