#include <stdio.h>

int main(int argc, char* argv[])
{
  int distance = 100;
  float power = 2.345f;
  double super_power = 56789.4532;
  char initial = 'A';
  char first_name[] = "Zed";
  char last_name[] = "Shaw";

  printf("You are %d miles away.\n", distance);
  printf("You have %f levels of power.\n", power);
  printf("You have %f awesome super powers.\n", super_power);
  printf("I have a middle initial %c.\n", initial);
  printf("I have a first name %s.\n", first_name);
  printf("I have a last name %s.\n", last_name);
  printf("My whole name is %s %c. %s.\n", first_name, initial, last_name);

  // Extra Credit
  printf("This is the octal digit format without a hash char %o\n", distance);
  printf("This is the octal digit format with a hash char %#o\n", distance);

  printf("This is the hex digit format without a hash char %x\n", distance);
  printf("This is the hex digit format with a hash char %#x\n", distance);

  printf("This is the digit format with left alignment %- 10d\n", distance);
  printf("This is the digit format with right alignment % 10d\n", distance);

  // printf("This is the digit format with left alignment ignoring 0 padding %-010d\n", distance);
  printf("This is the digit format with right alignment, 0 padding %010d\n", distance);

  printf("super_power in '%%e' format with precision 2 %.2e\n", super_power);
  printf("super_power in '%%g' format %g.\n", super_power);
  printf("super_power in '%%a' format with precision 3 %.3a.\n", super_power);
  return 0;
}
