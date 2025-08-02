#ifndef PLAYER_H
#define PLAYER_H

struct Bets;

struct Player
{
  int win_percentage = 0;
  int balance = 0;
  int biggest_win = 0;
  int total_bets = 0;
  int total_wins = 0;
  Bets* placed_bets = nullptr;
};

struct Bots
{
  int bot_count = 0;
  Player arr[];
};

Player* init_player();
Bots* init_bots(int count);

void destroy_player(Player* player);
void destroy_bots(Bots* bots);

void player_place_bet(Player* player, int option, int amount);
void player_pay(Player* player, int amount);
void player_reset_placed_bets(Player* player);

#endif
