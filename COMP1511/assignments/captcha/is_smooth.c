#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "heuristics.h"

//looks for sharp jumps in the side - digit distance values
//e.g. 7 has a large jump on its left side but is smooth on its right side
int is_smooth_r(int height, int width, int pixels[height][width]){
    int trailing_space[height];
    label_trailing_spaces(height, width, pixels, trailing_space);
    for(int i = 0; i < height-1; i ++){
        int current = trailing_space[i];
        int next = trailing_space[i+1];
        //if the next line is more than 5 away from the current line,
        //it counts as a jump and the side is not smooth
        if( abs(current - next) >= 5){
            return 0;
        }
    }
    return 1;
}
 
int is_smooth_l(int height, int width, int pixels[height][width]){
    int leading_space[height];
    label_leading_spaces(height, width, pixels, leading_space);
    for(int i = 0; i < height-1; i ++){
        int current = leading_space[i];
        int next = leading_space[i+1];
        //if the next line is more than 5 away from the current line,
        //it counts as a jump and the side is not smooth
        if( abs(current - next) >= 5){
            return 0;
        }
    }
    return 1;
}
