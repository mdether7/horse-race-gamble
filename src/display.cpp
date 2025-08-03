#include"display.h"
#include"player.h"
#include"bet_pool.h"
#include<unistd.h>
#include<stdio.h>

void display_intro()
{
  puts("==============================");
  puts("=== HORSE BETTING SIM v0.7 ===");
  puts("==============================");
}

void display_menu()
{
  puts("=== Main menu ===");
  puts("[1] Start Race");
  puts("[2] Place a Bet");
  puts("[3] Your stats");
  puts("[4] Quit");
}

void display_player_stats(const Player* player)
{
  if ( !player ) {
    return;
  }
  puts("Player Stats:");
  puts("=================");
  printf("Balance: %.2f$\n", (double)player->balance / 100);
  printf("Total Wins: %d\n", player->total_wins);
  printf("Total Bets: %d\n", player->total_bets);
  printf("Success Rate: %d%\n", player->win_percentage);
  printf("Biggest Win: %.2f$\n", (double)player->biggest_win / 100);
  puts("=================");
}

void display_countdown()
{
  printf("Get Ready...");
  fflush(stdout);
  sleep(1);
  printf(" 3...");
  fflush(stdout);
  sleep(1);
  printf(" 2...");
  fflush(stdout);
  sleep(1);
  printf(" 1...");
  fflush(stdout);
  sleep(1);
  printf(" GO!\n");
}

void display_race_header()
{
  puts("============================");
  puts("========= THE RACE =========");
  puts("============================");
}

void display_result_header()
{
  puts("=====================");
  puts("HERE ARE THE RESULTS!");
  puts("=====================");
}

void display_balance(const Player* player)
{
  double dollar_money = (double)player->balance / 100;
  puts("--------------------------------");
  printf("Your Wallet: %.2f$\n", dollar_money);
  puts("--------------------------------");
}

void display_placed_bet(const BetPool* pool, int option, int amount)
{
  double dollar_money = (double)amount / 100;
  printf("=> Bet of $%.2f placed on %s\n=> [%.2fx odds]\n", dollar_money,
                                                            pool->horses[option].name,
                                                            (double)pool->horses[option].odds / 100 );
  printf("=> Potential win [ $%.2f ]\n", (double)(amount * pool->horses[option].odds) / 10000);
}

void display_bet_pool(const BetPool* pool)
{
  if ( !pool ) {
    return;
  }
  puts("Available Bets:");
  puts("--------------------------------");
  puts("# | Horse Name   | Odds  | Win %");
  puts("--------------------------------");
  for (int i = 0; i < pool->pool_count; i++) {
    printf("%d ", (i + 1));
    printf("| %s | %.2fx | %d% \n",
               pool->horses[i].name,
               (double)pool->horses[i].odds / 100,
               pool->horses[i].win_percentage);
  }
  puts("--------------------------------");
}

void clear_screen() {
  printf("\033[2J\033[H");
}
