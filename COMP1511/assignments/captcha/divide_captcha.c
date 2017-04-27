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
        dividing_columns[divider] = next_empty_column(height, width, pixels, cur_col);
        cur_col = dividing_columns[divider];
    }
}

int next_empty_column(int height, int width, int pixels[height][width], int cur_col){
    while(line_empty(height, width, pixels, cur_col)){
        cur_col ++;
    }
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

