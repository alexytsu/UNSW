#include <stdio.h>
#include "captcha.h"

int main(int argc, char *argv[]) {
    
    //read the digit, get it's bounding box and get its balance
    int height, width, start_row, start_column, box_width, box_height;
    double h_balance, v_balance, density;

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

        //gets the bounding box around the pixel
        get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

        //puts the bounded pixel in box_pixels 
        int box_pixels[box_height][box_width];
        copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

        //balance = horizontal center of gravity
        h_balance = get_horizontal_balance(box_height, box_width, box_pixels);
        v_balance = get_vertical_balance(box_height, box_width, box_pixels);
        
        //density of digit in the bounding box 
        density = get_density(box_height, box_width, box_pixels);
    }
    
    if(h_balance < 0.5){
        printf("6\n");
    }else{
        printf("3\n");
    }

    return 0;
}
