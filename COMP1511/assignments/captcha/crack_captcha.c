#include <stdio.h>
#include <stdlib.h> 
#include "guess.h"
#include "image.h"
#include "heuristics.h"

//contains basically crack_digit.c but as a function that can be called
int captcha_digit(int height, int width, int pixels[height][width]);

int main(int argc, char *argv[]) {

    //read the digit, get it's bounding box and get its balance
    int height, width;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }
    if (get_pbm_dimensions(argv[1], &height, &width) != 1) {
        return 1;
    }

    //reads the pbm into the array pixels
    int pixels[height][width];

    //get all the attributes of the digit inside this function
    if (read_pbm(argv[1], height, width, pixels)) {
        int dividing_columns[3] = {0};
        divide_captcha(height, width, pixels, dividing_columns);

        int width1 = dividing_columns[0];
        int width2 = dividing_columns[1] - width1;
        int width3 = dividing_columns[2] - width2 - width1;
        int width4 = width - width3 - width2 -width1; 

        int unbounded1[height][width1];
        int unbounded2[height][width2];
        int unbounded3[height][width3];
        int unbounded4[height][width4];

        copy_pixels(height, width, pixels, 0, 0, height, width1, unbounded1);
        copy_pixels(height, width, pixels, 0, dividing_columns[0], height, width2, unbounded2);
        copy_pixels(height, width, pixels, 0, dividing_columns[1], height, width3, unbounded3);
        copy_pixels(height, width, pixels, 0, dividing_columns[2], height, width4, unbounded4);

        printf("%d", captcha_digit(height, width1, unbounded1));
        printf("%d", captcha_digit(height, width2, unbounded2));
        printf("%d", captcha_digit(height, width3, unbounded3));
        printf("%d", captcha_digit(height, width4, unbounded4));
        printf("\n");
    }
    return 0;
}

int captcha_digit(int height, int width, int pixels[height][width]){
    int start_row, start_column, box_width, box_height, holes;
    //gets the bounding box around the pixel
    get_bounding_box(height, width, pixels, &start_row, &start_column,
            &box_height, &box_width);
    //puts the bounded pixel in box_pixels 
    int box_pixels[box_height][box_width];
    copy_pixels(height, width, pixels, start_row, start_column, box_height,
            box_width, box_pixels);

    //find the similarity between the bounded digit and templates
    int similarity_scores[DIGITS] = {0};
    int reverse_scores[DIGITS] = {0};
    get_scores(box_height, box_width, box_pixels, similarity_scores, reverse_scores);

    int guess = check_guess(similarity_scores, reverse_scores,
            box_height, box_width, box_pixels);
    //
    //printf("guess: %d\n", guess);
    return guess;
}
