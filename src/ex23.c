#include <stdio.h>
#include <string.h>

#include "dbg.h"

int normal_copy(char* from, char* to, int count)
{
  int i = 0;
  for(i = 0; i < count; i++) {
    to[i] = from[i];
  }

  return i;
}

int rajs_copy(char* from, char* to, int count)
{
  int i = 0;
  for(i = 0; i < count; i++) {
    *to++ = *from++;
  }

  return i;
}

int rajs_second_copy(char* from, char* to, int count)
{
  check( count > 0, "Count less than 1: %d", count );

  do {
    *to++ = *from++;
  } while ( --count > 0 );
    
  return count;

error:
  return -1;
}

int duffs_device(char* from, char* to, int count) {
  {
    int n = (count + 7 ) / 8;

    switch(count % 8) {
      case 0: do {
                *to++ = *from++;
                case 7: *to++ = *from++;
                case 6: *to++ = *from++;
                case 5: *to++ = *from++;
                case 4: *to++ = *from++;
                case 3: *to++ = *from++;
                case 2: *to++ = *from++;
                case 1: *to++ = *from++;
              } while (--n > 0);
    }
  }

  return count;
}

int zeds_device(char* from, char* to, int count)
{
  {
    int n = (count + 7) / 8;

    switch(count % 8) {
      case 0:
      again: *to++ = *from++;

      case 7: *to++ = *from++;
      case 6: *to++ = *from++;
      case 5: *to++ = *from++;
      case 4: *to++ = *from++;
      case 3: *to++ = *from++;
      case 2: *to++ = *from++;
      case 1: *to++ = *from++;
              if(--n > 0) goto again;
    }
  }

  return count;
}

int valid_copy(char* data, int count, char expects)
{
  int i = 0;
  for(i = 0; i < count; i++) {
    if(data[i] != expects) {
      log_err("[%d] %c != %c", i, data[i], expects);
      return 0;
    }
  }

  return 1;
}

int main(int argc, char* argv[])
{
  char from[1000] = {'a'};
  char to[1000] = {'c'};
  int rc = 0;
  int count = 1000;

  // setup the from to have some stuff
  memset(from, 'x', count);
  // set it to a failure mode
  memset(to, 'y', count);
  check(valid_copy(to, count, 'y'), "Not initialized right");

  // use normal copy to
  rc = normal_copy(from, to, count);
  check(rc == count, "Normal copy failed: %d", rc);
  check(valid_copy(to, count, 'x'), "Normal copy failed");

  // reset
  memset(to, 'y', count);

  // use rajs copy to
  rc = rajs_copy(from, to, count);
  check(rc == count, "Rajs copy failed: %d", rc);
  check(valid_copy(to, count, 'x'), "Rajs copy failed");

  // reset
  memset(to, 'y', count);

  // use rajs second copy to
  rc = rajs_second_copy(from, to, count);
  check(rc == 0, "Rajs second copy failed: %d", rc);
  check(valid_copy(to, count, 'x'), "Rajs second copy failed");

  // reset
  memset(to, 'y', count);

  // use rajs second copy to for error
  rc = rajs_second_copy(from, to, 0);
  check(rc == -1, "Rajs second copy did not fail as expected: %d", rc);

  // reset
  memset(to, 'y', count);

  // duffs version
  rc = duffs_device(from, to, count);
  check(rc == count, "Duff's device failed: %d", rc);
  check(valid_copy(to, count, 'x'), "Duff's device failed copy");

  // reset
  memset(to, 'y', count);

  // my version
  rc = zeds_device(from, to, count);
  check(rc == count, "Zed's device failed: %d", rc);
  check(valid_copy(to, count, 'x'), "Zed's device failed copy");

  return 0;

error:

  return 1;

}
