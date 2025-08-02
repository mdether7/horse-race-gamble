#ifndef BET_H
#define BET_H

struct Bets
{
  int size;
  int values[];
};

Bets* create_bets(int size);
void destroy_bets(Bets* bets);

bool bet_placed(Bets* bets, int index);
void bets_erase(Bets* bets);
void bets_set(Bets* bets, int index, int amount);
int bets_get(Bets* bets, int index);
int bets_total(Bets* bets);

#endif
