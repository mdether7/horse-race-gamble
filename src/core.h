#ifndef HORSE_BET_SIM_H
#define HORSE_BET_SIM_H

namespace Game {

  struct Player
  {
    float balance = 500.0f;
    float win_percentage = 0.0f;
    float biggest_win = 0.0f;
    int total_bets = 0;
    int total_wins = 0;
  };

  void run();

}

#endif