#include <stdio.h>
#include "trader_bot.h"
#include "trader_functions.h"

//Sets name as per assignment specs
char *get_bot_name(void){
    return "xXx_1337_cr1ng3b0t";
}

//the "main" function of this robot, it is called every turn and assigns values
//to action and n corresponding to what we want to do this turn
void get_action(struct bot *bot, int *action, int *n){
    Location *current_location = bot->location;
    Market *market_list = get_market_list(current_location); 
    for(;market_list!=NULL;market_list=market_list->next){
        print_market_node(market_list);
    }
    *action = ACTION_MOVE;
    *n = 1;
}
