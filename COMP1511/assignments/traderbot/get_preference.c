#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trader_bot.h"
#include "trader_functions.h"

void rank_commodities(Market *market_list, Bot *bot){
    Market *n = market_list;
    for(;n!=NULL;n=n->next){
        Store *buyer = n->buyer_list;
        Store *seller = n->seller_list;

        int buyers = 0;
        int total_buying_price = 0;
        for(;buyer!=NULL;buyer=buyer->next){
            buyers++;
            total_buying_price += buyer->price;
        }
        double buying_average = (double)total_buying_price/buyers;

        int sellers = 0;
        int total_selling_price = 0;
        for(;seller!=NULL;seller=seller->next){
            sellers++;
            total_selling_price += seller->price;
        }
        double selling_average = (double)total_selling_price/sellers;

        buyer = n->buyer_list;
        for(int i = 0;buyer!=NULL;buyer=buyer->next){
            int max_by_carrying = 0;
            int max_by_demand = buyer->amount;
            int max_amount = min(max_by_demand, max_by_carrying);
            buyer->store_preference = (selling_average - buyer->price)*max_amount; 
        }

        seller = n->seller_list;
        for(int i = 0; seller!=NULL;seller=seller->next){
            //global variable for understanding of bot?
            //find the min of the maximum profit oyu can generate by considering max profit, when constrained by volume
            //max profit when constrained by weight
            //max profit when constrained by how much funds we have left

            int max_by_available = seller->amount;
            int max_by_funds = (bot->cash-10000)/seller->price;
            int max_by_weight = weight_remaining(bot)/n->weight;
            int max_by_volume = volume_remaining(bot)/n->volume;

            int max_amount = min(max_by_available, min(max_by_funds, min(max_by_volume, max_by_weight)));
            seller->store_preference = (buying_average - seller->price)*max_amount;
        }
    }
}

void rank_products(Market *market_list){
    for(Market *commodity = market_list; commodity != NULL; commodity=commodity->next){
        int max_preference = 0;
        if(commodity->seller_list == NULL){
            continue;
        }
        for(Store *store = commodity->seller_list; store!=NULL; store = store->next){
            if(store->store_preference > max_preference){
                max_preference = store->store_preference;
            }
        }
        commodity->preference_to_buy = max_preference;
    }
}

int weight_remaining(Bot *bot){
    int cargo_weight = 0;
    if(bot->cargo == NULL){
        return bot->maximum_cargo_weight;
    }
    for(struct cargo *cargo_list = bot->cargo; cargo_list!=NULL; cargo_list=cargo_list->next){
        cargo_weight += cargo_list->quantity * cargo_list->commodity->weight;
    }
    return bot->maximum_cargo_weight - cargo_weight;
}

int volume_remaining(Bot *bot){
    int cargo_volume = 0;
    if(bot->cargo == NULL){
        return bot->maximum_cargo_volume;
    }
    for(struct cargo *cargo_list = bot->cargo; cargo_list!=NULL; cargo_list=cargo_list->next){
        cargo_volume += cargo_list->quantity * cargo_list->commodity->volume;
    }
    return bot->maximum_cargo_volume - cargo_volume;
}

int distance_to_best_store(Market *market_list){
    Market *best_product = NULL;
    Market *product = market_list;
    int highest_preference = 0;
    int skipped = 1;
    for(;product!=NULL;product=product->next){
        if(product->preference_to_buy > highest_preference){
            highest_preference = product->preference_to_buy;
            best_product = product;
            skipped = 0;
        }
    }
   
    if(skipped) return 100; 

    Store *best_store = NULL;
    Store *store = best_product->seller_list; 
    highest_preference = 0; 
    for(;store!=NULL;store=store->next){
        if(store->store_preference > highest_preference){
            highest_preference = store->store_preference;
            best_store = store;
        }
    }

    return best_store->distance;
}

int distance_to_best_buyer(Market *market_list, Bot *bot, int *none_found){
    char *product_name = malloc(1+strlen(bot->cargo->commodity->name));
    strcpy(product_name, bot->cargo->commodity->name);
    Market *market_search = market_list;
    for(;market_search;market_search=market_search->next){
        if(!strcmp(market_search->product, product_name)){
            break;
        }
    }

    Store *buyers = market_search->buyer_list;
    int location = 0;
    int maxprice = 0;
    Store *closest_store = buyers;
    int found = 0;
    for(;buyers!=NULL;buyers=buyers->next){
        if(buyers->price > maxprice && can_sell(buyers->name, bot->location)){
            maxprice = buyers->price;
            location = buyers->distance;
        }
    }
    if(maxprice==0){
        *none_found = 1;
        return location;
    }
    return location;
}

int can_sell(char *store_name, Location *loc){
    Location *start = loc;
    do{
        if(strcmp(store_name, start->name)==0){
            break;
        }
        start = start->next;
    }while(start!=loc);

    printf("Analysing Seller!\n");

    int sellers = 0;
    for(struct bot_list *list = start->bots; list != NULL; list = list->next){
        for(struct cargo *cur_bot_cargo = list->bot->cargo; cur_bot_cargo!=NULL; cur_bot_cargo = cur_bot_cargo->next){
            if(strcmp(start->commodity->name, cur_bot_cargo->commodity->name)==0){
                sellers ++;
            } 
        } 
    }

    if(sellers >= start->quantity){
        return 0;
    }else{
        return 1;
    }
}
