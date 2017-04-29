#include <stdio.h>
#include "guess.h"
#include "image.h"
#include "heuristics.h"

//loops through 1000 reference pbms and for each, 
//creates a template of correct size and then
//compares the templates to the input digit
void get_scores(int box_height, int box_width, int
        box_pixels[box_height][box_width], int similarity_scores[DIGITS], int reverse_scores[DIGITS]){
    double hole_balance;
    //use holes to shortcut to an answer when possible (minor optimisation)
    int holes = get_holes(box_height, box_width, box_pixels, &hole_balance);
    if(holes >= 1){ 
        for(int digit = 0; digit < DIGITS; digit ++){
            if(digit == 0 || digit == 4 || digit == 6 || digit == 8 || digit == 9){
                for(int version = 0; version < TESTS; version ++){

                    //only check numbers with holes
                    //makes the template
                    int template[box_height][box_width];
                    get_bounded_template(box_height, box_width, digit, version, template);
                    //compares the template to the bounded digit
                    get_similarity(digit, version, box_height, box_width, box_pixels, template,
                            similarity_scores);
                }
            }
        }
    }else{
        for(int digit = 0; digit < DIGITS; digit ++){
            if(digit == 1 || digit == 3 || digit == 7){
                for(int version = 0; version < TESTS; version ++){

                    //don't check numbers with holes
                    int template[box_height][box_width];

                    //makes the template
                    get_bounded_template(box_height, box_width, digit, version, template);

                    //compares the template to the bounded digit
                    get_similarity(digit, version, box_height, box_width, box_pixels, template,
                            similarity_scores);
                }
            }
        }
        for(int digit = 0; digit < DIGITS; digit ++){
            if(digit == 2 || digit == 5){
                for(int version = 0; version < TESTS; version ++){

                    //don't check numbers with holes
                    int template[box_height][box_width];

                    //makes the template
                    get_bounded_template(box_height, box_width, digit, version, template);

                    //compares the template to the bounded digit
                    get_similarity(digit, version, box_height, box_width, box_pixels, template,
                            similarity_scores);
                    
                    //compares reverse
                    int box_rpixels[box_height][box_width];
                    for(int row = 0; row < box_height; row ++){
                        for(int col = 0; col < box_width; col ++){
                            box_rpixels[row][col] = box_pixels[box_height-row-1][col];
                        }
                    }
                    int reverse_scores[10] = {0};
                    get_similarity(digit, version, box_width, box_height, box_rpixels, template,
                            reverse_scores);
                }
            }
        }
    }
}

//taking the template, it analyses the similarity between it and the digit
void get_similarity(int digit, int version, int box_height, int box_width, int
        box_pixels[box_height][box_width], int template[box_height][box_width],
        int similarity_scores[DIGITS]){

    int score = 0;
    for(int row = 0; row < box_height; row ++){
        for(int col = 0; col < box_width; col ++){
            if(box_pixels[row][col] == template[row][col]){
                score ++;
            }
        }
    }
    similarity_scores[digit] += score;
}

//makes a reference image from pbm and then downscales it so its size matches
//the bounded digit
void get_bounded_template(int template_height, int template_width, int digit,
        int version, int template[template_height][template_width]){ 

    //filename generation from Muhammad Abubakar on the class forum
    //https://edstem.com.au/courses/416/discussion/28913?comment=72658
    char filename[15];
    sprintf(filename, "digit/%d_%02d.pbm", digit, version);

    //read the reference pbm
    int reference_height, reference_width;
    get_pbm_dimensions(filename, &reference_height, &reference_width);
    int reference[reference_height][reference_width];
    read_pbm(filename, reference_height, reference_width, reference);
    int start_row, start_column, box_height, box_width;

    //create a bounded reference
    get_bounding_box(reference_height, reference_width, reference, &start_row,
            &start_column, &box_height, &box_width);
    int bounded_reference[box_height][box_width];
    copy_pixels(reference_height, reference_width, reference, start_row,
            start_column, box_height, box_width, bounded_reference);
    
    //make a template by scaling the bounded reference to the size of the 
    //bounded read-in digit 
    downscale(box_height, box_width, bounded_reference, template_height,
            template_width, template);
}
