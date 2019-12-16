#include <stdio.h>
#include "captcha.h"

void analyze_image(int height, int width, int pixels[height][width]);

int main(int argc, char *argv[]) {
    int height, width;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
        return 1;
    }

    // first get image dimensions
    if (get_pbm_dimensions(argv[1], &height, &width) != 1) {
        return 1;
    }

    // now declare appropriate array
    int pixels[height][width];
    if (read_pbm(argv[1], height, width, pixels)) {
        analyze_image(height, width, pixels);
    }
    return 0;
}

void analyze_image(int height, int width, int pixels[height][width]) {
    int start_row, start_column, box_width, box_height;

    get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);
    printf("Bounding box height %d pixels, width %d pixels\n", box_height, box_width);
    printf("Bounding box bottom left corner is row %d column %d\n", start_row, start_column);
}
