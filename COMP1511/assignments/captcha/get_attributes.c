#include <stdio.h>
#include "captcha.h"

void get_attributes(int height, int width, int pixels[height][width], int
        start_row, int start_column, int box_height, int box_width, int
        box_pixels[box_height][box_width], double *h_balance, double
        *v_balance, double *density, int *holes, double quadrant_densities[4]){


        //balance = horizontal center of gravity
        *h_balance = get_horizontal_balance(box_height, box_width, box_pixels);
        *v_balance = get_vertical_balance(box_height, box_width, box_pixels);

        //density of digit in the bounding box 
        *density = get_density(box_height, box_width, box_pixels);
        *holes = get_holes(box_height, box_width, box_pixels);

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
        int start_row_quad = box_height/2; 
        int start_col_quad = box_width/2;
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
            {0, start_col_quad},
            {start_row_quad,0},
            {start_row_quad, start_col_quad}};

        //copy each quadrant and then find its density
        for(int quad = 0; quad < 4; quad++){
            copy_pixels(box_height, box_width, box_pixels,
                    start_coords[quad][0], start_coords[quad][1], quad_height,
                    quad_width, quadrants[quad]);
            quadrant_densities[quad] = get_density(quad_height, quad_width,
                    quadrants[quad]);
        }

}
