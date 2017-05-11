#include <stdio.h>
#include "trader_bot.h"

void print_world(struct bot *b){

    struct location *start_location = b->location;
    struct location *current_location = start_location;
    for(int i =0; current_location != start_location || i == 0;i ++){
        printf("%s: ", current_location->name);
        if(current_location->type == LOCATION_START){
            printf("start\n"); 
        }
        else if(current_location->type == LOCATION_SELLER){
            printf("will sell %d units of %s for $%d\n", current_location->quantity, current_location->commodity->name, current_location->price); 
        }
        else if(current_location->type == LOCATION_BUYER){
            printf("will buy %d units of %s for $%d\n", current_location->quantity, current_location->commodity->name, current_location->price); 
        }
        else if(current_location->type == LOCATION_DUMP){
            printf("dump\n"); 
        }
        else if(current_location->type == LOCATION_OTHER){
            printf("other\n"); 
        }
        else if(current_location->type == LOCATION_PETROL_STATION){
            printf("Petrol station %d units of available fuel for $%d\n", current_location->quantity, current_location->price);
        }
        current_location = current_location->next;
    }
}
