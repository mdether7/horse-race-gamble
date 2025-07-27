#ifndef GAME_H
#define GAME_H

namespace Game {

  enum class Phase { WELCOME_SCREEN = 0, MENU, RACE, RESULT, EXIT };

  struct Player
  {
    float balance = 500.0f;
    float win_percentage = 0.0f;
    float biggest_win = 0.0f;
    int total_bets = 0;
    int total_wins = 0;
  };

  void start();
  Phase handle_current_phase(Phase current, Player* p);
  Phase start_screen();
  Phase handle_menus(Player* p);
  Phase place_bet();
  Phase show_stats(const Player* p);
  Phase race_screen();
  Phase result_screen();

}

#endif