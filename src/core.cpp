#include"core.h"
#include"horses.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

namespace Game {

  enum class State
  {
    INTRO = 0,
    MENU,
    RACE,
    RESULT,
    EXIT, 
  };

  static int wait_for_enter()
  {
    // int c;
    // while ((c = getchar()) != '\n' && c != EOF) {}
    char buf[4];
    puts("Press Enter to continue...");
    if ( !fgets(buf, sizeof(buf), stdin) )
    {
      return 1;
    }
    return 0;
  }

  static State intro()
  {
    system("clear");
    puts("==============================");
    puts("=== HORSE BETTING SIM v0.3 ===");
    puts("==============================");
    
    int error = wait_for_enter();
    if ( error ) { return State::EXIT; }
    return State::MENU;
  }

  static State place_bet(Player* p)
  {
    puts("Betting screen!");

    int error = wait_for_enter();
    if ( error ) { return State::EXIT; }
    return State::MENU;
  }

  static State start_race(Player* p)
  {
    puts("Race started!");

    int error = wait_for_enter();
    if ( error ) { return State::EXIT; }
    return State::MENU;
  }

  static State show_results(const Player* p)
  {
    return State::EXIT;
  }

  static State show_stats(const Player* p)
  {
    system("clear");

    puts("Player Stats:");
    puts("=============");
    printf("Balance: %.2f$\n", p->balance);
    printf("Total Wins: %d\n", p->total_wins);
    printf("Total Bets: %d\n", p->total_bets);
    printf("Success Rate: %.2f\n", p->win_percentage);
    printf("Biggest Win: %.2f$\n", p->biggest_win);
    puts("=============");

    int error = wait_for_enter();
    if ( error ) { return State::EXIT; }
    return State::MENU;
  }

  static State handle_menus(Player* p) 
  {
    char input[100];
    bool mistake = false;
    while ( true )
    {
      system("clear");
      puts("=== Main menu ===");
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
        return State::EXIT;
      }

      input[strcspn(input, "\n")] = 0; // remove first occurance of newline
      if( strlen(input) == 1 ) {
        switch (input[0])
        {
          case '1': return State::RACE;
          case '2': return place_bet(p);
          case '3': return show_stats(p);
          case '4': return State::EXIT;
          default: mistake = true; break;
        }
      } else {
        mistake = true;
      }
    }
  }

  static State handle_states(State s, Player* p)
  {
    switch(s)
    {
      case State::INTRO: return intro();
      case State::MENU: return handle_menus(p);
      case State::RACE: return start_race(p);
      case State::RESULT: return show_results(p);
      default: return intro();
    }
  }

  void run() 
  {
    Player p;
    State current = State::INTRO;
    while ( current != State::EXIT ) 
    {
      current = handle_states(current, &p);
    }
    puts("Thanks for playing!");
  }

}