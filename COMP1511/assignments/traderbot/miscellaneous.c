#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trader_bot.h"
#include "trader_functions.h"

//We often need to find the min or max of two values
int max(int a, int b){
    return a>=b ? a:b;
}
int min(int a, int b){
    return a<=b ? a:b;
}

//find the distance between any two locations in the circular map
int distance_search(Location *loc1, Location *loc2){
    Location *forward = loc1;
    Location *backward = loc1;
    int distance_f = 0;
    int distance_b = 0;
    for(;forward!=loc2;forward=forward->next){
        distance_f ++;
    }
    for(;backward!=loc2;backward=backward->previous){
        distance_b ++;
    }
    //returns positive when equal otherwise, the shortest abs distance
    return distance_f<=distance_b ? distance_f:-distance_b;
}
