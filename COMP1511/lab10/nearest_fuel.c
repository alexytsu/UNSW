#include <stdio.h>
#include "trader_bot.h"

int nearest_fuel(struct bot *b){
    struct location *forward = b->location;
    struct location *backward = b->location;

    int distance_forward = 0;
    int distance_backward = 0;

    for(;forward->type!=LOCATION_PETROL_STATION;forward=forward->next){
        distance_forward ++;
    }

    for(;backward->type!=LOCATION_PETROL_STATION;backward=backward->previous){
        distance_backward ++;
    }

    if(distance_forward < distance_backward){
        return distance_forward;
    }
    if(distance_backward < distance_forward){
        return -distance_backward;
    }
    return distance_forward;
    

}
