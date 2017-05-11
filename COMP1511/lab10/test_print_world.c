#include <stdio.h>
#include "trader_bot.h"

int main(void) {

   struct commodity c[] = {
      // name                   weight    volume
      { "Mobiles",                774,      508 },
   };

   struct location l[] = {
      // name                     type             commodity  price quantity  next  previous bots
      { "CSE",               LOCATION_START,           NULL,      0,      0, &l[ 1], &l[ 5], NULL},
      { "Samsung",           LOCATION_SELLER,         &c[0],    220,  18291, &l[ 2], &l[ 0], NULL},
      { "Dump",              LOCATION_DUMP,            NULL,      0,      0, &l[ 3], &l[ 1], NULL},
      { "Coogee Beach",      LOCATION_OTHER,           NULL,      0,      0, &l[ 4], &l[ 2], NULL},
      { "Shell",             LOCATION_PETROL_STATION,  NULL,     76,    639, &l[ 5], &l[ 3], NULL},
      { "J&B Hifi",          LOCATION_BUYER,          &c[0],    400,   6375, &l[ 0], &l[ 4], NULL},
   };

   struct bot bots[] = {
      // name cash fuel turns_left location cargo fuel_tank_capacity maximum_move maximum_cargo_weight maximum_cargo_volume
      {"Mr Robot", 132864, 42, &l[0], NULL, 83, 42, 7, 141106, 1033375},
   };

   struct bot_list bot_lists[] = {
      // bot next
      {&bots[0], NULL},
   };

   l[0].bots = &bot_lists[0];

   print_world(&bots[0]);
   return 0;
}
