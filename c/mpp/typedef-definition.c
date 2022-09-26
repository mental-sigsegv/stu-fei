#include <stdio.h>
#include <string.h>

#define PI 3.14 

void foo() {
    typedef int* pntr;
}

typedef signed long slong;
typedef struct Books {
   char title[50];
   char author[50];
   char subject[100];
   int book_id;
} Book;
 
int main( ) {
   Book book;  // struct Books Book;
   return 0;
}

