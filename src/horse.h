#ifndef HORSE_H
#define HORSE_H

struct Horse 
{
  const char* name = "";
  int odds = 0;
  int win_percentage = 0;
  bool in_use = false;
};

extern const char* HORSE_NAMES[];

#endif