#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "guess.h"
#include "heuristics.h"
#include "image.h"

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

    //trivial to calculate so no need to put into get_attributes
    double tallness = (double)box_height/box_width;

    //get the number of times a vertical line can cut the number
    int vertical_intercepts = get_vertical_intercepts(box_height, box_width, box_pixels);

    //find if there is a hole in the top 
    int top_two_thirds_height = (2*box_height)/3;
    int top_two_thirds[top_two_thirds_height][box_width];
    copy_pixels(box_height, box_width, box_pixels, box_height - 1 - top_two_thirds_height, 0, top_two_thirds_height, box_width, top_two_thirds);
    double top_hole_balance;
    int top_hole = get_holes(top_two_thirds_height, box_width, top_two_thirds, &top_hole_balance);
    printf("top holes: %d\n", top_hole);

    //get if the bottom is smooth
    int bottom_height = box_height/3;
    int bottom_pixels[bottom_height][box_width];
    copy_pixels(box_height, box_width, box_pixels, 2, 0, bottom_height, box_width, bottom_pixels);
    int bottom_smooth_l = is_smooth_l(bottom_height, box_width, bottom_pixels);
    int bottom_smooth_r = is_smooth_r(bottom_height, box_width, bottom_pixels);
    //print_image(bottom_height, box_width, bottom_pixels);


    //get if the top is smooth
    int top_height = box_height/3;
    int top_pixels[top_height][box_width];
    copy_pixels(box_height, box_width, box_pixels, box_height - 1 - top_height, 0, top_height, box_width, top_pixels);
    int top_smooth_l = is_smooth_l(top_height, box_width, top_pixels);
    int top_smooth_r = is_smooth_r(top_height, box_width, top_pixels);
    //printf("%d\n", top_smooth_r);
    //print_image(top_height, box_width, top_pixels);

    int leading_spaces[box_height];
    label_leading_spaces(box_height, box_width, box_pixels, leading_spaces);
    int whole_smooth_r = is_smooth_r(box_height, box_width, box_pixels);
    int whole_smooth_l = is_smooth_l(box_height, box_width, box_pixels);

    //get the number of turns on the right hand side;
    int right_hand_points = analyse_right_side(box_height, box_width,
            box_pixels);
    //printf("%d\n", right_hand_points);

    int o1 = ordered_similarity_scores[0][0];
    int o2 = ordered_similarity_scores[1][0];
    int r1 = ordered_reverse_scores[0][0];
    int r2 = ordered_reverse_scores[1][0];
    int r3 = ordered_reverse_scores[2][0];

    //-------------------------------------------------------------------------
    //Actual Digit Guessing Logic: Uses the values gotten above
    //-------------------------------------------------------------------------

    //First return things that are absolute but highly restrictive
    if(o1 == 4 && vertical_intercepts >= 2 && top_smooth_l){
        return 4;
    }
    if(holes == 2){
        if(right_hand_points == 3){
            return 8;
        }
        if(right_hand_points == 1){
            return 0;
        }
    }

    if(holes == 1){
        if(right_hand_points == 1 && !whole_smooth_l){
            return 0;
        }
        if(whole_smooth_l && !top_hole) return 6;
        if(whole_smooth_r && top_hole) return 9;
    }




    //For debugging (if we get a 10 output, we know none of the conditions triggered
    return 10;
}
