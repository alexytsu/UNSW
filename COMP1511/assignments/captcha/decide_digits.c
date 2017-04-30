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

    int vertical_intercepts = get_vertical_intercepts(box_height, box_width, box_pixels);
    //determine how many curves the right hand of a digit has
    //3 has 2, 2 has 1.5 etc. 

    int bottom_height = box_height/3;
    int bottom_pixels[bottom_height][box_width];
    copy_pixels(box_height, box_width, box_pixels, 0, 0, bottom_height, box_width, bottom_pixels);
    print_image(bottom_height, box_width, bottom_pixels);
    int concave = concavity(bottom_height, box_width, bottom_pixels);
    printf("%d\n", concavity);
    int right_hand_points = analyse_right_side(box_height, box_width,
            box_pixels);
    //printf("%d\n", right_hand_points);

    //-------------------------------------------------------------------------
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
        int o1 = ordered_similarity_scores[0][0];
        int o2 = ordered_similarity_scores[1][0];

        int r1 = ordered_reverse_scores[0][0];
        int r2 = ordered_reverse_scores[1][0];
        int r3 = ordered_reverse_scores[2][0];

        if(right_hand_points == 2){
            if((o1 == 2)&&(r1==5||r2==5||r3==5)){
                return 2;
            }
            if((o2 == 2)&&(r1==5||r2==5)){
                return 2;
            }
            if((o1 == 5)&&(r1==2||r2==2||r3==2)){
                return 2;
            }
            if((o2 == 5)&&(r1==2||r2==2)){
                return 5;
            }
            if(vertical_intercepts >= 3){
                return 2;
            }
            return 1;
        }

        if(right_hand_points == 1){
            if(v_balance > 0.558){
                return 7;
            }
            if(fabs(v_balance - 0.58) < fabs(v_balance - 0.486)){
                return 7;
            }
            if(v_balance < 0.519){
                if(vertical_intercepts >= 3){
                    return 2;
                }
                return 1;
            }
            return 4;
            //return 1;
        }

        if(right_hand_points == 3){
            if((o1 == 2)&&(r1==5||r2==5)){
                return 2;
            }
            if((o2 == 2)&&(r1==5)){
                return 2;
            }
            return 3;
        }

        else{
            return o1;
        }
    }
    else{
        return 0;
    }

        /*
        if((ordered_similarity_scores[0][0] == 1 ) &&
                (ordered_reverse_scores[0][0] == 1 ||
                 ordered_reverse_scores[1][0] == 1)){
            return 1;
        }

        if((ordered_similarity_scores[0][0] == 1) && (ordered_reverse_scores[0][0] == 5)){
            return 8;
        }

        if(right_hand_points == 1){
            if((ordered_similarity_scores[0][0] == 5 ||
                        ordered_similarity_scores[1][0] == 5) &&
                    (ordered_reverse_scores[0][0] == 2 ||
                     ordered_reverse_scores[1][0] == 2 ||
                     ordered_reverse_scores[2][0] == 2)){
                return 5;
            }
            if((ordered_similarity_scores[1][0] == 2)  &&
                    (ordered_reverse_scores[0][0] == 5 ||
                     ordered_reverse_scores[1][0] == 5)){
                if(ordered_similarity_scores[1][1] != 7){
                return 2;
                }
            }
            return 7;
        }

        else if (right_hand_points == 3){
            if((ordered_similarity_scores[0][0] == 5) &&
                    (ordered_reverse_scores[0][0] == 2 ||
                     ordered_reverse_scores[1][0] == 2)){
                return 5;
            }
            return 3;
        }

        if((ordered_similarity_scores[1][0] == 2 ||
                    ordered_similarity_scores[0][0] == 2) &&
                (ordered_reverse_scores[0][0] == 5 ||
                 ordered_reverse_scores[1][0] == 5 ||
                 ordered_reverse_scores[2][0] == 5)){
            return 2;
        }

        if((ordered_similarity_scores[0][0] == 5 ||
                    ordered_similarity_scores[1][0] == 5) &&
                (ordered_reverse_scores[0][0] == 2 ||
                 ordered_reverse_scores[1][0] == 2 ||
                 ordered_reverse_scores[2][0] == 2)){
            return 5;
        }

        if((ordered_similarity_scores[0][0] == 1 ||
                    ordered_similarity_scores[1][0] == 1) &&
                (ordered_reverse_scores[0][0] == 1 ||
                 ordered_reverse_scores[1][0] == 1)){
            return 1;
        }

        return 1;
    }
    */
}
