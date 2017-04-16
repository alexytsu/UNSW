#include <stdio.h>
#include "captcha.h"

//get density returns 
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

