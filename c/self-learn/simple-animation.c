#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void load() {
    srand(time(0));
    printf("Wait for application to load...\n");
    for (int i = 0; i<=100; i += rand()%12) {
        printf("\rLoading: %2d%%", i);
        fflush(stdout);
        sleep(1);
    }
    printf("\nDone!\n");
}

int main()
{
    load();
    // getchar();
    return 0;
}
