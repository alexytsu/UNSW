#include <stdio.h>
#include "captcha.h"


void get_bounding_box(int height, int width, int pixels[height][width],
                  int *start_row, int *start_column, int *box_height, int *box_width){

    *start_row = 0;
    *start_column = 0;
    *box_width = 0;
    *box_height = 0;

    //get the start row
    int keep_checking = 1;
    int row = 0;
    while(keep_checking){
        for(int i = 0; i < width; i++){
            if(pixels[row][i]){
                keep_checking = 0; 
                *start_row = row;
                break;
            }
        } 
        row ++;
    }

    //get the box_height
    keep_checking = 1;
    while(keep_checking){
        int pixel_detected = 0;
        for(int i = 0; i < width; i++){
            if(pixels[row][i]){
                pixel_detected = 1;
            }
        }
        if(!pixel_detected){
           *box_height = row - *start_row; 
           keep_checking = 0;
        }
        row ++;
    }

    //get the start column
    keep_checking = 1;
    int col = 0;
    while(keep_checking){
        for(int i = 0; i < height; i++){
            if(pixels[i][col]){
                keep_checking = 0;
                *start_column = col;
                break;
            }
        }
        col ++;
    }

    //get the box_width
    keep_checking = 1;
    int right_edge_reached = 0;
    while(keep_checking){
        int pixel_detected = 0;
        for(int i = 0; i < height; i++){
            if(pixels[i][col]){
                pixel_detected = 1;
            }
        }
        if(right_edge_reached == 1){
            if(pixel_detected){
                right_edge_reached = 0;
            }
        }
        if(!pixel_detected && !right_edge_reached){
           *box_width = col - *start_column; 
            right_edge_reached = 1;
        }
        if(col == width-1){
            keep_checking = 0;
        }
        col ++;
    }


}
