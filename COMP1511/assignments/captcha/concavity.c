#include <stdio.h>
#include "heuristics.h"

int concavity(int height, int width, int pixels[height][width]){

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

    int row = 0;
    while(increasing){
        int current = trailing_space[row];
        int next = trailing_space[row+1];

        while(decreasing){
            if(next > current){
                printf("but why?");
               return 0; 
            }
            if(row >= height -2){
                break;
            }
            row ++;
        }
        if(next < current){
            decreasing = 1;
        }
        if(row >= height - 2){
            break;
        }
        row ++;
    }

    if(increasing && decreasing){
        return 1;
    }

    //concave left, threes, bottom of fives etc. 
    return 0;

}
