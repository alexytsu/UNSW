#include <stdio.h>
#include "trader_bot.h"
#include "trader_functions.h"

char *get_bot_name(void);
void get_action(struct bot *bot, int *action, int *n);

//Sets name as per assignment specs
char *get_bot_name(void){
    return "supr3m3 m3m3 p1zz3r cr1ng3";
}

//the "main" function of this robot, it is called every turn and assigns values
//to action and n corresponding to what we want to do this turn
void get_action(struct bot *bot, int *action, int *n){
    Location *current_location = bot->location;
    Market *market_list = get_market_list(current_location); 
    *action = 0;
    *n = 0;
}
