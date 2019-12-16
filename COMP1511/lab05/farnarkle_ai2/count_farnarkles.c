#include <stdio.h>
#include "farnarkle.h"

// return number of farnarkles
int count_farnarkles(int sequence1[N_TILES], int sequence2[N_TILES]) {
   
    int farnarkles = 0;
    for(int i = 0; i < N_TILES; i++){
        if(sequence1[i] == sequence2[i]){
            farnarkles += 1;
        }
    }

    return farnarkles;

}
