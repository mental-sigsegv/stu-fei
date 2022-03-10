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
#include <string.h>

struct Player {
    int pos_before;
    int pos_after;
    int num;
};

int round_num = 1;

void throw(struct Player *player, struct Player *oponnent, int race_size, int *winner, int arr[], int race_path[]) {
    int r1 = rnd(1, 6), r2 = rnd(1, 6);
    char special[6];
    for (int i=0; i<6; i++) {
        special[i] = '\0';
    }

     player->pos_before = player->pos_after;

    // Move
    if (player->pos_after == -1) {
        if (r1+r2 > 7) {
            player->pos_after = r1+r2-7;
        }
    } else if ((player->pos_after + (r1 > r2 ? r1 : r2)) >= race_size) {
        // taking care of special moves (S, T, E) if car is able to finish within max(r1, r2) move
        player->pos_after += (r1 >= r2 ? r1 : r2);
        *winner = player->num;
    } else if (((player->pos_after != -1) && (oponnent->pos_after != -1)) && (((r1+r2 == 12) && (player->pos_after < oponnent->pos_after)) || ((r1+r2 == 2) && (player->pos_after > oponnent->pos_after)))) {
        player->pos_after = oponnent->pos_after;
        oponnent->pos_after = player->pos_before;
        arr[player->pos_before] += 1;
        strcat(special, " S");
    } else {
        player->pos_after += (r1 > r2 ? r1 : r2);
    }

    // Tunnel / kick
    if ((*winner == -1) && (player->pos_after > -1) && (race_path[player->pos_after] != 0)) {
        // arr[player->pos_after] += 1;
        player->pos_after = race_path[player->pos_after];
        strcat(special, " T");
    } 
    
    if ((*winner == -1) && (player->pos_after == oponnent->pos_after) && ((player->pos_after != -1) && (oponnent->pos_after != -1))) {
        oponnent->pos_after = -1;
        oponnent->pos_before = -1;
        strcat(special, " E");
    }

    arr[player->pos_after] += 1;

    printf("[%d,%d] [%d] [%d,%d] [%d]%s\n", round_num, player->num, player->pos_before, r1, r2, player->pos_after, special);
    
    if (player->pos_after >= race_size) {
        *winner = player->num;
        return;
    }
    round_num++;
}

int main() {
    struct Player player1;
    player1.num = 1;
    player1.pos_after = -1;
    player1.pos_before = -1;


    struct Player player2;
    player2.num = 2;
    player2.pos_after = -1;
    player2.pos_before = -1;

    int s, t, n, enter, exit, winner = -1;
    scanf("%d %d %d", &s, &t, &n);
    srnd(s);
    
    if ((s <= 0) || ((n < 10) || (n > 100)) || ((2*t) > (n/2))) {
        return 1;
    }

    int tunnels[t][2], race_arr[n], visited[n];

    // Fill race arrays with zero values
    for (int i = 0; i < n; i++) {
        race_arr[i] = 0;
        visited[i] = 0;
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

    // Check if there is exit on enter
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
    printf("\n");

    // Print array  // TODO: REMOVE
    // printf("\n");
    // for (int i = 0; i < n; i++) {
    //     printf("%d ", race_arr[i]);
    // }
    // printf("\n");

    // Game
    while (winner == -1) {
        if (round_num%2 == 1) {
            throw(&player1, &player2, n, &winner, visited, race_arr);
        } else {
            throw(&player2, &player1, n, &winner, visited, race_arr);
        }

        if (round_num > 400) {  // TODO: remove error protection
            printf("\n ERROR");
            break;
        }
    }

    // Winner
    printf("WINNER: %d\n", winner);

    // Visited
    printf("VISITS:");
    for (int i = 0; i < n; i++)
    {
        printf(" %d", visited[i]);
    }
    
    // printf("Done");
    return 0;
}

