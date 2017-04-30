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


//--//Analyse the top two-thirds
    //find if there is a hole in the top 
    int top_two_thirds_height = (2*box_height)/3;
    int top_two_thirds[top_two_thirds_height][box_width];
    copy_pixels(box_height, box_width, box_pixels, box_height - 1 - top_two_thirds_height, 0, top_two_thirds_height, box_width, top_two_thirds);
    double top_hole_balance;
    int top_hole = get_holes(top_two_thirds_height, box_width, top_two_thirds, &top_hole_balance);

//--//Analyse the bottom two-thirds
    //find if there is a whole in the bottom
    int bot_two_thirds_height = (2*box_height)/3;
    int bot_two_thirds[bot_two_thirds_height][box_width];
    copy_pixels(box_height, box_width, box_pixels, 0, 0, bot_two_thirds_height, box_width, bot_two_thirds);
    double bot_hole_balance;
    int bot_hole = get_holes(bot_two_thirds_height, box_width, bot_two_thirds, &bot_hole_balance);

//--//Analyse the bottom third
    //get if the bottom is smooth
    int bottom_height = box_height/3;
    int bottom_pixels[bottom_height][box_width];
    copy_pixels(box_height, box_width, box_pixels, 2, 0, bottom_height, box_width, bottom_pixels);
    int bottom_smooth_l = is_smooth_l(bottom_height, box_width, bottom_pixels);
    int bottom_smooth_r = is_smooth_r(bottom_height, box_width, bottom_pixels);
    int touching_bot_sides = touching_both_sides(bottom_height, box_width, bottom_pixels);
    //find bottom tallness
    int bot_bound_w, bot_bound_h;
    int x,y;
    get_bounding_box(bottom_height, box_width, bottom_pixels, &x, &y, &bot_bound_w, &bot_bound_h);
    double bot_tallness = (double)bot_bound_h/bot_bound_w;

//--//Analyse the top third
    //get if the top is smooth
    int top_height = box_height/3;
    int top_pixels[top_height][box_width];
    copy_pixels(box_height, box_width, box_pixels, box_height - 1 - top_height, 0, top_height, box_width, top_pixels);
    int top_smooth_l = is_smooth_l(top_height, box_width, top_pixels);
    int top_smooth_r = is_smooth_r(top_height, box_width, top_pixels);
    int touching_top_sides = touching_both_sides(top_height, box_width, top_pixels);

    //find top tallness
    int top_bound_w, top_bound_h;
    get_bounding_box(top_height, box_width, top_pixels, &x, &y, &top_bound_w, &top_bound_h);
    double top_tallness = (double)top_bound_h/top_bound_w;

//--//Anaylse the whole digit
    int leading_spaces[box_height];
    label_leading_spaces(box_height, box_width, box_pixels, leading_spaces);
    int whole_smooth_r = is_smooth_r(box_height, box_width, box_pixels);
    int whole_smooth_l = is_smooth_l(box_height, box_width, box_pixels);

    //get the number of turns on the right hand side;
    int right_hand_points = analyse_right_side(box_height, box_width,
            box_pixels);
    //printf("%d\n", right_hand_points);

//--//Reference the similarity scores
    int ordered_similarity_scores[DIGITS][2];
    int ordered_reverse_scores[DIGITS][2];
    rank_scores(similarity_scores, ordered_similarity_scores);
    rank_scores(reverse_scores, ordered_reverse_scores);

    int o1 = ordered_similarity_scores[0][0];
    int o2 = ordered_similarity_scores[1][0];
    int r1 = ordered_reverse_scores[0][0];
    int r2 = ordered_reverse_scores[1][0];
    int r3 = ordered_reverse_scores[2][0];

//--//Analyse heuristics of the whole digit
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

    //-------------------------------------------------------------------------
    //Actual Digit Guessing Logic: Uses the values gotten above
    //-------------------------------------------------------------------------

    //First return things that are absolute but highly restrictive
    if(holes == 2){
        if(right_hand_points == 3){
            return 8;
        }
        if(right_hand_points == 1){
            return 0;
        }
    }

    if(holes == 1){
        if(!top_hole && !bot_hole && bottom_smooth_r){
            if(vertical_intercepts == 4 && right_hand_points > 3){
                return 8;
            }
            return 0;
        }
        if(o1 == 4 && vertical_intercepts >= 2 && top_smooth_l){
            return 4;
        }
        if(right_hand_points == 1 && !whole_smooth_l){
            return 9;
        }
        if(whole_smooth_l && !top_hole && bot_hole) return 6;
        if(whole_smooth_r && top_hole && !bot_hole) return 9;
    }

    if(holes == 0){
        if(vertical_intercepts < 3){// 1 or 7
            if(touching_top_sides && !touching_bot_sides){
                if(v_balance > 0.56){
                    return 7;
                }else{
                    return 1;
                }
            }
            if(touching_bot_sides && !touching_top_sides){
                return 1;
            }
            if(o1 == 1){
                return 1;
            }
            if(o1 == 7){
                return 7;
            }
        }
        if(vertical_intercepts >= 3){
            if(whole_smooth_r && right_hand_points < 3){
                return 7;  
            }
            if(o1 == 2 && r1 ==5){
                return 2;
            }
            if(o1 == 5 && r1 ==2){
                return 5;
            }
            if(right_hand_points == 3){
                if(top_smooth_r && bottom_smooth_r){
                    return 3;
                }
            }
        }
    }


    //For debugging (if we get a 10 output, we know none of the conditions triggered
    return o1;
}
