#include"input.h"
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<cassert>

int input_wait_for_enter()
{
  char buf[4];
  printf("Press Enter to continue... ");
  if ( !fgets(buf, sizeof(buf), stdin) ) {
    return 1;
  }
  return 0;
}

int input_valid_option(int first, int last)
{
  assert( first < last && "Invalid parameters!");
  assert((first > 0 && last > 0) && "Parameters must be higher than 0");

  char input[100];
  bool wrong = false;
  while ( true )
  {
    if ( wrong ) {
      printf("Invalid option!\n");
      wrong = false;
    }
    printf("Choose your option: ");

    if ( !fgets(input, sizeof(input), stdin) ) {
      puts("FGETS ERROR! (CTRL + D probably)");
      return -1;
    }

    char* end;
    long option = strtol(input, &end, 10);

    if (*end != '\0' && *end != '\n') {
      wrong = true;
      continue;
    }
    if ( option < first || option > last ) {
      wrong = true;
      continue;
    }  
    return (int)option;
  }
}

int input_get_amount(int max)
{
  char input[100];
  while (true) {
      printf("Type amount: ");
      if (!fgets(input, sizeof(input), stdin)) {
          puts("FGETS ERROR! (CTRL + D probably)");
          return -1;
      }
      
      char* end;
      long amount = strtol(input, &end, 10);
      
      if (amount <= 0) {
          puts("Invalid amount!");
          continue;
      }
      
      if (amount > INT_MAX / 100) {
          puts("Amount too large!");
          continue;
      }
      
      long result = amount * 100; 
      
      // Handle decimal part
      if (*end == ',' || *end == '.') {
          char* second_end;
          long second_part = strtol(++end, &second_end, 10);
          
          if (second_part < 0 || second_part > 99) {
              puts("Invalid decimal part (must be 00-99)!");
              continue;
          }
          
          int decimal_digits = second_end - end;
          if (decimal_digits == 1) {
              second_part *= 10;  // "5.5" -> 50 cents
          } else if (decimal_digits != 2) {
              puts("Invalid decimal format (use 1 or 2 digits)!");
              continue;
          }
          
          result += second_part;
          end = second_end;
      }
      if (*end != '\0' && *end != '\n' && *end != ' ') {
          puts("Invalid input format!");
          continue;
      }
      if (result > max) {
          puts("You don't have enough money!");
          continue;
      }
    return (int)result;
  }
}