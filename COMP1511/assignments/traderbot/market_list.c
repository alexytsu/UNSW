#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trader_bot.h"
#include "trader_functions.h"

/*------------------------------------------------------------------------------
this function is called each turn to return a linked list of custom market
structs. its using heuristics and information calculated from this linked list
of commodities that we make a decision for our action.

the market linked list displays for each commodotiy that exists in the world...
    - name: of the product
    - supply: total amount available for the bot to buy
    - demand: total amount available for the bot to sell
    - sellers: the total number of merchants of the product
    - buyers: the total number of shops buying the product
    - volume: of the product
    - weight: of the product
    - store_lists: a list of stores that sells or buys the product
        - the store list shows each location that either sells or buys the
          product and some information about those stores
        - distance: from the bot
        - price: buying or selling price
        - amount: amount that store can buy or sell
        - type: whether the store buys or sells
-------------------------------------------------------------------------------*/
Market *get_market_list(Location *cur_loc){
    Location *start = cur_loc;
    Market *market_head = NULL;
    do{
        Market *temp = malloc(sizeof(struct market));
        if(market_from_location(temp, cur_loc, start)){
            if(temp->buyers == 1 || temp->sellers == 1){
                market_head = market_add(temp, market_head);
            }
        }
        cur_loc = cur_loc->next;
    }while(cur_loc != start);

    printf("MARKET LIST\n");
    return market_head;
}

//creates a Market wrapper for a location
int market_from_location(Market *m, Location *loc, Location *bot_loc){

    //if not a buyer or seller, we don't include it in the "market"
    if(loc->type != LOCATION_BUYER && loc->type != LOCATION_SELLER){
        return 0;
    }

    m->product = loc->commodity->name;
    m->volume = loc->commodity->volume;
    m->weight = loc->commodity->weight;
    m->store_type = loc->type;
    m->next = NULL;

    //create and initialise the details of that particular store
    m->seller_list = malloc(sizeof(Store));
    m->buyer_list = malloc(sizeof(Store));
    m->seller_list->distance = distance_search(loc, bot_loc);
    m->buyer_list->distance = distance_search(loc, bot_loc);
    create_store(m->seller_list, m->buyer_list, loc);

    //store additional information
    if(loc->type == LOCATION_BUYER){
        m->demand = loc->quantity;
        m->buyers = 1;
        m->supply = 0;
        m->sellers = 0;
        return 1;
    }

    if(loc->type == LOCATION_SELLER){
        m->supply = loc->quantity;
        m->sellers = 1;
        m->buyers = 0;
        m->demand = 0;
        return 1;
    }
    return 0;
}

//prints a custom Market linked list
void print_market_node(Market *m){
    printf("%s, supply: %d\t demand: %d\t sellers: %d\t buyers %d\t volume:%d\t weight:%d\t\n", m->product, m->supply, m->demand, m->sellers, m->buyers, m->volume, m->weight);
    printf("Buyer List\n");
    print_store_locations(m->buyer_list);
    printf("Seller List\n");
    print_store_locations(m->seller_list);
}


//either adds a new commodity to the market list or adds the quantity being
//bought or sold of a particular commodity to its existing node
Market *market_add(Market *node, Market *head){

    Market *previous = NULL;
    Market *n = head;

    //check if the commodity is already in the list
    for(;n!=NULL;n=n->next){
        //update the values if already in the list
        if(!strcmp(n->product,node->product)){
            n->supply+=node->supply;
            n->demand+=node->demand;
            n->sellers+=node->sellers;
            n->buyers+=node->buyers;

            if(node->store_type==LOCATION_BUYER){
                n->buyer_list = add_store(node->buyer_list, n->buyer_list);
            }else if(node->store_type==LOCATION_SELLER){
                n->seller_list = add_store(node->seller_list, n->seller_list);
            }

            return head;
        }
        previous = n;
    }

    //if not in the list, add it to the list
    if(previous==NULL){
        head = node;
    }else{
        previous->next = node;
    }
    node->next = n;
    return head;
}
