#include <stdio.h>
#include "heuristics.h"

double get_vertical_symmetry(int height, int width, int pixels[height][width]){
    int overlap = 0;
    for(int row = 0; row <= height/2; row ++){
        for(int col = 0; col < width; col ++){
            if(pixels[row][col] == pixels[height-row-1][col]){
                overlap ++;
            }
        }
    }
    return (double)overlap/(width*height);
}

