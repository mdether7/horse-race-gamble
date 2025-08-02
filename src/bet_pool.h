#ifndef BET_POOL_H
#define BET_POOL_H
#include"horse.h"

struct BetPool
{
  int pool_count = 0;
  Horse horses[];
};

BetPool* create_betpool();
void destroy_betpool(BetPool* pool);
void regenerate_pool(BetPool* pool);

#endif