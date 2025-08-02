#ifndef INPUT_H
#define INPUT_H

int input_wait_for_enter();
int input_valid_option(int first, int last);
bool input_get_yes_no(const char* message);
int input_get_amount(int max);

#endif