#include <stdio.h>
#include "captcha.h"

//returns the digit that has the highest similarity score
int best_digit(double similarity_scores[DIGITS]){

    int best_digit = 0;
    int max_score = 0;

    for(int i = 0; i<DIGITS; i++){
        //if larger than current_max, set it as the new max
        if(similarity_scores[i] > max_score){
            max_score = similarity_scores[i];
            //retains the index where the max was found so we know the digit
            //rather than just its score
            best_digit = i;
        }
    }  
    return best_digit;
}

//checks that the attributes of the digit matches with the guess from the 
//similarity comparison (which isn't perfect)
int check_guess(int guess, double similarity_scores[DIGITS], int start_row, int
        start_column, int box_height, int box_width, int box_pixels[box_height][box_width]){

    double h_balance, v_balance, density, quadrant_densities[4];
    int holes;
    get_attributes(start_row, start_column, box_height, box_width, box_pixels,
            &h_balance, &v_balance, &density, &holes, quadrant_densities);
    printf("%.2lf, %.21f, %.21f, %.21f\n", h_balance, v_balance, density, quadrant_densities[0]);
    return guess;

}
