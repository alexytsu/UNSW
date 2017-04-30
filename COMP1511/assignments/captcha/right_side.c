#include <stdio.h>
#include "heuristics.h"

int analyse_right_side(int height, int width, int pixels[height][width]){
    
    //index 0 is top row, index height -1 is bottom row
    int trailing_space[height]; 

    //get the trailing spaces so we can analyse it with pseudo-calculus
    label_trailing_spaces(height, width, pixels, trailing_space);
    
    //do we start increasing or decreasing?
    int increasing, decreasing;
    int turning_points = 0;
    if(trailing_space[1] > trailing_space[0]){
        increasing = 1;
        decreasing = 0;
    }else{
        increasing = 0;
        decreasing = 1;
    }

    //get the number of turning points, if currently decreasing, there must
    //have been a turning point if we are now increasing
    for(int i = 0; i < height - 1; i ++){
        int current = trailing_space[i];
        int next = trailing_space[i+1];
        if(increasing){
            if(next < current){
                decreasing = 1;
                increasing = 0;
                if(current-next<4){
                    turning_points ++;
                }
            }
        }else if(decreasing){
            if(next > current){
                increasing = 1;
                decreasing = 0;
                if(next - current<4){
                    turning_points ++;
                }
            }
        }
    }
    return turning_points;
}
