#include <stdio.h>
#include "heuristics.h"

//get density returns a percentage value for how dense the image is
//ie. the more pixels in an image the higher the density
//digits with a lot of white space will have lower densities

double get_density(int height, int width, int pixels[height][width]){
    
    int area = height*width;
    int black = 0;
    for( int row = 0; row < height; row ++){
        for( int col = 0; col < width; col ++){
            black +=  pixels[row][col];
        }
    }

    double density = (double)black/area;
    return density;
}

