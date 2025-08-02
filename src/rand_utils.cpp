#include"rand_utils.h"
#include<stdlib.h>
#include<cassert>

int utils_random_int(int min, int max)
{
  assert(min <= max && "Invalid range!");
  int range = max - min + 1;
  return min + rand() % range;
}

