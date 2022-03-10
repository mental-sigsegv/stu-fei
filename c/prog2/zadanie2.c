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
    int s, t, n, enter, exit;
    scanf("%d %d %d", &s, &t, &n);
    srnd(s);
    
    if ((s <= 0) || ((n < 10) || (n > 100)) || ((2*t) > (n/2))) {
        return 1;
    }

    int tunnels[t][2], race_arr[n];

    // Fill race arrays with zero values
    for (int i = 0; i < n; i++) {
        race_arr[i] = 0;
    }
    
    // Load tunnels
    for (int i = 0; i < t; i++) {
        scanf("%d %d", &tunnels[i][0], &tunnels[i][1]);
    }

    // Check for tunnels && assign into array
    for (int i = 0; i < t; i++) {
        enter = tunnels[i][0];
        exit = tunnels[i][1];

        if ((enter <= 0) || (exit >= n-1) || (exit == enter) || (race_arr[enter] != 0)) {
            return 2;
        }

        race_arr[enter] = exit;
    }

    // Check if there exist exti on enter
    for (int i = 0; i < t; i++) {
        enter = tunnels[i][0];
        exit = tunnels[i][1];

        if (race_arr[exit] != 0) {
            return 2;
        }
    }
   
    // Print tunnels
    printf("TUNNELS:");
    for (int i = 0; i < n; i++) {
        if (race_arr[i] != 0) {
            printf(" [%d,%d]", i, race_arr[i]);
        }
    }

    // Print array
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", race_arr[i]);
    }
    printf("\n");

    // Game
    int r1, r2, player1 = -1, player2 = -1, last1, last2;

    for (int i = 1; i <= 17; i++) {
        if (i%2 == 1) {
            r1 = rnd(1, 6); r2 = rnd(1, 6);
            last1 = player1;

            if ((player1 == -1) || ((r1+r2) > 7)) {
                player1 = r1+r2-7;
            } else {
                player1 += r1+r2;
            }

            printf("[%d,%d] [%d] [%d,%d] [%d]\n", i, i%2, last1, r1, r2, player1);
        } else {
            r1 = rnd(1, 6); r2 = rnd(1, 6);
            printf("2ndplayer\n");
            
        }
    }
    
    // printf("Done");
    return 0;
}

