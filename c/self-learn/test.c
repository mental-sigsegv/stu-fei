#include <stdio.h>


char* get_path() {
    return "this-is-path";
}

int main()
{
    printf("%s", get_path());
    return 0;
}
