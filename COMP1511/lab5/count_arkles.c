#include <stdio.h>
#include "farnarkle.h"

// return number of arkles
int count_arkles(int sequence1[N_TILES], int sequence2[N_TILES]) {
    int counted[N_TILES] = {0};
    int arkles = 0;
    for(int i = 0; i < N_TILES; i++){
        for(int j = 0; j < N_TILES; j++){
            if(sequence2[i] == sequence1[j] && counted[j] == 0 && sequence2[i] != sequence1[i]){
                counted[j] = 1;
                arkles += 1;
                break;
            }
        }
    }

    return arkles;

}
