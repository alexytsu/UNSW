#include <stdio.h>
#include "image.h"

//check a column, if it is empty return 1, else return 0
int line_empty(int height, int width, int pixels[height][width], int col);
int next_empty_column(int height, int width, int pixels[height][width], int cur_col);

//divides captchas into 4 images, separating the digits
void divide_captcha(int height, int width, int pixels[height][width], int
        dividing_columns[3]){
    
    int cur_col = 0;
    for(int divider = 0; divider < 3; divider ++){
        //returning and running with cur_col again allows us to start off from 
        //where we left off at the end of the last digit
        dividing_columns[divider] = next_empty_column(height, width, pixels, cur_col);
        cur_col = dividing_columns[divider];
    }
}

//whilst we are currently in a digit, we look for the next empty column
int next_empty_column(int height, int width, int pixels[height][width], int cur_col){
    //whilst the line is empty proceed until the we have found a digit
    while(line_empty(height, width, pixels, cur_col)){
        cur_col ++;
    }
    //now that we are at a digit, the next empty line is a dividing line
    while(!(line_empty(height, width, pixels, cur_col))){
        cur_col ++;
    }
    return cur_col;
}

//check a column, if it is empty return 1, else return 0
int line_empty(int height, int width, int pixels[height][width], int col){
    for(int row = 0; row < height; row ++){
        if(pixels[row][col]){
            return 0;
        }
    }
    return 1;
}
