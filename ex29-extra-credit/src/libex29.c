#include <stdio.h>
#include <ctype.h>
#include "dbg.h"

int print_a_message(const char* msg)
{
  printf("A STRING: %s\n", msg);
  return 0;
}

int uppercase(const char* msg, long len)
{
  check(len > 0, "msg length must be positive: %ld", len);

  long i = 0;
  for (i = 0; i < len; i++) {
    printf("%c", toupper(msg[i]));
  }

  printf("\n");

  return 0;

error:
  return 1;
}

int lowercase(const char* msg, long len)
{
  check(len > 0, "msg length must be positive: %ld", len);

  long i = 0;
  for (i = 0; i < len; i++) {
    printf("%c", tolower(msg[i]));
  }

  printf("\n");

  return 0;

error:
  return 1;
}

int fail_on_purpose(const char* msg)
{
  printf("A STRING: %s\n", msg);
  return 1;
}
