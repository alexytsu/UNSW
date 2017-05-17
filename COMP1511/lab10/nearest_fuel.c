#include <stdio.h>
#include "trader_bot.h"

int nearest_fuel(struct bot *b){
    struct location *forward = b->location;
    struct location *backward = b->location;

    int distance_forward = 0;
    int distance_backward = 0;

    //check how far the next petrol station is forward
    for(;forward->type!=LOCATION_PETROL_STATION;forward=forward->next){
        distance_forward ++;
    }

    //check how far the next petrol station is backwards
    for(;backward->type!=LOCATION_PETROL_STATION;backward=backward->previous){
        distance_backward ++;
    }

    //return the appropriate value
    if(distance_forward < distance_backward){
        return distance_forward;
    }
    if(distance_backward < distance_forward){
        return -distance_backward;
    }
    return distance_forward;
}
