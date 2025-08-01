#include"bets.h"

#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

void bets_reset(Bets* b)
{
  assert((b != NULL) && "Not expecting nullptr");
  for ( int i = 0; i < b->size; i++ )
  {
    b->bets[i] = 0.0f;
  }
}

void bets_print(Bets* b)
{
  printf("[ ");
  for ( int i = 0; i < b->size; i++ )
  {
    printf("%f ", b->bets[i]);
  }
  printf(" ]\n");
}

void bets_set(Bets* b, float amount, int index)
{
  assert((b != NULL) && "Not expecting nullptr");
  assert((index >= 0 && index < b->size) && "Bets out of bounds!");
  b->bets[index] = amount;
}

Bets* create_bets(int size)
{
  size_t mem_size = sizeof(Bets) + size * sizeof(float);

  Bets* b = (Bets*)malloc(mem_size);
  if ( b == NULL ) {
    return NULL;
  }

  b->size = size;

  for ( int i = 0; i < size; i++ )
  {
    b->bets[i] = 0.0f;
  }
  return b;
}

void destroy_bets(Bets* b)
{
  if ( b != NULL ) {
    free(b);
  }
}