#include <stdio.h>
#include "heuristics.h"

int analyse_right_side(int height, int width, int pixels[height][width]){
    
    
    //index 0 is top row, index height -1 is bottom row
    int trailing_space[height]; 

    //plug two high holes
    for(int col = 0; col < width; col ++){
        for(int row = 0; row < height; row ++){
            if(pixels[row][col]){
                //check not out of bounds
                //i
                if(row < 4){
                    if(pixels[4][col]){
                        pixels[row][col] = 1;
                    }
                }
                if(row + 4 < height){
                    if(pixels[row+4][col]){
                        pixels[row+1][col] = 1;
                        pixels[row+2][col] = 1;
                        pixels[row+3][col] = 1;
                    }
                }
            }
        }
    }

    for(int row = 0; row < height; row ++){
        for(int col = 0; col < width; col ++){
            if(pixels[height - 1 - row][width - 1 - col]){
                trailing_space[row] = col;
                break;
            }
        }
    }

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
