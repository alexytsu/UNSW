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

        int width1 = dividing_columns[0];
        int width2 = dividing_columns[1] - width1;
        int width3 = dividing_columns[2] - width2 - width1;
        int width4 = width - width3 - width2 -width1; 

        int unbounded1[height][width1];
        int unbounded2[height][width2];
        int unbounded3[height][width3];
        int unbounded4[height][width4];

        copy_pixels(height, width, pixels, 0, 0, height, width1, unbounded1);
        print_image(height, width1, unbounded1);

    }
    return 0;

}
