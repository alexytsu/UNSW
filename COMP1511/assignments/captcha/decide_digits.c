#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "guess.h"
#include "heuristics.h"

//checks that the attributes of the digit matches with the guess from the 
//similarity comparison (which isn't perfect)
int check_guess(int similarity_scores[DIGITS], int reverse_scores[DIGITS], int
        box_height, int box_width, int box_pixels[box_height][box_width]){

    int ordered_similarity_scores[DIGITS][2];
    int ordered_reverse_scores[DIGITS][2];
    rank_scores(similarity_scores, ordered_similarity_scores);
    rank_scores(reverse_scores, ordered_reverse_scores);

    //balance = horizontal center of gravity
    double h_balance = get_horizontal_balance(box_height, box_width, box_pixels);
    double v_balance = get_vertical_balance(box_height, box_width, box_pixels);

    //density of digit in the bounding box 
    double density = get_density(box_height, box_width, box_pixels);
    double hole_balance;
    int holes = get_holes(box_height, box_width, box_pixels, &hole_balance);

    //gets quadrant densities
    double quadrant_densities[4] = {0};
    get_quadrant_densities(box_height, box_width, box_pixels,
            quadrant_densities);
    //
    //trivial to calculate so no need to put into get_attributes
    double tallness = (double)box_height/box_width;

    //8 or (sometimes) 0
    if(holes == 2){
        if(similarity_scores[0] > similarity_scores[8]){
            return 0;
        }
        return 8;
    }

    //0, 4, 6 or 9
    else if(holes == 1){
        //holes is a pretty accurate metric
         
        return ordered_similarity_scores[0][0];
    }

    //1, 2, 3, 5 or 7
    else if(holes == 0){
        if((ordered_similarity_scores[1][0] == 2 || ordered_similarity_scores[0][0] == 2) && (ordered_reverse_scores[0][0] == 5 || ordered_reverse_scores[1][0] == 5 || ordered_reverse_scores[2][0] == 5)){
            return 2;
        }
        else if((ordered_similarity_scores[0][0] == 5 || ordered_similarity_scores[1][0] == 5) && (ordered_reverse_scores[0][0] == 2 || ordered_reverse_scores[1][0] == 2 || ordered_reverse_scores[2][0] == 2)){
            return 5;
        }
        else if((ordered_similarity_scores[0][0] == 1 || ordered_similarity_scores[1][0] == 1) && (ordered_reverse_scores[0][0] == 1 || ordered_reverse_scores[1][0] == 1)){
            return 1;
        }
        else{
            return 3;
        }
        /*
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
        }
        else if(digit == 2 || digit ==5){
            return top_three[0];
        }
        */

        return 1;
    }

    //Error number of holes
    else{ 
        return 0;        
    }
}
