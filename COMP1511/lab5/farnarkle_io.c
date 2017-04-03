#include <stdio.h>
#include "farnarkle.h"

int read_tiles(int tiles[N_TILES]) {
    
    for(int i = 0; i < N_TILES; i++){
<<<<<<< HEAD
        tiles[i] = MAX_TILES + 1;
        scanf("%d", &tiles[i])
                
            return 0;
        
=======
        if(scanf("%d", &tiles[i])){

        }else{
            return 0;
        }

>>>>>>> f8689045a980c58da1966e003c64fbcac536feca
    }

    return 1;
}

void print_tiles(int tiles[N_TILES]) {
    for(int i = 0; i < N_TILES; i++){
        printf("%d ", tiles[i]);
    }

    printf("\n");
}
