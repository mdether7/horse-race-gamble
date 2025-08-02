#include"bet_pool.h"
#include"horse.h"
#include"rand_utils.h"
#include"config.h"

#include<stdlib.h>
#include<math.h>

static void generate_win_chance(BetPool* pool)
{
  int total = 100;
  for (int i = 0; i < pool->pool_count - 1; i++) {
    int max_allowed = total - (pool->pool_count - i - 1);
    int percentage = utils_random_int(1, max_allowed);
    pool->horses[i].win_percentage = percentage;
    total -= percentage;
  }
  pool->horses[pool->pool_count - 1].win_percentage = total;
}

static void generate_names(BetPool* pool)
{
  int used_names[MAX_BET_POOL] = {0};
  for (int i = 0; i < pool->pool_count; i++) {
    while (1) {
      int r = rand() % MAX_BET_POOL;
      if ( !used_names[r] ) {
        pool->horses[i].name = HORSE_NAMES[r];
        used_names[r] = 1;
        break;
      }
    }
  }
}

static int calculate_multiplier(int percentage)
{
  if ( percentage <= 0) { return 0; }

  const int SCALE = 100;
  const int HOUSE_EDGE = 10;

  int base_odds = (SCALE * SCALE) / percentage;
  int final_odds = (base_odds * (SCALE - HOUSE_EDGE)) / SCALE;

  return final_odds;
}

static void reset_pool(BetPool* pool)
{
  if ( !pool ) {
    return;
  }
  pool->pool_count = 0;
  for (int i = 0; i < MAX_BET_POOL; i++) {
    pool->horses[i].name = "";
    pool->horses[i].odds = 0;
    pool->horses[i].win_percentage = 0;
    pool->horses[i].in_use = false;
  }

}

BetPool* create_betpool()
{
  size_t mem_size = sizeof(BetPool) + MAX_BET_POOL * sizeof(Horse);

  BetPool* pool = (BetPool*)malloc(mem_size);
  if ( !pool ) {
    return nullptr;
  }

  pool->pool_count = 0;
  for (int i = 0; i < MAX_BET_POOL; i++) {
    pool->horses[i].name = "";
    pool->horses[i].odds = 0;
    pool->horses[i].win_percentage = 0;
    pool->horses[i].in_use = false;
  }

  return pool;
}

void destroy_betpool(BetPool* pool)
{
  if ( pool ) {
    free(pool);
  }
}

static void generate_odds(BetPool* pool)
{
  generate_win_chance(pool);
  for (int i = 0; i < pool->pool_count; i++) {
    pool->horses[i].odds = calculate_multiplier(
                           pool->horses[i].win_percentage);
  }
}

void regenerate_pool(BetPool* pool)
{
  if ( !pool ) {
    return;
  }
  reset_pool(pool);

  int bet_count = utils_random_int(MIN_BET_POOL, MAX_BET_POOL);
  pool->pool_count = bet_count;

  generate_names(pool);
  generate_odds(pool);

  for (int i = 0; i < pool->pool_count; i++) {
    pool->horses[i].in_use = true;
  }
}

