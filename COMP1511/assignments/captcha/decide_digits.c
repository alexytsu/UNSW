#include <stdio.h>
#include "guess.h"
#include "heuristics.h"

//stores the similarity scores of the 3 most likely candidate guesses
void best_digits(int similarity_scores[DIGITS], int top_three[3], int
        top_scores[3]){

    //finds the top three scores in similarity_scores
    //puts the highest scoring digits in top_three
    //puts their corresponding scores in top_scores
    
    //since we will be destroying elements in the list whilst we sort it, we 
    //should make a copy

    double copy_similarities[DIGITS] = {0};
    for(int i = 0; i < DIGITS; i ++){
        copy_similarities[i] = similarity_scores[i];
    }

    int max = 0;
    int index_of_max = 0;
    //each iteration, find the max and add it to top_scores and its index to 
    //top_three
    for(int rank = 0; rank < 3; rank ++){
        max = 0;
        index_of_max = 0;
        for(int i = 0; i < DIGITS; i ++){
            if(copy_similarities[i] > max){
                index_of_max = i;
                max = copy_similarities[i];
                copy_similarities[i] = 0;
            }
        }
        top_scores[rank] = max;
        top_three[rank] = index_of_max;
    }
}

//checks that the attributes of the digit matches with the guess from the 
//similarity comparison (which isn't perfect)
int check_guess(int top_three[3], int top_scores[3], int start_row, int
        start_column, int box_height, int box_width, int
        box_pixels[box_height][box_width]){

    double h_balance, v_balance, density, quadrant_densities[4], tallness;
    int holes;
    get_attributes(start_row, start_column, box_height, box_width, box_pixels,
            &h_balance, &v_balance, &density, &holes, quadrant_densities);
    
    //we analyse the guess for possible mistakes. this depends on what the
    //guess is. we use a switch structure to check each possible guess

    if(holes == 2){
        return 8;
    }else{
        return top_three[0];
    }
}
