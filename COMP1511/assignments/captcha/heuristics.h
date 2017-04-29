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

//gets all the attributes (including quadrant density), calls all the attribute
//functions listed above. stores the values it gets in external variables by
//use of pointers
void get_attributes(int start_row, int start_column, int box_height, int
        box_width, int box_pixels[box_height][box_width], double *h_balance,
        double *v_balance, double *density, int *holes, double
        quadrant_densities[4], double *hole_balance, double *vertical_symmetry);

double get_vertical_symmetry(int height, int width, int pixels[height][width]);

