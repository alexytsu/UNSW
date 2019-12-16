// Written April 2017
// andrewt@unsw.ed.au
// for http://www.cse.unsw.edu.au/~cs1511/assignments/captcha
//
// read a PBM image file

#include <stdio.h>
#include "captcha.h"

int read_pbm_header(FILE *f, int *height, int *width);
int read_pbm_pixels(FILE *f, int height, int width, int pixels[height][width]);


// filename must contain a PBM (monochrome) image of size height & width
// elements of array pixels are set to 1 for black, 0 for white
//
// pixels[0][0] will contain bottom-left pixel of image
// pixels[height-1][width-1] will contains top-right pixel of image
//
// read_pbm returns 1 if it successfully reads image, returns 0 otherwise
// an message is written to stderr if read_pbm is not successful

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
