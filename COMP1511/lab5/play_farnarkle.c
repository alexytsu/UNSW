#include <stdio.h>
#include "farnarkle.h"

int main(void) {
    int hidden_sequence[N_TILES];
    int guess[N_TILES];

    create_random_tiles(hidden_sequence);
    for(int i = 0; i < N_TILES; i++){
        printf("%d\n", hidden_sequence[i]);
    }

    int win = 0;
    int turn = 1;
    while(!win){
        printf("Enter guess for turn %d: ", turn);
        if (read_tiles(guess) != 1){
            printf("Could not read guess\n");
            return 1;
        }
        turn ++;
        printf("%d farnarkles ", count_farnarkles(hidden_sequence, guess));
        printf("%d arkles\n", count_arkles(hidden_sequence, guess));
        if(count_farnarkles(hidden_sequence, guess) == 4){
            win = 1;
            printf("You win\n");
        }
    }

    return 0;
}
