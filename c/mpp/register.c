#include<stdio.h>
  
// register int x = 10;
int main()
{
    register int i = 10;
    int *a = &i;
    printf("%d", *a);

    // register static int* a = &i;

    return 0;
}
