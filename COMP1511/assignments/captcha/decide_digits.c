#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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

    double h_balance, v_balance, density, quadrant_densities[4], tallness, hole_balance;
    int holes;
    get_attributes(start_row, start_column, box_height, box_width, box_pixels,
            &h_balance, &v_balance, &density, &holes, quadrant_densities, &hole_balance);
    //trivial to calculate so no need to put into get_attributes
    tallness = (double)box_height/box_width;

    //guess is. we use a switch structure to check each possible guess
    if(holes == 2){
        //may be a 0 or and 8
        for(int i = 0; i < 3; i ++){
            if(top_three[i] == 8){
                return 8;
            }
            if(top_three[i] == 0){
                return 0;
            }
        }
        return 8;
    }else if(holes == 1){
        if(top_three[0] == 8){
            return top_three[1];
        }
        return top_three[0];
    }else if(holes == 0){

        double heuristic_scores[3] = {0};
        double stat_tallness[10] = {1.503, 1.770, 1.478, 1.457, 1.378, 1.486, 1.448, 1.546, 1.452, 1.460}; 
        for(int i = 0; i < 3; i ++){
            int digit = top_three[i];    
            heuristic_scores[i] += fabs(stat_tallness[digit] - tallness); 
        }
        printf("heuristic scores\n");
        for (int i = 0; i < 3; i ++){
            printf("%d: %lf\n", top_three[i], heuristic_scores[i]);
        }

        return top_three[0];
    }else{
        return top_three[0];
    }
}
