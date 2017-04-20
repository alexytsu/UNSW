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
        get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);

        //puts the bounded pixel in box_pixels 
        int box_pixels[box_height][box_width];
        copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

        //balance = horizontal center of gravity
        h_balance = get_horizontal_balance(box_height, box_width, box_pixels);
        v_balance = get_vertical_balance(box_height, box_width, box_pixels);
        
        //density of digit in the bounding box 
        density = get_density(box_height, box_width, box_pixels);
        holes = get_holes(box_height, box_width, box_pixels);

        //get the density of each quadrant of the bounded digit
        //since quad_width & height are integers, they will take the correct value whether 
        //box_width and height are odd or even 
        //N.B. when both box_width and box_height are odd, the bottom left quadrant will be 
        //smalle than the top right by one pixel in each dimension
        //q3 | q4
        //___|___
        //q1 | q2  

        int lower_height = box_height/2;
        int left_width = box_width/2;
        int higher_height, right_width;

        //if even, top and bottom height are same, otherwise, q4 is larger by one pixel in each dimension
        if(box_height % 2 == 1){
            higher_height = height/2 + 1;
        }else{
            higher_height = height/2;
        }
        if(box_width % 2 == 1){
            right_width = height/2 + 1;
        }else{
            right_width = height/2;
        }

        //create copies of the pixels so that we can perform analysis on each quadrant

        int dimensions[4][2] = {{lower_height, left_width}, 
                                {lower_height, right_width}, 
                                {higher_height, left_width}, 
                                {higher_height, right_width}};

        int quadrant1[dimensions[0][0]][dimensions[0][1]];
        int quadrant2[lower_height][right_width];
        int quadrant3[higher_height][left_width];
        int quadrant4[higher_height][right_width];

        copy_pixels(box_height, box_width, box_pixels, 0, 0, lower_height, left_width, quadrant1);
        copy_pixels(box_height, box_width, box_pixels, 0, left_width, lower_height, right_width, quadrant2);
        copy_pixels(box_height, box_width, box_pixels, lower_height, 0, higher_height, left_width, quadrant3);
        copy_pixels(box_height, box_width, box_pixels, lower_height, left_width, higher_height, right_width, quadrant4);

        //put them in an array for easier analysis
        int quadrants[4] = {quadrant1, quadrant2, quadrant3, quadrant4};

        //get the density of each quadrant
        int densities[4];
        for(int i = 0; i < 4; i ++){
        }

    }
       
    if(holes == 2){
        printf("8");
    }else if(holes == 1){
        if(v_balance >= 0.55){
            printf("9");
        }else if(v_balance <= 0.45){
            printf("6");
        }else{
            printf("0");
        }
    }else if(h_balance >= 0.5){
        printf("3");
    }

    return 0;
}
