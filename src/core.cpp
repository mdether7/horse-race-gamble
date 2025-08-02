#include"core.h"
#include"display.h"
#include"input.h"
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
      default: State::EXIT; break;
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

  static void bet(Context* ctx)
  {
    clear_screen();
    regenerate_pool(ctx->pool);
    display_bet_pool(ctx->pool);

    int option = input_valid_option(1, ctx->pool->pool_count);
    if ( option < 0 ) { ctx->state = State::EXIT; return; } //fgets error
    int amount = input_get_amount(ctx->player->balance);
    if ( amount < 0) { ctx->state = State::EXIT; return; } //fgets error
    option--; // to array index

    player_place_bet(ctx->player, option, amount);
    player_pay(ctx->player, amount);

    display_placed_bet(ctx->pool, option, amount);

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
      case State::RACE: break;
      case State::RESULT: break;
      default: break;
    }
  }

  int run(int bot_count)
  {
    srand(time(NULL));

    Context ctx;
    if ( !initialize_game(&ctx, bot_count) ) {
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
