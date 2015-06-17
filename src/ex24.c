#include <stdio.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
  BLUE_EYES, GREEN_EYES, BROWN_EYES, BLACK_EYES, OTHER_EYES
} EyeColor;

const char* EYE_COLOR_NAMES[] = {
  "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
  int age;
  char first_name[MAX_DATA];
  char last_name[MAX_DATA];
  EyeColor eyes;
  float income;
} Person;


int main(int argc, char* argv[])
{
  Person you = {.age = 0};
  char* in   = NULL;
  int rc     = 0;
  int i      = 0;
  int eyes   = -1;

  printf("What's your First Name? ");
  in = fgets(you.first_name, MAX_DATA, stdin);
  check(in != NULL, "Failed to read first name");

  printf("What's your Last Name? ");
  in = fgets(you.last_name, MAX_DATA, stdin);
  check(in != NULL, "Failed to read last name");

  printf("How old are you? ");
  rc = fscanf(stdin, "%d", &you.age);
  check(rc > 0, "You have to enter a number.");

  printf("What color are your eyes?\n");
  for(i = 0; i <= OTHER_EYES; i++) {
    printf("%4d) %s\n", i+1, EYE_COLOR_NAMES[i]);
  }
  printf("> ");

  rc = fscanf(stdin, "%d", &eyes);
  check(rc > 0, "You have to enter a number");

  you.eyes = eyes - 1;
  check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option");

  printf("----- Results -----\n");

  printf("%10s: %s"  , "First Name", you.first_name           );
  printf("%10s: %s"  , "Last Name" , you.last_name            );
  printf("%10s: %d\n", "Age"       , you.age                  );
  printf("%10s: %s\n", "Eyes"      , EYE_COLOR_NAMES[you.eyes]);
  printf("%10s: %f\n", "Income"    , you.income               );

  return 0;

error:
  return -1;
}
