#include <stdio.h>
#include "farnarkle.h"

int main(){
    int hidden_sequence[N_TILES];
    int guess[N_TILES];

    create_random_tiles(hidden_sequence);
    printf("Hidden guess is:");
    for(int i = 0; i < N_TILES; i++){
        printf(" %d", hidden_sequence[i]); 
    }
    printf("\n");

    int turn = 0;
    int previous_guesses[MAX_TURNS][N_TILES];
    int farnarkles[MAX_TURNS];
    int arkles[MAX_TURNS];
    int win = 0;
    int used[N_TILES];

    while(win == 0){

        farnarkle_player(turn, previous_guesses, farnarkles, arkles, guess, 0);

        printf("Player guess for turn %d", turn);
        for(int i = 0; i < N_TILES; i++){
            printf(" %d", guess[i]);
        }
        printf("\n%d farnarkles %d arkles\n", count_farnarkles(hidden_sequence, guess)
                , count_arkles(hidden_sequence, guess));

        farnarkles[turn] = count_farnarkles(hidden_sequence, guess);
        arkles[turn] = count_arkles(hidden_sequence, guess);

        for(int i = 0; i < N_TILES; i++){
            previous_guesses[turn][i] = guess[i];
        }         

        turn ++;
        if(turn == 8){
            win = 1;
        }
    }

    //test the mechanics of the functions
    printf("guesses: \n");
    for(int i = 0; i<turn; i++){
        for(int j = 0; j<N_TILES; j++){
            printf("%d ", previous_guesses[i][j]);
        }
        printf("arkles: %d ", arkles[i]);
        printf("farnakles: %d", farnarkles[i]);
        printf("\n");
    }


    getUsed(used, farnarkles, turn);
    for(int i = 0; i < 16; i++){
        farnarkle_player(turn, previous_guesses, farnarkles, arkles, guess, i);
    }
}
