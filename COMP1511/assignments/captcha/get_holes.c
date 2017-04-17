#include <stdio.h>
#include "captcha.h"
#define MAX_LABELS 4

void label(int height, int width, int pixels[height][width], int posx, int posy, int curlabel);
//gets the number of holes in a digit by connected-component labelling
//algorithm as described from https://en.wikipedia.org/wiki/Connected-component_labeling
//each hole will be labelled with an int from 2 and above
//if we label each contiguous group of 0's as a "hole" we will always have exactly
//one more hole than actual holes since, the "outside" of each number will always
//be counted as a hole

int get_holes(int height, int width, int pixels[height][width]){
  
    //if the digit hits the edge of the bounding box, we will have issues with
    //extra outside holes, so create a border within which the bounded digit can
    //safely sit
    //                                  000000
    //0110  which has                   001100
    //1001  five "holes"   to --->      010010  which has 2 "holes"
    //1001                              010010
    //0110                              001100
    //                                  000000
    
    int nheight = height + 2;
    int nwidth = width + 2; 
    int npixels[nheight][nwidth];
    for(int row = 0; row < height; row ++){
        for(int col = 0; col < width; col ++){
            npixels[1+row][1+col] = pixels[row][col];
        }
    }
    
    //label the new array
    int curlabel = 2;
    for(int row = 0; row < nheight; row ++){
        for(int col = 0; col < nwidth; col ++){
            label(nheight, nwidth, npixels, row, col, curlabel);
            curlabel ++;
        }
    }

    //count the number of labels
    int labels[MAX_LABELS] = {0}; 
    int current_label = 0; 
    int unique = 1;
    for(int row = 0; row < nheight; row ++){
        for(int col = 0; col < nwidth; col ++){
            current_label = npixels[row][col];
            unique = 1;
            for(int i = 0; i < MAX_LABELS; i ++){
                if(labels[i] == current_label){
                    unique = 0;
                }
            }
            
            if(unique){
                for(int i = 0; i < MAX_LABELS; i ++){
                    if(labels[i] == 0){
                        labels[i] = current_label;
                        break;
                    }
                }
            }
        }
    }
    
    int holes = -2;
    for(int i = 0; i < MAX_LABELS; i ++){
        if(labels[i] != 0){
            holes ++;
        }
    }

    return holes;
}


   

//this labels holes in the new array, npixels 
//it calls itself recursively such that as soon as an empty pixel is found, 
//all pixels that can connect to it will also be labelled
//it then moves on to find the next path

void label(int height, int width, int pixels[height][width], int posx, int posy, int curlabel){

    //break if we attempt to check an out of bounds element
    if(posx < 0 || posy < 0 || posx >= height || posy >= width){
        return;
    }
    //only perform the labelling if the pixel is empty
    //when checking pixels, we only care about those labelled 0
    //1's are border pixels, any other int has already been labelled
    //since 0 = false, we can use !0 to only analyse digits we want
    if(!pixels[posx][posy]){
        pixels[posx][posy] = curlabel;
        //if it is empty, also label recursively everything around it
        //use an array of values corresponding to directions to check all 
        //boxes around the current box
        //
        //vector method of traversing the array taken from user gus of stackoverflow
        //saves from having to have 4 cases
        //http://stackoverflow.com/a/14466081
        int dx[] = {+1, 0, -1, 0};
        int dy[] = {0, +1, 0, -1};
        for(int i = 0; i<4; i++){
            label(height, width, pixels, posx+dx[i], posy+dy[i], curlabel);
        }
    }
}
