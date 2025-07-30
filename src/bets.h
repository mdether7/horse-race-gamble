#ifndef BET_H
#define BET_H

struct Bets
{
  int size;
  float bets[];
};

Bets* create_bets(int size);
void destroy_bets(Bets* b);
void bets_reset(Bets* b);
void bets_print(Bets* b);
void bets_set(Bets* b, float amount, int index);

#endif
