#include <stdio.h>
#include "heuristics.h"

int touching_both_sides(int height, int width, int pixels[height][width]){
    int row1 = 0;
    for(int i = 0; i < height; i ++){
        row1 += pixels[i][0];
    }

    int row2 = 0;
    for(int i = 0; i < height; i ++){
        row2 += pixels[i][width-1];
    }

    if(row1 && row2){
        return 1;
    }
    return 0;
}
