#include <stdio.h>
#include "captcha.h"

int main(int argc, char *argv[]) {

    //read the digit, get it's bounding box and get its balance
    int height, width, start_row, start_column, box_width, box_height, holes;
    double h_balance, v_balance, density;
    double quadrant_densities[4];


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
        get_bounding_box(height, width, pixels, &start_row, &start_column,
                &box_height, &box_width);

        //puts the bounded pixel in box_pixels 
        int box_pixels[box_height][box_width];
        copy_pixels(height, width, pixels, start_row, start_column, box_height,
                box_width, box_pixels);

        //balance = horizontal center of gravity
        h_balance = get_horizontal_balance(box_height, box_width, box_pixels);
        v_balance = get_vertical_balance(box_height, box_width, box_pixels);

        //density of digit in the bounding box 
        density = get_density(box_height, box_width, box_pixels);
        holes = get_holes(box_height, box_width, box_pixels);

        //get the density of each quadrant of the bounded digit when the
        //bounding box has even dimensions the quadrant dimensions are easy
        //however, when odd, we will have one pixel overlap in the middle this
        //way we can have all quadrants to be the exact same size rather than
        //havign some one pixel wider or taller than others this helps us
        //initialize a 3d array of quadrants which helps us compact the
        //analysis code
        //q3 | q4
        //___|___
        //q1 | q2  

        //do maths that gets us the dimensions and locations of the quadrants
        int start_row = box_height/2; 
        int start_col = box_width/2;
        int quad_height, quad_width;
        if(box_height % 2 == 1){
            quad_height = box_height/2 + 1;
        }else{
            quad_height = box_height/2;
        }
        if(box_width % 2 == 1){
            quad_width = box_width/2 + 1;
        }else{
            quad_width = box_width/2;
        }

        //stores relevant quantities in an array, allowing us to loop 
        //rather than analyse each quadrant individually
        int quadrants[4][quad_height][quad_width];
        int start_coords[4][2] = {{0,0},
            {0, start_col},
            {start_row,0},
            {start_row, start_col}};

        //copy each quadrant and then find its density
        for(int quad = 0; quad < 4; quad++){
            copy_pixels(box_height, box_width, box_pixels,
                    start_coords[quad][0], start_coords[quad][1], quad_height,
                    quad_width, quadrants[quad]);
            quadrant_densities[quad] = get_density(quad_height, quad_width,
                    quadrants[quad]);
        }
    }
    return 0;
}
