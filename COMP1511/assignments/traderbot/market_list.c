#include <stdlib.h>
#include <string.h>
#include "trader_functions.h"


int distance_search(Location *loc1, Location *loc2){
    Location *forward = loc1;
    Location *backward = loc1;
    int distance_f = 0;
    int distance_b = 0;
    for(;forward!=loc2;forward->next){
        distance_f ++;
    }
    for(;backward!=loc2;backward->previous){
        distance_b ++;
    }
    return distance_f<=distance_b ? distance_f:-distance_b;
}

int market_from_location(Market *m, Location *loc){

    Location *bot_location = loc;

    m->product = loc->commodity->name;
    m->volume = loc->commodity->volume;
    m->weight = loc->commodity->weight;
    m->next = NULL;

    if(loc->type == LOCATION_BUYER){
        m->demand = loc->quantity;
        m->buyers = 1;
        m->supply = 0;
        m->sellers = 0;
        return 1;
    }
    else if(loc->type == LOCATION_SELLER){
        m->supply = loc->quantity;
        m->sellers = 1;
        m->buyers = 0;
        m->demand = 0;
        return 1;
    }
    else{
        return 0;
    }
}

void print_market_node(Market *m){
    printf("%s, supply: %d\t demand: %d\t sellers: %d\t buyers %d\t volume:%d\t weight:%d\t\n", m->product, m->supply, m->demand, m->sellers, m->buyers, m->volume, m->weight);
}

Market *market_add(Market *node, Market *head){
    Market *previous = NULL;
    Market *n = head;
    for(;n!=NULL;n=n->next){
        if(!strcmp(n->product,node->product)){
            n->supply+=node->supply;
            n->demand+=node->demand;
            n->sellers+=node->sellers;
            n->buyers+=node->buyers;
            n->volume=node->volume;
            n->weight=node->weight;
            return head;
        }
        previous = n;
    }

    if(previous==NULL){
        head = node;
    }else{
        previous->next = node;
    }

    node->next = n;

    return head; 
}

Market *get_market_list(Location *cur_loc){
    Location *start = cur_loc;

    Market *market_head = NULL;

    do{
        Market *temp = malloc(sizeof(struct market));
        if(market_from_location(temp, cur_loc)){
            print_market_node(temp);
            if(temp->buyers == 1 || temp->sellers == 1){
                market_head = market_add(temp, market_head);
            }
        }
        cur_loc = cur_loc->next;
    }while(cur_loc != start);

    printf("ALL NODES ADDED, PRINT THE WHOLE LIST\n");
    for(;market_head!=NULL;market_head = market_head->next){
        print_market_node(market_head);
    }
}
