#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heuristics.h"

int is_smooth_r(int height, int width, int pixels[height][width]){

    int trailing_space[height];
    label_trailing_spaces(height, width, pixels, trailing_space);

    int increasing, decreasing;
    if(trailing_space[1] >= trailing_space[0]){
        increasing = 1;
        decreasing = 0;
    }else{
        increasing = 0;
        decreasing = 1;
    }

    for(int i = 0; i < height-1; i ++){
        int current = trailing_space[i];
        int next = trailing_space[i+1];
        if( abs(current - next) >= 5){
            return 0;
        }
    }
    
    return 1;
}
