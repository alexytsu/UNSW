#include <stdio.h>
#include "captcha.h"

void copy_pixels(int height, int width, int pixels[height][width],
                 int start_row, int start_column, int copy_height, int copy_width,
                 int copy[copy_height][copy_width]){

    for(int row = 0; row < copy_height; row++){
        for(int col = 0; col < copy_width; col++){
           
            copy[row][col] = pixels[row+start_row][col+start_column];

        }
    }


}
