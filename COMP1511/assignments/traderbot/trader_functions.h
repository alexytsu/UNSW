#include "trader_bot.h"

typedef struct location Location;

typedef struct store{
    char *name;
    int distance;
    int price;
    int amount;
    double store_preference;
    struct store *next;
}Store;

typedef struct market{
    char *product;
    int store_type;
    int supply;
    int demand;
    int sellers;
    int buyers;
    int volume;
    int weight;
    int preference_to_buy;
    Store *buyer_list;
    Store *seller_list;
    struct market *next;
}Market;

typedef struct bot Bot;

int distance_search(Location *loc1, Location *loc2);
int market_from_location(Market *m, Location *loc, Location *bot_loc);
int fuel_status(int *fuel_distance, Bot *bot);
void print_market_node(Market *m);
Market *market_add(Market *node, Market *head);
Market *get_market_list(Location *cur_loc);
Store *add_store(Store *node, Store *head);
void print_store_locations(Store *store);
void create_store(Store *seller_list, Store *buyer_list, Location *loc);
void rank_commodities(Market *market_list, Bot *bot);
void rank_products(Market *market_list);
int volume_remaining(Bot *bot);
int weight_remaining(Bot *bot);
int min(int a, int b);
int max(int a, int b);
int distance_to_best_store(Market *market_list);
int distance_to_best_buyer(Market *market_list, Bot *bot, int *none_found);
int nearest_dump(Location *location);
