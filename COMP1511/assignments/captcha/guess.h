#define DIGITS 10
#define TESTS 100

//--------------------
//Digit Guessing Logic
//--------------------

//returns the index where the maximum value is within similarity_scores
void best_digits(int similarity_scores[DIGITS], int top_three[5], int
        top_scores[5]);

//double checks the output of best_digit against known attributes of numbers
int check_guess(int similarity_scores[DIGITS], int reverse_scores[DIGITS], int
        box_height, int box_width, int box_pixels[box_height][box_width]);

//loops through all 1000 reference images and tests them against the input 
//calls get_similarity, get_bounded_template and get_holes
void get_scores(int box_height, int box_width, int
        box_pixels[box_height][box_width], int similarity_scores[DIGITS], int reverse_scores[DIGITS]);

//compares the given digit with 1000 known digits and stores them in
//similarity_scores. the higher the score at index 'i', the more likely the
//digit is to be the digit 'i'
void get_similarity(int digit, int version, int box_height, int box_width, int
        box_pixels[box_height][box_width], int template[box_height][box_width],
        int similarity_scores[DIGITS]);

//rank scores
void rank_scores(int unordered[DIGITS], int ordered[DIGITS][2]);
