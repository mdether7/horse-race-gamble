#include"bets.h"
#include<stdlib.h>

Bets* create_bets(int size)
{
  size_t mem_size = sizeof(Bets) + size * sizeof(int);

  Bets* bets = (Bets*)malloc(mem_size);
  if ( !bets ) {
    return nullptr;
  }

  bets->size = size;
  for (int i = 0; i < size; i++) {
    bets->values[i] = 0; 
  }

  return bets;
}

void destroy_bets(Bets* bets)
{
  if ( bets ) {
    free(bets);
  }
}

void bets_erase(Bets* bets)
{
  if ( !bets ) {
    return;
  }
  for (int i = 0; i < bets->size; i++) {
    bets->values[i] = 0;
  }
}

bool bet_placed(Bets* bets, int index)
{
  return bets->values[index] != 0;
}

void bets_set(Bets* bets, int index, int amount)
{
  if ( !bets ) {
    return;
  }
  if ( index < 0 || index >= bets->size ) {
    return;
  }
  bets->values[index] = amount;
}

int bets_get(Bets* bets, int index)
{
  if ( !bets ) {
    return -1;
  }
  if ( index < 0 || index >= bets->size ) {
    return -1;
  }
  return bets->values[index];
}

int bets_total(Bets* bets)
{
  if ( !bets ) {
    return -1;
  }

  int total = 0; 
  for (int i = 0; i < bets->size; i++) {
    total += bets->values[i];
  }

  return total;
}
