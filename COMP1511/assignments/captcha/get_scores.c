#include <stdio.h>
#include "captcha.h"

void get_scores(int box_height, int box_width, int
        box_pixels[box_height][box_width], int match_score[DIGITS][TESTS]){
    
    for(int digit = 0; digit < DIGITS; digit ++){
        for(int version = 0; version < TESTS; version ++){
            int template[box_height][box_width];
            get_bounded_template(box_height, box_width, digit, version, template);
            get_matches(digit, version, box_height, box_width, box_pixels, template,
                    match_score);
        }
    }

}

void get_matches(int digit, int version, int box_height, int box_width, int
        box_pixels[box_height][box_width], int template[box_height][box_width],
        int match_score[DIGITS][TESTS]){
    int score = 0;
    for(int row = 0; row < box_height; row ++){
        for(int col = 0; col < box_width; col ++){
            if(box_pixels[row][col] == template[row][col]){
                score ++;
            }
        }
    }
    match_score[digit][version] = score;
}

void get_bounded_template(int template_height, int template_width, int digit,
        int version, int template[template_height][template_width]){ 

    //filename generation from Muhammad Abubakar on the class forum
    //https://edstem.com.au/courses/416/discussion/28913?comment=72658
    char filename[15];
    sprintf(filename, "digit/%d_%02d.pbm", digit, version);

    //read each digit in as a reference and put it in a bounding box
    int reference_height, reference_width;
    get_pbm_dimensions(filename, &reference_height, &reference_width);
    int reference[reference_height][reference_width];
    read_pbm(filename, reference_height, reference_width, reference);
    int start_row, start_column, box_height, box_width;
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
