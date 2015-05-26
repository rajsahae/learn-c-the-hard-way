#include <stdio.h>

int main(int argc, char* argv[])
{
  // go through each string in argv
  
  int i = 0;
  while(i < argc) {
    printf("arg %d: %s\n", i, argv[i]);
    i++;
  }

  // let's make our own array of strings
  int num_states = 4;
  char *states[] = { "California", "Oregon", "Washington", "Texas" };

  i = 0; // watch for this
  while(i < num_states) {
    printf("state %d: %s\n", i, states[i]);
    i++;
  }

  // Extra Credit

  // print backwards
  i = argc - 1;
  while(i >= 0) {
    printf("arg %d: %s\n", i, argv[i]);
    i--;
  }

  return 0;
}
