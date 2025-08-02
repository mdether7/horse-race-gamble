#ifndef DISPLAY_H
#define DISPLAY_H

struct Player;
struct BetPool;

void clear_screen();
void display_intro();
void display_menu();
void display_bet_pool(const BetPool* pool);
void display_placed_bet(const BetPool* pool, int option, int amount);
void display_player_stats(const Player* player);

#endif
