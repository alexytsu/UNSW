#include <stdio.h>
#include "farnarkle.h"

int main(){

    //initialize the variables
    int hidden_sequence[N_TILES];
    int guess[N_TILES];
    int turn = 0;
    int previous_guesses[MAX_TURNS][N_TILES];
    int farnarkles[MAX_TURNS];
    int arkles[MAX_TURNS];
    int win = 0;

    //create and print out the hidden sequence
    create_random_tiles(hidden_sequence);
    printf("Hidden sequence is:");
    for(int i = 0; i < N_TILES; i++){
        printf(" %d", hidden_sequence[i]); 
    }
    printf("\n");

    //keep guessing until the player wins
    while(win == 0){

        //produce a new guess
        farnarkle_player(turn, previous_guesses, farnarkles, arkles, guess);

        //print the guesses produced by farnarkle_player
        printf("Player guess for turn %d:", turn+1);
        for(int i = 0; i < N_TILES; i++){
            printf(" %d", guess[i]);
        }

        //print the score produced by farnarkle_player
        printf("\n%d farnarkles %d arkles\n", count_farnarkles(hidden_sequence, guess)
                , count_arkles(hidden_sequence, guess));

        //store the guess in the array of previous guesses
        //store the farnarkle and arkle score of each guess
        for(int i = 0; i < N_TILES; i++){
            previous_guesses[turn][i] = guess[i];
        }         
        arkles[turn] = count_arkles(hidden_sequence, guess);
        farnarkles[turn] = count_farnarkles(hidden_sequence, guess);
        
        //break the while loop if farnarkle_player wins
        if(farnarkles[turn] == 4){
            win = 1;    
        }
        
        //increment the turn
        turn ++;

        //hardstop for testing purposes
        if(turn == 15){
            win = 1;
        }
    }// end of the while loop

    printf("Player took %d turns to guess code.\n", turn);
}
