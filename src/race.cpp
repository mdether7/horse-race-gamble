#include"race.h"
#include"bet_pool.h"
#include<stdlib.h>

int race_determine_winner(const BetPool* pool)
{
  int percentages[pool->pool_count] = {0};
  for (int i = 0; i < pool->pool_count; i++) {
    percentages[i] = pool->horses[i].win_percentage;
  }

  int grid[100] = {0};

  int sum = 0;
  int horse_id = 0;
  int total = percentages[horse_id];

  while ( total != 100 ) {
    grid[sum++] = horse_id;
    if ( sum >= total ) {
      total += percentages[++horse_id];
    }
  }
  for ( int i = 0; i < percentages[horse_id]; ++i ) {
    grid[sum++] = horse_id;
  }

  // Fisher-Yates shuffle algorithm!
  for (int i = 99; i > 0; i--) {
    int j = rand() % (i + 1);
    int temp = grid[i];
    grid[i] = grid[j];
    grid[j] = temp;
  }

  return grid[rand() % 100];
}