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
    copy_pixels(box_height, box_width, box_pixels, 2, 0, bottom_height,
            box_width, bottom_pixels);
    int bottom_smooth_l = is_smooth_l(bottom_height, box_width, bottom_pixels);
    int bottom_smooth_r = is_smooth_r(bottom_height, box_width, bottom_pixels);
    int touching_bot_sides = touching_both_sides(bottom_height, box_width,
            bottom_pixels);
    //find bottom tallness
    int bot_bound_w, bot_bound_h;
    int x,y;
    get_bounding_box(bottom_height, box_width, bottom_pixels, &x, &y,
            &bot_bound_w, &bot_bound_h);
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
    //similarity scores are determined by percentage overlap with templates
    //reverse scores are determine by flipping each template upside down
    int ordered_similarity_scores[DIGITS][2];
    int ordered_reverse_scores[DIGITS][2];
    rank_scores(similarity_scores, ordered_similarity_scores);
    rank_scores(reverse_scores, ordered_reverse_scores);

    //for easier referencing in the later logic
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
    if(holes == 2){//8 and some weird 0's
        if(right_hand_points == 3){//8's are not smooth like 0's
            return 8;
        }
        if(right_hand_points == 1){//0's don't bounce back in like 8's
            return 0;
        }
        if(vertical_intercepts == 4 && right_hand_points > 3){
            //you can pass through the edge of an 8 and get four but not a 0
            return 8;
        }
    }

    if(holes == 1){//0, 4, 6, 9
        if(!top_hole && !bot_hole && bottom_smooth_r){
            //if its hole is in the middle, its a 0
            return 0;
        }
        if(o1 == 4 && vertical_intercepts >= 2 && top_smooth_l){
            //if it looks like a 4 and you its top left is smooth it's a 4
            return 4;
        }
        if(right_hand_points == 1 && !whole_smooth_l){
            //if the left hand side isn't smooth but the right is, its a 9
            return 9;
        }
        //look for the position of the hole
        if(whole_smooth_l && !top_hole && bot_hole) return 6;
        if(whole_smooth_r && top_hole && !bot_hole) return 9;
    }

    if(holes == 0){//either 1, 2, 3, 5, 7
        if(vertical_intercepts < 3){// 1 or 7
            if(touching_top_sides && !touching_bot_sides){
                //7s usually have their widest point in the top and 1s in the 
                //bottom. but 7's are also more top heavy
                if(v_balance > 0.57){
                    return 7;
                }else{
                    return 1;
                }
            }
            if(touching_bot_sides && !touching_top_sides){
                //most ones have a serif at the bottom that is their widest point
                return 1;
            }
            if(o1 == 1){
                //revert to similarity guessing
                return 1;
            }
            if(o1 == 7){
                //revert to similarity guessing
                return 7;
            }
        }
        if(vertical_intercepts >= 3){// 2, 5, 3 or 7
            if(whole_smooth_r && right_hand_points < 3){
                //smooth right side but not a 2 5 or 3
                return 7;  
            }
            if(o1 == 2 && r1 ==5){
                //2's look like upside down 5s
                return 2;
            }
            if(o1 == 5 && r1 ==2){
                //5's look like upside down 2s
                return 5;
            }
            if(right_hand_points == 3){
                if(top_smooth_r && bottom_smooth_r){
                    //three's are are smooth on their right side but change
                    //direction a lot as well
                    return 3;
                }
            }
            //these numbers all have similarity to other upside down numbers
            if(o1 == 3 && r1 == 3){
                return 3;
            }
            if(o2 ==2 && r1 ==5){
                return 2;
            }
            if(o2 == 5 && r1 ==2){
                return 5;
            }
        }
    }

    //if none of the heuristics trigger a digit, revert to similarity
    return o1;
}
