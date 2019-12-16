#include <stdlib.h>
#include <time.h>
#include "farnarkle.h"

// set tiles to pseudo-random values
void create_random_tiles(int tiles[N_TILES]) {
    int i;
    // seed (initialize) pseudo-random number generate with current time in seconds
    srand(time(NULL));

    for(int i = 0; i < N_TILES; i++){
        tiles[i] = rand() % MAX_TILE + 1;
    }
}
