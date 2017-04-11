#include <stdio.h>
#include "captcha.h"

int check_row(int width, int height, int pixels[height][width], int row);
int check_column(int width, int height, int pixels[height][width], int col);

//checks if a row is empty
//returns 0 if non-empty, 1 if empty
int check_row(int width, int height, int pixels[height][width], int row){
    for(int i = 0; i < width; i++){
        if(pixels[row][i] == 1){
            return 0;
        }
    }
    return 1;
}

int check_column(int width, int height, int pixels[height][width], int col){
    for(int i = 0; i < height; i++){
        if(pixels[i][col] == 1){
            return 0;
        }
    }
    return 1;
}

void get_bounding_box(int height, int width, int pixels[height][width],
                  int *start_row, int *start_column, int *box_height, int *box_width){

    *start_row = 0;
    *start_column = 0;
    *box_width = 0;
    *box_height = 0;

    while(check_row(height, width, pixels, *start_row)){
        *start_row ++;
    }
    while(check_col(height, width, pixels, *start_column)){
        *start_column ++;
    }

    *box_height = *start_row;
    *box_width = *start_column;

    while(!check_row(height, width, pixels, *box_height)){
        *box_height ++;
    }
    while(!check_col(height, width, pixels, *box_width)){
        *box_width ++;
    }
}
