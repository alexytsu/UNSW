#include <stdio.h>
#include "heuristics.h"

int get_vertical_intercepts(int height, int width, int pixels[height][width]){
    int intercepts = 0;
    int currently_intercepting = 0;
    int max_intercepts = 0;
    int number_of_max_intercepts = 0;
    for(int col = 0; col < width; col ++){
        intercepts = 0;
        currently_intercepting = 0;
       for(int row = 0; row < height; row ++){
            if(pixels[row][col]){
                if(!currently_intercepting){
                    currently_intercepting = 1;
                    intercepts ++;
                }
            }else{
                if(currently_intercepting){
                    currently_intercepting = 0;
                }
            }
       }
       if(intercepts > max_intercepts){
            max_intercepts = intercepts;
       }else if(intercepts == max_intercepts){
            number_of_max_intercepts ++;
       }
    }
    
    if(number_of_max_intercepts <= 3){
        max_intercepts --;
    }

    //printf("%d", max_intercepts);    
    return max_intercepts;
}

