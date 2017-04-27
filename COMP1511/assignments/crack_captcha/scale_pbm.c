#include <stdio.h>
#include <math.h>
#include "captcha.h"

void downscale(int height, int width, int pixels[height][width], int nheight, int nwidth, int npixels[nheight][nwidth]){

    //create a 1D holding the bounded digit
    int pixel_copy[height*width];
    for(int i = 0; i < height; i ++){
        for(int j = 0; j < width; j ++){
            pixel_copy[i*width+j] = pixels[i][j];
        }
    }

    //keep as a double until needed to maintain precision 
    double height_ratio = height/(double)nheight;
    double width_ratio = width/(double)nwidth;
    double px, py;
    for(int row = 0; row < nheight; row ++){
        for(int col = 0; col < nwidth; col ++){     
            px = floor(col*width_ratio);
            py = floor(row*height_ratio);
            npixels[row][col] = pixel_copy[(int)((py*width)+px)]; 
        }
    }
}
