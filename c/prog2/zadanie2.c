//////////////////     NEMENIT !!!      /////////////////////

//    Vo vasom rieseni vyuzite tieto tieto funkcie na
//    generovanie pseudo-nahodnych cisiel.
//1 1
//    Funkcia srnd(seed):
//       * Zavolajte 1-krat na zaciatku programu na
//       inicializaciu generovanej postupnosti cisiel.
//
//    Funkcia rnd(from, to):
//       * Sluzi na vygenerovanie dalsieho nahodneho
//       cisla z intervalu <from,to>.

#define R_MAX 2147483647 // vsetky generovane cisla su mensie ako R_MAX
static long long unsigned int SEED = 0x1; // seed generatora
void srnd(int seed) { SEED = seed; }

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}
/////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

int main() {
    int s, t, n;
    scanf("%d %d %d", &s, &t, &n);
    int tunnels[t][2];

    if (s <= 0) {
        return 1;
    } else if (n < 10 || n > 100) {
        return 1;
    } else if ((2*t) > (n/2)) {
        return 1;
    }

    for (int i = 0; i < t; i++) {
        scanf("%d %d", &tunnels[i][0], &tunnels[i][1]);
    }

    // printf("Done");
    return 0;
}

