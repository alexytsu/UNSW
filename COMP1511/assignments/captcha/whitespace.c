#include <stdio.h>
#include "heuristics.h"
#include "image.h"

//looks at space between the digit and the right wall of its bounding box
void label_trailing_spaces(int height, int width, int pixels[height][width], int trailing_space[height]){

    //11100
    //11000   
    //11000
    //11100
    //
    //becomes
    //
    //11100
    //11100
    //11100
    //11100
   
    //plug two high holes such as the above
    for(int col = 0; col < width; col ++){
        for(int row = 0; row < height; row ++){
            if(pixels[row][col]){
                //check not out of bounds
                //i
                if(row < 4){
                    if(pixels[4][col]){
                        pixels[row][col] = 1;
                    }
                }
                if(row + 4 < height){
                    if(pixels[row+4][col]){
                        pixels[row+1][col] = 1;
                        pixels[row+2][col] = 1;
                        pixels[row+3][col] = 1;
                    }
                }
            }
        }
    }

    //create an array of distances between the right edge of the image and 
    //the digit at each height value
    for(int row = 0; row < height; row ++){
        for(int col = 0; col < width; col ++){
            if(pixels[height - 1 - row][width - 1 - col]){
                trailing_space[row] = col;
                break;
            }
        }
    }
}

//looks at distances between the digit and its left bounding box wall
void label_leading_spaces(int height, int width, int pixels[height][width], int leading_space[height]){

    //11100
    //11000   
    //11000
    //11100
    //
    //becomes
    //
    //11100
    //11100
    //11100
    //11100
   
    //plug two high holes such as the above
    for(int col = 0; col < width; col ++){
        for(int row = 0; row < height; row ++){
            if(pixels[row][col]){
                //check not out of bounds
                //i
                if(row < 4){
                    if(pixels[4][col]){
                        pixels[row][col] = 1;
                    }
                }
                if(row + 4 < height){
                    if(pixels[row+4][col]){
                        pixels[row+1][col] = 1;
                        pixels[row+2][col] = 1;
                        pixels[row+3][col] = 1;
                    }
                }
            }
        }
    }
    
    //create an array of distances between the right edge of the image and 
    //the digit at each height value
    for(int row = 0; row < height; row ++){
        for(int col = 0; col < width; col ++){
            if(pixels[height - 1 - row][col]){
                leading_space[row] = col;
                break;
            }
        }
    }
}
