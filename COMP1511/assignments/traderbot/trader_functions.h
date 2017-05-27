typedef struct location Location;

typedef struct store{
    char *name;
    int distance;
    int price;
    int amount;
    int type;
    int store_preference;
    struct store *next;
}Store;

typedef struct market{
    char *product;
    int supply;
    int demand;
    int sellers;
    int buyers;
    int volume;
    int weight;
    int product_preference;
    Store *buyer_list;
    Store *seller_list;
    struct market *next;
}Market;

int distance_search(Location *loc1, Location *loc2);
int market_from_location(Market *m, Location *loc, Location *bot_loc);
void print_market_node(Market *m);
Market *market_add(Market *node, Market *head);
Market *get_market_list(Location *cur_loc);
Store *add_store(Store *node, Store *head);
void print_store_locations(Store *store);
