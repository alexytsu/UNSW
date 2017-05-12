#include <stdio.h>
#include "trader_bot.h"

char *get_bot_name(void);
void get_action(struct bot *b, int *action, int *n);
int min(int a, int b);

void get_action(struct bot *b, int *action, int *n){
    struct location *current_location = b->location;
    if(current_location->type != LOCATION_PETROL_STATION){
        *n = nearest_fuel(b);
        *action = ACTION_MOVE;
    }else if(current_location->type == LOCATION_PETROL_STATION){
        if(b->fuel < b->fuel_tank_capacity){
            *action = ACTION_BUY;
            *n = b->fuel_tank_capacity - b->fuel;
        }
        else{
            printf("WOW\n");
            *action = 0;
            *n = min(b->fuel, b->maximum_move);
        }
    }
}

int min(int a, int b){
    return a<b ? a:b;
}

char *get_bot_name(void){
    return "p1zz3r_m3m3_supr3m3";
}
