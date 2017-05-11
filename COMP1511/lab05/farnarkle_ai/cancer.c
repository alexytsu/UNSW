#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "farnarkle.h"

// return number of farnarkles
int count_farnarkles(int sequence1[N_TILES], int sequence2[N_TILES]) {
   
    int farnarkles = 0;
    for(int i = 0; i < N_TILES; i++){
        if(sequence1[i] == sequence2[i]){
            farnarkles += 1;
        }
    }

    return farnarkles;

}

int count_arkles(int sequence1[N_TILES], int sequence2[N_TILES]) {
    int counted[N_TILES] = {0};
    int arkles = 0;

    for(int i = 0; i < N_TILES; i++){
        if(sequence1[i] == sequence2[i]){
            counted[i] = 1;
        }
    }

    for(int i = 0; i < N_TILES; i++){
        for(int j = 0; j < N_TILES; j++){
            if(sequence2[i] == sequence1[j] && counted[j] == 0 && sequence2[i] != sequence1[i]){
                counted[j] = 1;
                arkles += 1;
                break;
            }
        }
    }

    return arkles;

}

// set tiles to pseudo-random values
void create_random_tiles(int tiles[N_TILES]) {
    int i;
    // seed (initialize) pseudo-random number generate with current time in seconds
    srand(time(NULL));

    for(int i = 0; i < N_TILES; i++){
        tiles[i] = rand() % MAX_TILE + 1;
    }
}

int read_tiles(int tiles[N_TILES]) {
    for(int i = 0; i < N_TILES; i++){
        scanf("%d", &tiles[i]);
    }

    return 1;
}

void print_tiles(int tiles[N_TILES]) {
    for(int i = 0; i < N_TILES; i++){
        printf("%d ", tiles[i]);
    }

    printf("\n");
}
