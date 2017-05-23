typedef struct location Location;
typedef struct market{
    
}Market;

Market *get_market_list(Location *cur_loc){
    Location *start = *cur_loc;
    do{
        printf("%s\n", cur_loc->name); 
        cur_loc = cur_loc->next;
    }while(cur_loc != start);
}
