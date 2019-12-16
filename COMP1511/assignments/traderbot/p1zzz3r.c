#include <stdio.h>
#include <stdlib.h>
#include "trader_bot.h"
#include "trader_functions.h"

//Sets name as per assignment specs
char *get_bot_name(void){
    return "cr1ng3y mc cr1ng3f4c3";
}

//the "main" function of this robot, it is called every turn and assigns values
//to action and n corresponding to what we want to do this turn
void get_action(struct bot *bot, int *action, int *n){

    Location *current_location = bot->location;

    //check fuel_status and if we need to move strictly towards the nearest station
    int fuel_distance = 0;
    int refuel = fuel_status(&fuel_distance, bot);
    printf("%d fuel left and %d distance from nearest fuel station\n", bot->fuel, fuel_distance);
    //perform fuel checks
    if(refuel && bot->turns_left>3){
        printf("REFUEL MODE ENGAGED!!!\n");
        /*
        if(fuel_distance != 0){
            *action = ACTION_MOVE;
            *n = fuel_distance;
            //    return;
        }
        */
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
    for(;print!=NULL;print=print->next){
        print_market_node(print);
    }

    int move = distance_to_best_store(market_list);

    if(move != 0 && bot->cargo==NULL){
        *action = ACTION_MOVE;
        if(refuel){
            if(fuel_distance*move >= 0){
                *n = min(fuel_distance, move);
            }else{
                *n = fuel_distance;
            }
        }else{
            *n = move;
        }
        return;

    }else if(move == 0 && bot->cargo==NULL && bot->turns_left >= 4){
        *action = ACTION_BUY;
        *n = (bot->cash - 10000)/bot->location->price;
        return;
    }

    if(bot->cargo!=NULL){
        int none_found = 0;
        move = distance_to_best_buyer(market_list, bot, &none_found);
        //        int isovercrowded = overcrowded(move, bot->location);
        if(none_found){
            *n = nearest_dump(bot->location);
            if(*n==0){
                *action = ACTION_DUMP;
            }
            *action = ACTION_MOVE;
        }
        else{
            *action = ACTION_MOVE;
            if(refuel){
                if(move*fuel_distance>=0){
                    *n = min(move, fuel_distance);
                }else{
                    *n = fuel_distance;
                }
            }else{
                *n = move;
            }
        }
        return;
    }

    if(move != 0){
        *action = ACTION_MOVE;
        if(refuel){
            if(fuel_distance*move >= 0){
                *n = min(fuel_distance, move);
            }else{
                *n = fuel_distance;
            }
        }else{
            *n = move;
        }
    }else if(move == 0){
        *action = ACTION_SELL;
        *n = 1000;
    }
}


int nearest_dump(Location *location){
    Location *forward = location;
    Location *backward = location;
    int distance_f = 0; 
    int distance_b = 0;
    for(;forward->type!=LOCATION_DUMP;forward=forward->next){
        distance_f ++;
    } 
    for(;backward->type!=LOCATION_DUMP;backward=backward->previous){
        distance_b ++;
    }

    return distance_f <= distance_b ? distance_f:-distance_b;
}
