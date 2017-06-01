#include <stdio.h>
#include "trader_bot.h"
#include "trader_functions.h"

//Sets name as per assignment specs
char *get_bot_name(void){
    return "cr1ng3y_mc_cr1ng3f4c3";
}

//the "main" function of this robot, it is called every turn and assigns values
//to action and n corresponding to what we want to do this turn
void get_action(struct bot *bot, int *action, int *n){

    Location *current_location = bot->location;
    Location *sanitize_location = bot->location;
    do{
        if(sanitize_location->quantity == 0){
            sanitize_location->previous->next = sanitize_location->next;
            sanitize_location->next->previous = sanitize_location->previous;
            free(sanitize_location);
            sanitize_location = sanitize_location->previous->next;
            continue;
        }
        sanitize_location = sanitize_location->next;
    }while(sanitize_location!=bot->location);

    //check fuel_status and if we need to move strictly towards the nearest station
    int fuel_distance = 0;
    int refuel = fuel_status(&fuel_distance, bot);

    //perform fuel checks
    if(refuel){
        printf("%d fuel left and %d distance from nearest fuel station\n", bot->fuel, fuel_distance);
        printf("REFUEL MODE ENGAGED!!!\n");
        if(fuel_distance != 0){
            *action = ACTION_MOVE;
            *n = fuel_distance;
            return;
        }
        if(fuel_distance == 0){
            printf("BOUGHT FUEL!\n");
            *action = ACTION_BUY;
            *n = 1000;
            return;
        }
    }

    //create a bare market list without preferencing/order
    Market *market_list = get_market_list(current_location);

    //for each commodity, rank the seller_list and buyer_list by max profit's made by visiting them
    rank_commodities(market_list, bot);
    rank_products(market_list);

    //print the market)list
    Market *print = market_list;
    if(print==NULL){
        printf("NULLED YOU CUCK!\n");
    }
    for(;print!=NULL;print=print->next){
        print_market_node(print);
    }

    int move = distance_to_best_store(market_list);

    if(move != 0 && bot->cargo==NULL){
        *action = ACTION_MOVE;
        *n = move;
    }else if(move == 0 && bot->cargo==NULL && bot->turns_left >= 4){
        *action = ACTION_BUY;
        *n = 1000;
    }

    if(bot->cargo!=NULL){
        move = distance_to_best_buyer(market_list, bot);
        if(move != 0){
            *action = ACTION_MOVE;
            *n = move;
        }else if(move == 0){
            *action = ACTION_SELL;
            *n = 1000;
        }

    }
}
