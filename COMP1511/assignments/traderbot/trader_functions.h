#include <stdlib.h>
#include <string.h>

typedef struct location Location;

typedef struct buyer{
    int distance;
    int price;
    int amount; 
    struct buyer *next;
}Buyer;

typedef struct market{
    char *product;
    int supply;
    int demand;   
    int sellers;
    int buyers;
    int volume;
    int weight;
    //Buyer *buyer_list;
    //Seller *seller_list;
    struct market *next;  
}Market;



void market_from_location(Market *m, Location *loc){
    m->product = loc->commodity->name;
    if(loc->type == LOCATION_BUYER){
        m->demand = loc->quantity;
        m->buyers = 1;
        m->supply = 0;
        m->sellers = 0;
    }
    else if(loc->type == LOCATION_SELLER){
        m->supply = loc->quantity;
        m->sellers = 1;
        m->buyers = 0;
        m->demand = 0;
    }
    else{
        m->supply = 0;
        m->sellers = 0;
        m->demand = 0;
        m->buyers = 0;
    }
    m->volume = loc->commodity->volume;
    m->weight = loc->commodity->weight;
    
    //todo
    //m->buyer_list = NULL;
    //m->seller_list = NULL;
    m->next = NULL;
}

void print_market_node(Market *m){
    printf("%s, supply: %d\t demand: %d\t sellers: %d\t buyers %d\t volume:%d\t weight:%d\t\n", m->product, m->supply, m->demand, m->sellers, m->buyers, m->volume, m->weight);
}

Market *market_add(Market *temp, Market *head){
    printf("REACHED BEFORE ASSIGNMENTS!\n");
    for(;head!=NULL;head=head->next){
        printf("Entered loop iteration!\n");
        if(!strcmp(head->product,temp->product)){
            printf("Entered if statement\n");
            head->supply+=temp->supply;
            head->demand+=temp->demand;
            head->sellers+=temp->sellers;
            head->buyers+=temp->buyers;
            head->volume=temp->volume;
            head->weight=temp->weight;
            return head;
        }
        printf("Skipped if statement!\n");
    }
    printf("New value!\n");

    temp->next = head;
    return temp; 
}

Market *get_market_list(Location *cur_loc){
    printf("#################\n\n");
    Location *start = cur_loc;
    Market *market_head = NULL;
    do{
        Market *temp = malloc(sizeof(Market));
        market_from_location(temp, cur_loc);
        if(temp->buyers == 1 || temp->sellers == 1){
            market_head = market_add(temp, market_head);
        }
        cur_loc = cur_loc->next;
    }while(cur_loc != start);

    for(;market_head!=NULL;market_head = market_head->next){
        print_market_node(market_head);
    }
}
