#include <stdio.h>
#include "heuristics.h"
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
    //safely sit. this is also a problem with the unbounded digit so we may as 
    //well just use the bounded digit. 
    //
    //                                  000000
    //0110  which has                   001100
    //1001  five "holes"   to --->      010010  which has 2 "holes"
    //1001                              010010
    //0110                              001100
    //                                  000000
    
    int nheight = height + 2;
    int nwidth = width + 2; 
    int npixels[nheight][nwidth];
    for(int row = 0; row < nheight; row ++){
        for(int col = 0; col < nwidth; col ++){
            if(row == 0 || col == 0){
                npixels[row][col] = 0;
            }else if(row < height && col < width){
                npixels[row][col] = pixels[row-1][col-1];
            }else{
                npixels[row][col] = 0;
            }
        }
    }
    
    //label the new array
    int curlabel = 1; //the first label will be 2, which is unique from the 0s and 1s that make up the image
    for(int row = 0; row < nheight; row ++){
        for(int col = 0; col < nwidth; col ++){
            if(npixels[row][col] == 0){
                curlabel ++;
                label(nheight, nwidth, npixels, row, col, curlabel);
            }
        }
    }

    //there are always three extra labels than holes
    // 1. the extra label for the border
    // 2. the extra label for the actual number
    int holes = curlabel - 2;
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
