#include <stdio.h>

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

    for(int row = 0; row < height; row++){
        for(int col = 0; col < width; col++){
            if(pixels[row][col]){
                column_sum += col;
                n_black_pixels++;
            }

        }
    }
    double horizontal_balance = (column_sum/n_black_pixels + 0.5)/(width);
    return(horizontal_balance);


}
