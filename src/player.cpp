#include"player.h"
#include"bets.h"
#include"config.h"

#include<stdlib.h>

Player* init_player()
{
  Player* player = (Player*)malloc(sizeof(Player));
  if ( !player ) {
    return nullptr;
  }
  player->placed_bets = create_bets(MAX_BET_POOL);
  if ( !player->placed_bets ) {
    free(player);
    return nullptr;
  }

  player->win_percentage = 0;
  player->balance = STARTING_BALANCE;
  player->biggest_win = 0;
  player->total_bets = 0;
  player->total_wins = 0;
  
  return player;
}

Bots* init_bots(int count)
{
  size_t mem_size = sizeof(Bots) + count * sizeof(Player);
  Bots* bots = (Bots*)malloc(mem_size);
  if ( !bots ) {
    return nullptr;
  }
  bots->bot_count = count;
  for (int i = 0; i < count; i++) {
    bots->arr[i].placed_bets = create_bets(MAX_BET_POOL);
    if ( !bots->arr[i].placed_bets ) {
      for (int current = i - 1; current >= 0; current--) {
        destroy_bets(bots->arr[current].placed_bets);
      }
      free(bots);
      return nullptr;
    }
    bots->arr[i].win_percentage = 0;
    bots->arr[i].balance = STARTING_BALANCE;
    bots->arr[i].biggest_win = 0;
    bots->arr[i].total_bets = 0;
    bots->arr[i].total_wins = 0;
  }
  return bots;
}

void player_place_bet(Player* player, int option, int amount)
{
  if ( !player ) {
    return;
  }
  bets_set(player->placed_bets, option, amount);
  player->total_bets++;
}

void player_add_balance(Player* player, int amount)
{

}

void player_sub_balance(Player* player, int amount)
{
  if ( !player || amount <= 0 ) {
    return;
  }
  player->balance -= amount;
  if ( player->balance < 0 ) {
    player->balance = 0;
  }
}

void player_reset_placed_bets(Player* player)
{
  if ( !player ) {
    return;
  }
  bets_erase(player->placed_bets);
}

void destroy_player(Player* player)
{
  if ( player ) {
    destroy_bets(player->placed_bets);
    free(player);
  }
}

void destroy_bots(Bots* bots)
{
  if ( bots ) {
    for (int i = 0; i < bots->bot_count; i++) {
      destroy_bets(bots->arr[i].placed_bets);
    }
    free(bots);
  }
}
