#include <stdio.h>
#include "farnarkle.h"

// an automated farnarkle_player
// given all previous guesses and their farnarkles and arkle counts
// make a new guess
//
// inputs:
// turn - which turn this is
// previous_guesses contains the turn - 1 previous_guesses
// farnarkles[i] contains the number of farnarkles for previous_guess[i]
// arkles[i] contains the number of arkles for previous_guess[i]
//
// output:
// guess - the next guess

void farnarkle_player(int turn, 
    int previous_guesses[MAX_TURNS][N_TILES], 
    int farnarkles[MAX_TURNS], 
    int arkles[MAX_TURNS], 
    int guess[N_TILES],
    int educatedguess) {

    for(int i = 0; i < N_TILES; i++){
        guess[i] = turn+1;
    }
   
    //now used has the four numbers but in the wrong sequence
    if(turn>=8){

        for(int i = 0; i<N_TILES; i++){
            for(int j = 0; j<N_TILES; j++){
                if(i == j){
                    guess[j] = used[i];
                }else{
                    guess[j] = 0;
                }
                }
            }
    }
    for (int i = 0; i < N_TILES; i++){
        printf("%d", guess[i]);
    }
}

void getUsed(int used[N_TILES],
        int farnarkles[MAX_TURNS],
        int turn){

    //farnarkle[i] is the number of times (i+1) occurs 
    int place = 0;
    for (int i = 0; i < 8; i++){
        while(farnarkles[i] > 0){
            used[place] = i+1;
            place ++;
            farnarkles[i]  -= 1;
        }
    }
}

