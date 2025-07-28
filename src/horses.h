#ifndef HORSES_H
#define HORSES_H

struct Horse 
{
  const char* name;
  float odds;
  int win_percentage;
};

Horse* generate_horses(int count);
void free_horses(Horse* h);
int total_horse_count();

#endif