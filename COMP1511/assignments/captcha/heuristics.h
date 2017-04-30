//-------------------------------------------------------
//Image analysis functions (run these on arrays not PBMs)
//-------------------------------------------------------

//gets the vertical and horizontal center of gravity of the bounded digit
//returns as a percentage position within the image
double get_horizontal_balance(int height, int width, int pixels[height][width]);
double get_vertical_balance(int height, int width, int pixels[height][width]);
   
//gets the density of the entire bounded digit
double get_density(int height, int width, int pixels[height][width]);

//gets the number of holes holes in a bounded digit 
int get_holes(int height, int width, int pixels[height][width], double *hole_balance);

int analyse_right_side(int height, int width, int pixels[height][width]);

int get_vertical_intercepts(int height, int width, int pixels[height][width]);

void label_leading_spaces(int height, int width, int pixels[height][width], int leading_space[height]);
void label_trailing_spaces(int height, int width, int pixels[height][width], int trailing_space[height]);

int is_smooth_r(int height, int width, int pixels[height][width]);
int is_smooth_l(int height, int width, int pixels[height][width]);

void get_quadrant_densities(int box_height, int box_width, int
        box_pixels[box_height][box_width], double
        quadrant_densities[4]);
