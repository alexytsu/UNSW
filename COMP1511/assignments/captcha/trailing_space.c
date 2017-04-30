#include <stdio.h>
#include "heuristics.h"

void label_trailing_spaces(int height, int width, int pixels[height][width], int trailing_space[height]){
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
}
