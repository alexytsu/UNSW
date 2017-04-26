#define DIGITS 10
#define TESTS 100

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

//-------------------------------------------------------
//Image analysis functions (run these on arrays not PBMs)
//-------------------------------------------------------

//gets the vertical and horizontal center of gravity of the bounded digit
//returns as a percentage position within the image
double get_horizonatal_balance(int height, int width, int pixels[height][width]);
double get_vertical_balance(int height, int width, int pixels[height][width]);
   
//gets the density of the entire bounded digit
double get_density(int height, int width, int pixels[height][width]);

//gets the number of holes holes in a bounded digit 
int get_holes(int height, int width, int pixels[height][width]);

//gets all the attributes (including quadrant density), calls all the attribute
//functions listed above. stores the values it gets in external variables by
//use of pointers
void get_attributes(int start_row, int start_column, int box_height, int
        box_width, int box_pixels[box_height][box_width], double *h_balance,
        double *v_balance, double *density, int *holes, double
        quadrant_densities[4]);

//loops through all 1000 reference images and tests them against the input 
//calls get_similarity, get_bounded_template and get_holes
void get_scores(int box_height, int box_width, int
        box_pixels[box_height][box_width], double similarity_scores[DIGITS]);

//compares the given digit with 1000 known digits and stores them in
//similarity_scores. the higher the score at index 'i', the more likely the
//digit is to be the digit 'i'
void get_similarity(int digit, int version, int box_height, int box_width, int
        box_pixels[box_height][box_width], int template[box_height][box_width],
        double similarity_scores[DIGITS]);

//returns the index where the maximum value is within similarity_scores
int best_digit(double similarity_scores[DIGITS]);

//double checks the output of best_digit against known attributes of numbers
int check_guess(int guess, double similarity_scores[DIGITS], int start_row, int start_column, int box_height, int box_width, int box_pixels[box_height][box_width]);
