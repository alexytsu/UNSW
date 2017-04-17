#include <stdio.h>
#include "captcha.h"

// filename must contain a PBM (monochrome) image of size height & width
// elements of array pixels are set to 1 for black, 0 for white
//
// pixels[0][0] will contain bottom-left pixel of image
// pixels[height-1][width-1] will contains top-right pixel of image
//
// read_pbm returns 1 if it successfully reads image, returns 0 otherwise
// an message is written to stderr if read_pbm is not successful

//Written April 2017 by Andrew Taylor

int read_pbm(char filename[], int height, int width, int pixels[height][width]) {
    int file_height, file_width, n_pixels_read;
    FILE *f;

    f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "'%s' - can not open: ", filename);
        perror("");  // print reasons open failed
        return 0;
    }
    if (read_pbm_header(f, &file_height, &file_width) != 1) {
        fclose(f);
        return 0;
    }
    if (file_height != height || file_width != width) {
        fprintf(stderr, "Mismatch between image dimensions (%d x %d) and supplied array dimensions (%d x %d)\n",  file_height, file_width , height, width);
        fclose(f);
        return 0;
    }
    n_pixels_read = read_pbm_pixels(f, height, width, pixels);
    if (n_pixels_read == height * width) {
        fclose(f);
        return 1;
    } else {
        fprintf(stderr, "Insufficient pixels read (%d) for image dimensions (%d x %d)\n",  n_pixels_read, height, width);
    }
    fclose(f);
    return 0;
}

// filename must contain a PBM image  height & width areset to image deminsions
// read_pbm returns 1 if it successful, 0 otherwise

int get_pbm_dimensions(char filename[], int *height, int *width) {
    int result;
    FILE *f;
    f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "'%s' - can not open: ", filename);
        perror("");  // print reasons open failed
        return 0;
    }
    result = read_pbm_header(f, height, width);
    fclose(f);
    return result;
}

// read a PBM header from stream f, setying height and width
// return 1 if successful, 0 otherwise

int read_pbm_header(FILE *f, int *height, int *width) {
    if (
            fgetc(f) == 'P' &&
            fgetc(f) == '1' &&
            fscanf(f, "%d", width) == 1 &&
            fscanf(f, "%d", height) == 1
        ) {
        return 1;
    } else {
        fprintf(stderr, "File not in Portable Bit Map format\n");
        return 0;
    }
}

// read PBM pixels from stream f into array image
// characters other than '1' (black) and '0' (white) are ignored
// number of pixels read is returned

int read_pbm_pixels(FILE *f, int height, int width, int pixels[height][width]) {
    int c;
    int row = height - 1;
    int column = 0;
    c = fgetc(f);
    while (c != EOF && row >= 0) {
        if (c == '0' || c == '1') {
            pixels[row][column] = c == '1';
            column = column + 1;
            if (column == width) {
                column = 0;
                row = row - 1;
            }
        }
        c = fgetc(f);
    }
    return column + (height - 1 - row)*width;
}
void copy_pixels(int height, int width, int pixels[height][width],
                 int start_row, int start_column, int copy_height, int copy_width,
                 int copy[copy_height][copy_width]){

    for(int row = 0; row < copy_height; row++){
        for(int col = 0; col < copy_width; col++){
           
            copy[row][col] = pixels[row+start_row][col+start_column];

        }
    }
}

void get_bounding_box(int height, int width, int pixels[height][width],
                  int *start_row, int *start_column, int *box_height, int *box_width){

    *start_row = 0;
    *start_column = 0;
    *box_width = 0;
    *box_height = 0;

    //get the start row
    int keep_checking = 1;
    int row = 0;
    while(keep_checking){
        for(int i = 0; i < width; i++){
            if(pixels[row][i]){
                keep_checking = 0; 
                *start_row = row;
                break;
            }
        } 
        row ++;
    }

    //get the box_height
    keep_checking = 1;
    while(keep_checking){
        int pixel_detected = 0;
        for(int i = 0; i < width; i++){
            if(pixels[row][i]){
                pixel_detected = 1;
            }
        }
        if(!pixel_detected){
           *box_height = row - *start_row; 
           keep_checking = 0;
        }
        row ++;
    }

    //get the start column
    keep_checking = 1;
    int col = 0;
    while(keep_checking){
        for(int i = 0; i < height; i++){
            if(pixels[i][col]){
                keep_checking = 0;
                *start_column = col;
                break;
            }
        }
        col ++;
    }

    //get the box_width
    keep_checking = 1;
    int right_edge_reached = 0;
    while(keep_checking){
        int pixel_detected = 0;
        for(int i = 0; i < height; i++){
            if(pixels[i][col]){
                pixel_detected = 1;
            }
        }
        if(right_edge_reached == 1){
            if(pixel_detected){
                right_edge_reached = 0;
            }
        }
        if(!pixel_detected && !right_edge_reached){
           *box_width = col - *start_column; 
            right_edge_reached = 1;
        }
        if(col == width-1){
            keep_checking = 0;
        }
        col ++;
    }
}
