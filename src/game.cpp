#include"game.h"
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

namespace Game {

  void start() 
  {
    Player p;
    Phase current = Phase::WELCOME_SCREEN;
    while ( current != Phase::EXIT ) {
      current = handle_current_phase(current, &p);
    }
    puts("Thanks for playing!");
  }

  Phase handle_current_phase(Phase current, Player* p)
  {
    switch (current)
    {
      case Phase::WELCOME_SCREEN: return start_screen();
      case Phase::MENU: return handle_menus(p);
      case Phase::RACE: return race_screen();
      case Phase::RESULT: return result_screen();
      default: return start_screen(); // default fallback
    }
  }

  Phase handle_menus(Player* p) 
  {
    char input[100];
    bool mistake = false;
    while ( true )
    {
      system("clear");
      puts("=== CHOOSE YOUR ACTION ===");
      puts("[1] Start Race");
      puts("[2] Place a Bet");
      puts("[3] Your stats");
      puts("[4] Quit");
      if ( mistake ) {
        puts("Invalid input! Try again. [1-4]");
        mistake = false;
      }
      printf("Choose your option: ");

      if ( !fgets(input, sizeof(input), stdin) ) {
        puts("FGETS ERROR! (CTRL + D probably)");
        return Phase::EXIT;
      }
      input[strcspn(input, "\n")] = 0; // remove first occurance of newline

      if( strlen(input) == 1 ) {
        switch (input[0])
        {
          case '1': return Phase::RACE;
          case '2': return place_bet();
          case '3': return show_stats(p);
          case '4': return Phase::EXIT;
          default: mistake = true; break;
        }
      } else {
        mistake = true;
      }
    }
  }

  static void wait_for_enter()
  {
    char buf[4];
    puts("Press Enter to continue...");
    fgets(buf, sizeof(buf), stdin);
  }

  Phase show_stats(const Player* p)
  {
    system("clear");
    puts("Player Stats:");
    puts("-------------");
    printf("Balance: %.2f$\n", p->balance);
    printf("Total Wins: %d\n", p->total_wins);
    printf("Total Bets: %d\n", p->total_bets);
    printf("Success Rate: %.2f\n", p->win_percentage);
    printf("Biggest Win: %.2f$\n", p->biggest_win);
    puts("-------------");

    wait_for_enter();
    return Phase::MENU;
  }

  //   Available Horses:
// --------------------------------
// # | Horse Name   | Odds  | Win %
// --------------------------------
// 1 | Thunderbolt  | 4.5x  | 25%
// 2 | Black Beauty | 3.0x  | 30%
// 3 | Rusty Rocket | 7.0x  | 10%
// 4 | Iron Hoof    | 2.8x  | 35%
// --------------------------------

  static void display_horse_info() {}

  static void display_race_card()
  {
    puts("Available Horses:");
    puts("--------------------------------");
    puts("# | Horse Name   | Odds  | Win %");
    puts("--------------------------------");

  }

  Phase place_bet()
  {


    wait_for_enter();
    return Phase::MENU;
  }



  Phase race_screen() { puts("RACE!"); return Phase::EXIT; }
  Phase result_screen() { puts("RESLUT!"); return Phase::EXIT; }

  Phase start_screen() 
  {
    char input[100];
    bool mistake = false;
    while ( true ) 
    {
      system("clear");
      puts("==============================");
      puts("=== HORSE BETTING SIM v0.1 ===");
      puts("==============================");
      puts("Type enter to conitinue...");
      if ( mistake ) {
        puts("Invalid input! Try again.");
        mistake = false;
      }
      printf("> ");

      if ( !fgets(input, sizeof(input), stdin) ) {
        puts("FGETS ERROR! (CTRL + D probably)");
        return Phase::EXIT;
      }

      input[strcspn(input, "\n")] = 0; // remove first occurance of newline
      if ( strlen(input) == 0 ) {
        return Phase::MENU;
      } else {
        mistake = true;
      }
    }
  }

}