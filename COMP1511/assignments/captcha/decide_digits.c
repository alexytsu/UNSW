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

    int copy_similarities[DIGITS] = {0};
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
            }
        }
        copy_similarities[index_of_max] = 0;
        top_scores[rank] = max;
        top_three[rank] = index_of_max;
    }
}

//checks that the attributes of the digit matches with the guess from the 
//similarity comparison (which isn't perfect)
int check_guess(int top_three[3], int top_scores[3], int start_row, int
        start_column, int box_height, int box_width, int
        box_pixels[box_height][box_width]){

    double h_balance, v_balance, density, quadrant_densities[4], tallness, hole_balance, vertical_symmetry;
    int holes;
    get_attributes(start_row, start_column, box_height, box_width, box_pixels,
            &h_balance, &v_balance, &density, &holes, quadrant_densities, &hole_balance, &vertical_symmetry);
    //trivial to calculate so no need to put into get_attributes
    tallness = (double)box_height/box_width;
    //printf("%lf", v_balance);
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

        // return top_three[2] if 1,3,7
        // return top_three[0] if 2,5

        int no_holes[5] = {1,2,3,5,7};
        double heuristic_scores[5] = {0};
        double stat_tallness[10] = {1.503, 1.770, 1.478, 1.457, 1.378, 1.486, 1.448, 1.546, 1.452, 1.460}; 
        double stat_h_balance[10] = {0.4995, 0.5253, 0.5441, 0.5725, 0.5473, 0.5134, 0.4669, 0.5308, 0.5024, 0.5293};
        double stat_symmetry[10] = {0.0, 0.3672, 0.2986, 0.3396, 0.0, 0.2856, 0.0, 0.2964, 0.0, 0.0};
        double stat_v_balance[10] = { 0.4978, 0.4865, 0.4918, 0.4804, 0.4939, 0.4840, 0.5966, 0.4969, 0.5171};
        for(int i = 0; i < 5; i ++){
            int digit = no_holes[i];    
       //     heuristic_scores[i] += fabs(stat_tallness[digit] - tallness); 
            heuristic_scores[i] += fabs(stat_symmetry[digit] - vertical_symmetry);
        //    heuristic_scores[i] += fabs(stat_h_balance[digit] - h_balance);
         //   heuristic_scores[i] += fabs(stat_v_balance[digit] - v_balance);
        }
        double min = 1;
        int index_min = 0;
        for(int i = 0; i < 5; i ++){
            if(heuristic_scores[i]<min){
                min = heuristic_scores[i];
                index_min = i;
            }
        }
        int digit = no_holes[index_min];
        if(digit == 1 || digit == 3 || digit == 7){
            return top_three[2];
        }else if(digit == 2 || digit ==5){
            return top_three[0];
        }
        
    }else{
        return top_three[0];
    }
}
