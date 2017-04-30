#include <stdio.h>
#include "heuristics.h"

int analyse_right_side(int height, int width, int pixels[height][width]){
    
    
    //index 0 is top row, index height -1 is bottom row
    int trailing_space[height]; 

    label_trailing_spaces(height, width, pixels, trailing_space);

    int increasing, decreasing;
    int turning_points = 0;
    if(trailing_space[1] > trailing_space[0]){
        increasing = 1;
        decreasing = 0;
    }else{
        increasing = 0;
        decreasing = 1;
    }

    for(int i = 0; i < height - 1; i ++){
        int current = trailing_space[i];
        int next = trailing_space[i+1];
//TODO better jump detection
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
