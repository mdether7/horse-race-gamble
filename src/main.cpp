#include"core.h"
#include"config.h"
int main()
{
  int result = 1;
  result = Game::run(BOT_COUNT);
  if ( result != 0 ) {
    return 1;
  }
  return 0;
}