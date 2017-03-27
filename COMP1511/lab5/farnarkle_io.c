#include <stdio.h>
#include "farnarkle.h"

// read N_TILES tiles into array tiles
// return 1 if successful, 0 otherwise
int read_tiles(int tiles[N_TILES]) {

    for(int i = 0; i < N_TILES; i++){
        scanf("%d", &tiles[i]);
    }
    return 1;

}

// print tiles on a single line
void print_tiles(int tiles[N_TILES]) {
    
    for(int i = 0; i < N_TILES; i++){
        printf("%d ", tiles[i]);
    }
    printf("\n");
}
