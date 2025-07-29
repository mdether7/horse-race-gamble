#include"core.h"
#include"horses.h"
#include"bets.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<assert.h>

namespace Game {

  enum class State
  {
    INTRO = 0,
    MENU,
    RACE,
    RESULT,
    EXIT, 
  };

  static const int MIN_HORSE_NUMBER = 3;

  struct Player
  {
    float balance = 500.00f;
    float win_percentage = 0.0f;
    float biggest_win = 0.0f;
    int total_bets = 0;
    int total_wins = 0;
    Bets* bets = NULL;
  };

  struct Context
  {
    Horse* horses = NULL;
    int horse_count;
  };

  static int get_random_int(int min, int max)
  {
    assert(min <= max && "Invalid range!");
    int range = max - min + 1;
    int random = rand() % range;
    return min + random; 
  }

  static int init_bets(Bets* b, int MAX_BETS)
  {
    b = create_bets(MAX_BETS);
    if ( b == NULL ) { return 1; }
    else { return 0; }
  }

  static void clean_up_player(Player* p)
  {
    destroy_bets(p->bets);
  }

  static void clean_up_horses(Context* c)
  {
    free_horses(c->horses);
    c->horses = NULL;
    c->horse_count = 0;
  }

  static void clean_up(Context* c, Player* p)
  {
    clean_up_horses(c);
    clean_up_player(p);
  }

  static int horse_gen(Context* c)
  {
    if ( c->horses == NULL )
    {
      int count = get_random_int(MIN_HORSE_NUMBER, total_horse_count());
      c->horses = generate_horses(count);
      if ( c->horses == NULL ) { puts("Horses mem alloc failed!"); return 0; }
      c->horse_count = count;
    }
    return 1;
  }

  static int wait_for_enter()
  {
    // int c;
    // while ((c = getchar()) != '\n' && c != EOF) {}
    char buf[4];
    printf("Press Enter to continue... ");
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

  static State place_bet(Player* p, Context* c)
  {
    system("clear");

    if ( !horse_gen(c) ) { return State::EXIT; }

    puts("Available Horses:");
    puts("--------------------------------");
    puts("# | Horse Name   | Odds  | Win %");
    puts("--------------------------------");
    for ( int i = 0; i < c->horse_count; i++ )
    {
      printf("%d ", (i + 1));
      printf("| %s | %.2fx | %d% \n",
              c->horses[i].name,
              c->horses[i].odds,
              c->horses[i].win_percentage);
    }
    puts("--------------------------------");
    printf("Your Wallet: %.2f$\n", p->balance);
    puts("--------------------------------");

    printf("Enter horse number you want to bet on: ");

    int error = wait_for_enter();
    if ( error ) { return State::EXIT; }
    return State::MENU;
  }

  // Your Wallet: $500

  // Enter Horse Number to Bet On: 2
  // Enter Bet Amount: 50

  // ➡ Bet of $50 placed on Black Beauty (3.0x odds)

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
    puts("=================");
    printf("Balance: %.2f$\n", p->balance);
    printf("Total Wins: %d\n", p->total_wins);
    printf("Total Bets: %d\n", p->total_bets);
    printf("Success Rate: %.2f\n", p->win_percentage);
    printf("Biggest Win: %.2f$\n", p->biggest_win);
    puts("=================");

    int error = wait_for_enter();
    if ( error ) { return State::EXIT; }
    return State::MENU;
  }

  static State handle_menus(Player* p, Context* c) 
  {
    clean_up_horses(c); // << here for the debug;

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
          case '2': return place_bet(p, c);
          case '3': return show_stats(p);
          case '4': return State::EXIT;
          default: mistake = true; break;
        }
      } else {
        mistake = true;
      }
    }
  }

  static State handle_states(State s, Player* p, Context* c)
  {
    switch(s)
    {
      case State::INTRO: return intro();
      case State::MENU: return handle_menus(p, c);
      case State::RACE: return start_race(p);
      case State::RESULT: return show_results(p);
      default: return intro();
    }
  }

  void run() 
  {
    srand(time(NULL));

    Context c;
    Player p;
    init_bets(p.bets, total_horse_count()); // max betting range
    
    State current = State::INTRO;
    while ( current != State::EXIT ) 
    {
      current = handle_states(current, &p, &c);
    }
    clean_up(&c, &p);
    puts("Thanks for playing!");
  }

}