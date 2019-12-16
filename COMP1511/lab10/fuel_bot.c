#include <stdio.h>
#include "trader_bot.h"

char *get_bot_name(void);
void get_action(struct bot *b, int *action, int *n);
int min(int a, int b);

//sets *action to BUY, SELL or MOVE and *n to the corresponding amount
void get_action(struct bot *b, int *action, int *n){

    //get the current location of the bot and its type
    struct location *current_location = b->location;
    int type = current_location->type;
    
    //simple behaviour as described in the lab specs
    if(type != LOCATION_PETROL_STATION){
        *n = min(b->maximum_move, nearest_fuel(b));
        *action = ACTION_MOVE;
    }else if(type == LOCATION_PETROL_STATION){
        if(b->fuel < b->fuel_tank_capacity){
            *action = ACTION_BUY;
            *n = b->fuel_tank_capacity - b->fuel;
        }
        else{
            *action = 0;
            *n = min(b->fuel, b->maximum_move);
        }
    }
}

//returns the minimum of a and b
//we use this whenenver the bot needs to move to check that we do not 
//exceed the maximum allowed movement
int min(int a, int b){
    return a<b ? a:b;
}

//sets our bot's name
char *get_bot_name(void){
    return "p1zz3r_m3m3_supr3m3";
}
