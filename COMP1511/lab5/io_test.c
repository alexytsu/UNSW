#include <stdio.h>
#include "farnarkle.h"

int main(void) {
    int tiles[N_TILES];

    printf("Enter sequence: ");
    if (read_tiles(tiles) == 1) {
        printf("Sequence read was: ");
        print_tiles(tiles);
    } else {
        printf("Could not read tiles\n");
    }

}
