#include"horses.h"
#include<stdlib.h>
#include<math.h>

static const char* HORSE_NAMES[] =
{
  "Thunder     ",
  "Doggo       ",
  "Lovely      ",
  "La Bubu     ",
  "Black Beauty",
  "Iron Hoof   ",
  "Green Luck  ",
};

static const int TOTAL_HORSE_NUMBER = sizeof(HORSE_NAMES) / sizeof(char*); 

static void set_random_name(Horse* h, int* used_names)
{
  while (1)
  {
    int r = rand() % TOTAL_HORSE_NUMBER;
    if ( !used_names[r] )
    {
      h->name = HORSE_NAMES[r];
      used_names[r] = 1;
      break;
    }
  }
}

static void set_random_win_percentage(Horse* h, int count)
{
  int total = 100;
  for (int current = 0; current < count - 1; current++) 
  {
    int max_allowed = total - (count - current - 1);
    int percentage = (rand() % max_allowed) + 1;
    
    h[current].win_percentage = percentage;
    total -= percentage;
  }
  h[count - 1].win_percentage = total;
}

static float calculate_multiplier(int percentage)
{
  float win_probability = (float)percentage / 100;
  float odds = (1 / win_probability) * (1 - 0.10); // house edge formula
  float rounded =  roundf(odds * 100) / 100.0f;
  return rounded;
}

static void calculate_odds(Horse* h, int count)
{
  set_random_win_percentage(h, count);
  for ( int current = 0; current < count; current++ )
  {
    h[current].odds = calculate_multiplier(h[current].win_percentage);
  }
}

int total_horse_count()
{
  return TOTAL_HORSE_NUMBER;
}

Horse* generate_horses(int count)
{
  Horse* horses = (Horse*)malloc(count * sizeof(Horse));
  if (!horses) { return NULL; }

  int used_names[TOTAL_HORSE_NUMBER] = {0};
  for ( int current = 0; current < count; current++ )
  {
    set_random_name(&horses[current], used_names);
  }
  calculate_odds(horses, count);
  return horses;
}