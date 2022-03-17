#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define R_MAX 2147483647 // vsetky generovane cisla su mensie ako R_MAX
static long long unsigned int SEED = 0x1; // seed generatora
void srnd(int seed) { SEED = seed; }

int rnd(int from, int to) { 
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}

int checkenter(int t, int enter[]) {
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < i; j++) {
            if (enter[i] == enter[j]) {
                return 1;
            }
        }
    }
    return 0;
}

int checkexitandenter(int enter[], int exit[], int t){
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++) {
            if (exit[i] == enter[j]) {
                return 1;
            }
        }
    }
    return 0;
}

void bubble(int enter[], int exit[], int t) {
    for (int step = 0; step < t - 1; step++) {
        for (int i = 0; i < t - step - 1; i++) {
            if (enter[i] > enter[i + 1]) {
                int temp = enter[i];
                int temp2 = exit[i];
                enter[i] = enter[i + 1];
                exit[i] = exit[i + 1];
                enter[i + 1] = temp;
                exit[i + 1] = temp2;
            }
        }
    }
}

int max(int r1, int r2) {
    if (r1 > r2) {
        return r1;
    }
    else {
        return r2;
    }
}

int main() {
    int s, t, n, nmin = 10, nmax = 100;
    scanf("%d %d %d", &s, &t, &n);
    srnd(s);
    int enter[t], exit[t]; 

    for (int i = 0; i < t; i++)
    {
        enter[t] = 0; 
        exit[t] = 0; 
    }
    

    if ((s > 0) && (nmax >= n) && (n >= nmin) && ((t * 2) <= (n/2))) {
        for (int i = 0; i < t; i++) {
            scanf("%d %d", &enter[i], &exit[i]);
            if ((enter[i] == 0) || (exit[i] == 0) || (enter[i] == (n - 1)) || (exit[i] == (n - 1)) || (enter[i] < 0) || (exit[i] < 0) || (enter[i] > (n - 1)) || (exit[i] > (n - 1))) {
                return 2;
            }
        }
        if (((checkexitandenter(enter, exit, t)) == 1)  || ((checkenter(t, enter) == 1))) {
            return 2;
        }
    }
    else
    {
        return 1;
    }
    
    bubble(enter,exit,t);
    printf("TUNNELS:");
    for (int i = 0; i < t; ++i) {
        printf(" [%d,%d]", enter[i], exit[i]);
    }
    
    printf("\n");

    int path[n], r1, r2;
    int round = 0, player_num, pos_before, pos_after;
    int hrac1 = -1, hrac2 = -1;

    int tmp, checkS, checkT, checkE;

    for (int i = 0; i < n; i++) {
        path[i] = 0;
    }
    

    for (int i = 0; ((hrac1 < n) && (hrac2 < n)); i++) {
        checkS = 0;
        checkT = 0;
        checkE = 0;

        if ((i % 2) == 0) {  // hrac1
            player_num = 1;
            pos_before = hrac1;
            r1 = rnd(1, 6);
            r2 = rnd(1, 6);
            
            if (hrac1 == -1) {
                if ((r1 + r2) > 7) {
                hrac1 = (r1 + r2 - 7);
                }
            }

            else if ((hrac1 >= 0) && (hrac2 >=0) && ( ((r1 + r2) == 12) || ((r1 + r2) == 2) )) {
                if ((hrac1 > hrac2) && ((r1 + r2) == 12)){
                    hrac1 = hrac1 + max(r1,r2);
                }
                
                if ((hrac1 < hrac2) && ((r1 + r2) == 12)) {
                    tmp = hrac1;
                    hrac1 = hrac2;
                    hrac2 = tmp;
                    checkS = 1;
                    path[hrac2]++;
                }

                if ((hrac1 < hrac2) && ((r1 + r2) == 2)){
                    hrac1 = hrac1 + max(r1,r2);
                }

                if ((hrac1 > hrac2) && ((r1 + r2) == 2)) {
                    tmp = hrac1;
                    hrac1 = hrac2;
                    hrac2 = tmp;
                    checkS = 1;
                    path[hrac2]++;
                }
            }

            else {
                hrac1 = hrac1 + max(r1, r2);
            }

            for (int j = 0; j < t; j++) {
                if (hrac1 == enter[j]) {
                    hrac1 = exit[j];
                    checkT = 1;
                } 
            }

            round++;
            pos_after = hrac1;

            if ((pos_after >= 0) && (pos_after < n)) {
                path[pos_after]++; 
            }

            if ((hrac1 == hrac2) && (hrac1 >= 0)) {
                hrac2 = -1;
                checkE = 1;
            }
            
        }

        else {   //hrac2
            player_num = 2;
            pos_before = hrac2;
            r1 = rnd(1, 6);
            r2 = rnd(1, 6);

            if (hrac2 == -1) {
                if ((r1 + r2) > 7) {
                hrac2 = (r1 + r2 - 7);
                }
            }

            else if ((hrac1 >= 0) && (hrac2 >=0) && ( ((r1 + r2) == 12) || ((r1 + r2) == 2) )) {
                if ((hrac1 < hrac2) && ((r1 + r2) == 12)){
                    hrac2 = hrac2 + max(r1,r2);
                }
                
                if ((hrac1 > hrac2) && ((r1 + r2) == 12)) {
                    tmp = hrac1;
                    hrac1 = hrac2;
                    hrac2 = tmp;
                    checkS = 1;
                    path[hrac1]++;
                }
                
                if ((hrac1 > hrac2) && ((r1 + r2) == 2)){
                    hrac2 = hrac2 + max(r1,r2);
                }

                if ((hrac1 < hrac2) && ((r1 + r2) == 2)) {
                    tmp = hrac1;
                    hrac1 = hrac2;
                    hrac2 = tmp;
                    checkS = 1;
                    path[hrac1]++;
                }
            }
            
            else {
                hrac2 = hrac2 + max(r1, r2);
            }

            for (int j = 0; j < t; j++) {
                if (hrac2 == enter[j]) {
                    hrac2 = exit[j];
                    checkT = 1;
                } 
            }

            round++;
            pos_after = hrac2;

            if ((pos_after >= 0) && (pos_after < n)) {
                path[pos_after]++; 
            }

            if ((hrac1 == hrac2) && (hrac1 >= 0)) {
                hrac1 = -1;
                checkE = 1;
            }
            
        }

        printf("[%d,%d] [%d] [%d,%d] [%d]", round, player_num, pos_before, r1, r2, pos_after);
        
        if (checkS == 1) {
            printf(" S");
        }

        if (checkT == 1) {
            printf(" T");
        }
        
        if (checkE == 1) {
            printf(" E");
        }

        printf("\n");
        
       

        if (hrac1 >= n) {
            printf("WINNER: 1\n");
        }

        if (hrac2 >= n) {
            printf("WINNER: 2\n");
        }      
    }

    printf("VISITS:");

    for (int k = 0; k < n; k++) {
        printf(" %d", path[k]);
    }

    return 0;
}