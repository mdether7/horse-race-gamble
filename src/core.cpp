#include"core.h"
#include"display.h"
#include"race.h"
#include"input.h"
#include"bets.h"
#include"player.h"
#include"bet_pool.h"

#include<stdlib.h>
#include<stdio.h>
#include<time.h>

namespace Game {

  enum class State
  {
    INTRO = 0,
    MENU,
    BET,
    STATS,
    RACE,
    RESULT,
    EXIT 
  };

  struct Context
  {
    Player* player = nullptr;
    Bots* bots = nullptr;
    BetPool* pool = nullptr;
    State state = State::INTRO;
    bool should_regenerate = true;
    bool bet_placed = false;
    int winner = 0;
  };

  static bool initialize_game(Context* ctx, int bot_count)
  {
    if (!(ctx->player = init_player())) return false;
    if (!(ctx->bots = init_bots(bot_count))) return false;
    if (!(ctx->pool = create_betpool())) return false;
    return true;
  }

  static void clean_up(Context* ctx)
  {
    destroy_bots(ctx->bots);
    destroy_betpool(ctx->pool);
    destroy_player(ctx->player);
  }

  static void intro(Context* ctx)
  {
    clear_screen();
    display_intro();
    int error = input_wait_for_enter();
    if ( error ) { ctx->state = State::EXIT; }
    ctx->state = State::MENU;
  }

  static void menu(Context* ctx)
  {
    clear_screen();
    display_menu();

    int option = input_valid_option(1, 4);
    if ( option < 0 ) { ctx->state = State::EXIT; } // FGETS ERROR

    switch(option)
    {
      case 1: ctx->state = State::RACE; break;
      case 2: ctx->state = State::BET; break;
      case 3: ctx->state = State::STATS; break;
      case 4: ctx->state = State::EXIT; break;
      default: ctx->state = State::EXIT; break;
    } 
  }

  static void stats(Context* ctx)
  {
    clear_screen();
    display_player_stats(ctx->player);

    int error = input_wait_for_enter();
    if ( error ) { ctx->state = State::EXIT; return; }
    ctx->state = State::MENU;
  }

  static void return_funds(Context* ctx, int option)
  {
    player_add_balance(ctx->player, ctx->player->placed_bets->values[option]);
    ctx->player->placed_bets--;
    puts("Funds returned, bet again");
  }

  static void bet(Context* ctx)
  {
    if ( ctx->should_regenerate ) {
      regenerate_pool(ctx->pool);
      ctx->should_regenerate = false;
    }

    clear_screen();
    display_bet_pool(ctx->pool);
    display_balance(ctx->player);

    int option = input_valid_option(1, ctx->pool->pool_count);
    if ( option < 0 ) { ctx->state = State::EXIT; return; } //fgets error
    option--; // to array index
    if ( bet_placed(ctx->player->placed_bets, option) ) {
      if (input_get_yes_no("Are you sure you want to override this bet?")) {
        return_funds(ctx, option);
      } else {
        ctx->state = State::BET; return;
      }
    }
    int amount = input_get_amount(ctx->player->balance);
    if ( amount < 0) { ctx->state = State::EXIT; return; } //fgets error

    player_place_bet(ctx->player, option, amount);
    player_sub_balance(ctx->player, amount);

    display_placed_bet(ctx->pool, option, amount);
    ctx->bet_placed = true;

    int error = input_wait_for_enter();
    if ( error ) { ctx->state = State::EXIT; return; }
    ctx->state = State::MENU;
  }

  static void race(Context* ctx)
  {
    clear_screen();
    if ( !ctx->bet_placed ) {
      puts("You first need to bet!");
      int error = input_wait_for_enter();
      if ( error ) { ctx->state = State::EXIT; return; }
      ctx->state = State::MENU; return;
    }
    display_race_header();
    display_countdown();

    int winner = race_determine_winner(ctx->pool);
    ctx->winner = winner;
    printf("WINNER: %s\n", ctx->pool->horses[winner].name);

    int error = input_wait_for_enter();
    if ( error ) { ctx->state = State::EXIT; return; }
    ctx->state = State::RESULT;
  }

  static int calculate_prize_money(Context* ctx)
  {
    int prize = 0;
    for (int bet = 0; bet < ctx->player->placed_bets->size; bet++) {
      if ( bet == ctx->winner && ctx->player->placed_bets->values[bet] != 0 ) {
        prize = ctx->player->placed_bets->values[bet] * (double)ctx->pool->horses[ctx->winner].odds / 100;
      }
    }
    return prize;
  }

  static void update_player_stats(Context* ctx, int prize)
  {
    player_add_balance(ctx->player, prize);
    if ( prize ) { ctx->player->total_wins++; }
    if ( prize > ctx->player->biggest_win ) {
      ctx->player->biggest_win = prize;
    }
    ctx->player->win_percentage = (ctx->player->total_wins * 100) / ctx->player->total_bets;
  }

  static void result(Context* ctx)
  {
    clear_screen();
    display_result_header();

    int prize = calculate_prize_money(ctx);
    if ( prize ) {
      printf("You won! $%.2f\n", (double)prize / 100);
    } else {
      printf("You lost!\n");
    }
  
    update_player_stats(ctx, prize);

    player_reset_placed_bets(ctx->player);
    ctx->should_regenerate = true;
    ctx->bet_placed = false;

    if ( ctx->player->balance < 100 ) {
      puts("You're out of money!");
      ctx->state = State::EXIT; return;
    }

    int error = input_wait_for_enter();
    if ( error ) { ctx->state = State::EXIT; return; }
    ctx->state = State::MENU;
  }


  static void handle_states(Context* ctx)
  {
    switch(ctx->state)
    {
      case State::INTRO: intro(ctx); break;
      case State::MENU: menu(ctx); break;
      case State::BET: bet(ctx); break;
      case State::STATS: stats(ctx); break;
      case State::RACE: race(ctx); break;
      case State::RESULT: result(ctx); break;
      default: break;
    }
  }

  int run(int bot_count)
  {
    srand(time(NULL));

    Context ctx;
    if ( !initialize_game(&ctx, bot_count) ) {
      clean_up(&ctx);
      return 1;
    }

    while ( ctx.state != State::EXIT ) {
      handle_states(&ctx);
    }

    clean_up(&ctx);
    puts("Thanks for playing!");
    return 0;
  }
}
