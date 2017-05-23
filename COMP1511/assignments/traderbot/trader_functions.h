typedef struct location Location;

typedef struct store{
    int distance;
    int price;
    int amount;
    int type;
    struct buyer *next;
}Store;

typedef struct market{
    char *product;
    int supply;
    int demand;
    int sellers;
    int buyers;
    int volume;
    int weight; 
    Store *seller_list;
    struct market *next;  
}Market;
int distance_search(Location *loc1, Location *loc2);
int market_from_location(Market *m, Location *loc);
void print_market_node(Market *m);
Market *market_add(Market *node, Market *head);
Market *get_market_list(Location *cur_loc);
