#include <stdio.h>
#include <stdlib.h> 
#include "guess.h"
#include "image.h"
#include "heuristics.h"


int main(int argc, char *argv[]) {

    //read the digit, get it's bounding box and get its balance
    int height, width, start_row, start_column, box_width, box_height, holes;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }
    if (get_pbm_dimensions(argv[1], &height, &width) != 1) {
        return 1;
    }

    //reads the pbm into the array pixels
    int pixels[height][width];

    //get all the attributes of the digit inside this function
    if (read_pbm(argv[1], height, width, pixels)) {
        int dividing_columns[3] = {0};
        divide_captcha(height, width, pixels, dividing_columns);
        for(int i = 0; i < 3; i ++){
            printf("%d\n", dividing_columns[i]);
        }
    }
    return 0;

}
