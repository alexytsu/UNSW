#include <stdio.h>
#include "farnarkle.h"

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
