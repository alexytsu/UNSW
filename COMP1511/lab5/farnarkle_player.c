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

void farnarkle_player(int turn, int previous_guesses[MAX_TURNS][N_TILES], int farnarkles[MAX_TURNS], int arkles[MAX_TURNS], int guess[N_TILES]) {
    
    //previous_guesses, farnarkles, arkles will be populated till turn - 1
    //ie on turn '1' (the second turn), only index 0 will be populated

    if(turn < 8){
        for(int i = 0; i < N_TILES; i++){
            guess[i] = turn + 1;
        }
    }

    //gets the 4 digits in the sequence
    int used[N_TILES];
    if(turn >= 8){
        //find the digits in the sequence
        int digit = 0;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j<farnarkles[i]; j++){
                used[digit] = i+1;
                digit ++;
            }
        }
    }

    if(turn>=8 && turn <12){ 
        for(int i = 0; i < N_TILES; i++){
            if(i == (turn-8)%4){
                guess[i] = used[0];    
            }else{
                guess[i] = 0;
            }
        }
    }else if(turn>=12 && turn <16){

        for(int i = 0; i < N_TILES; i++){
            if(i == (turn-8)%4){
                guess[i] = used[1];    
            }else{
                guess[i] = 0;
            }
        }
    }else if(turn>=16 && turn <20){

        for(int i = 0; i < N_TILES; i++){
            if(i == (turn-8)%4){
                guess[i] = used[2];    
            }else{
                guess[i] = 0;
            }
        }
    }else if(turn>=20 && turn <24){

        for(int i = 0; i < N_TILES; i++){
            if(i == (turn-8)%4){
                guess[i] = used[3];    
            }else{
                guess[i] = 0;
            }
        }
    }
   
    else if(turn == 25){
        //look through the guesses indexed at 8-23 and determine the final guess 
        for(int i = 8; i < 23; i++){
            //get the index of used
            int position = i%4;
            int index = (i-8)/4;
            if(farnarkles[i]){
                guess[position] = used[index] ;
            }
        }
    }
}
