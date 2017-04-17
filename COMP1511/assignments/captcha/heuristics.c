#include <stdio.h>
#include "captcha.h"

double get_horizontal_balance(int height, int width, int pixels[height][width]){

    /*
    horizontal_balance = (column_sum/n_black_pixels + 0.5)/width
        where
           column_sum = sum of the column indices of all black pixels
           n_black_pixels = number of black pixels
           width = image width
    */
    double n_black_pixels = 0;
    double column_sum = 0;

    for(int row = 0; row < height; row ++){
        for(int col = 0; col < width; col ++){
            if(pixels[row][col]){
                column_sum += col;
                n_black_pixels ++;
            }
        }
    }
    double horizontal_balance = (column_sum/n_black_pixels + 0.5)/(width);
    return horizontal_balance;
}

double get_vertical_balance(int height, int width, int pixels[height][width]){
    /*
    vertical_balance = (row_sum/n_black_pixels + 0.5)/height)
        where
           row_sum = sum of the row indices of all black pixels
           n_black_pixels = number of black pixels
           height = image height
    */

    double n_black_pixels = 0;
    double row_sum = 0;

    for(int row = 0; row < height; row ++){
        for(int col = 0; col < width; col ++){
            if(pixels[row][col]){
                row_sum += row;
                n_black_pixels ++;
            }
        }
    }
    double vertical_balance = (row_sum/n_black_pixels + 0.5)/(height);
    return vertical_balance;
}

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

