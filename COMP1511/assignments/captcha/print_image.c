#include <stdio.h>
#include "image.h"

void print_image(int height, int width, int pixels[height][width]){

    for(int row = height-1; row >= 0; row --){
        for(int col = 0; col < width; col ++){
            printf("%d", pixels[row][col]);
        }
        printf("\n");
    }
}
