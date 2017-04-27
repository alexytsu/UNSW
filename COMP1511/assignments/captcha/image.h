//-------------------------------------------------------
//PBM Manipulation Functions/Image Manipulation Functions
//-------------------------------------------------------

//reads a PBM file into an integer array
int read_pbm(char filename[], int height, int width, int
        pixels[height][width]);

//reads the dimensions of a PBM file from the header
int get_pbm_dimensions(char filename[], int *height, int *width);

//gets the bounding box of the digit within an image
void get_bounding_box(int height, int width, int pixels[height][width], int
        *start_row, int *start_column, int *box_height, int *box_width);

//creates a template from the reference digits
//the template matches the size of the bounded digit being cracked
//calls: downscale()
void get_bounded_template(int template_height, int template_width, int digit,
        int version, int template[template_height][template_width]);

//used by get_bounded_template to shrink the reference templates to the size
//of the digit being cracked
void downscale(int height, int width, int pixels[height][width], int nheight,
        int nwidth, int npixels[nheight][nwidth]);

//prints an array to stdout (for debugging and testing)
void print_image(int height, int width, int pixels[height][width]);

//allows us to copy small sections of one array to another
void copy_pixels(int height, int width, int pixels[height][width], int
        start_row, int start_column, int copy_height, int copy_width, int
        copy[copy_height][copy_width]);

//gets the starting coords and sizes of each bounded digit in a captcha
//gives all the information required to use
void divide_captcha(int height, int width, int pixels[height][width], int
        dividing_columns[3]);
