#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/** Our old friend die from ex17 **/
void die(const char* message)
{
  if ( errno ) {
    perror(message);
  }
  else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

// a typedef creates a fake type, in this case for a function pointer
typedef int (*compare_cb)(int a, int b);

// Create typedef for sort function
typedef int* (*sort_cb)(int* numbers, int count, compare_cb cmp);

/*
 * Basic swap function
 * I added this myself because I think it's cleaner
 */
void swap(int* a, int* b)
{
  int temp = 0;
  temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * A classic bubble sort function that uses the compare_cb to do the sorting
 */
int* bubble_sort(int* numbers, int count, compare_cb cmp)
{
  int* target = malloc(count * sizeof(int));
  if ( !target ) die("Memory error.");

  memcpy(target, numbers, count * sizeof(int));

  int i = 0, j = 0;
  for ( i = 0 ; i < count ; i++ ) {
    for ( j = 0 ; j < count - 1 ; j++ ) {
      if ( cmp(target[j], target[j+1]) > 0 ) {
        swap(&target[j], &target[j+1]);
      }
    }
  }

  return target;
}

int* selection_sort(int* numbers, int count, compare_cb cmp)
{
  int* target = malloc(count * sizeof(int));
  if ( !target ) die("Memory error");

  memcpy(target, numbers, count * sizeof(int));

  int i = 0, j = 0, min = 0;

  for ( i = 0 ; i < count ; i++ ) {

    min = i;

    for ( j = i + 1 ; j < count ; j++ ) {
      if ( cmp(target[min], target[j]) > 0 ) {
        min = j;
      }
    }

    if ( i != min ) {
      swap(&target[i], &target[min]);
    }
  }

  return target;
}

int sorted_order(int a, int b)
{
  return a - b;
}

int reverse_order(int a, int b)
{
  return b - a;
}

int strange_order(int a, int b)
{
  if ( a == 0 || b == 0 ) {
    return 0;
  }
  else {
    return a % b;
  }
}

int random_order(int a, int b)
{
  if ( rand() % 2 == 0 ) {
    return -1;
  }
  else {
    return 1;
  }
}

/**
 * Used to test that we are sorting things correctly by doing the sort and
 * printing it out
 */
void test_sorting(int *numbers, int count, sort_cb sort, compare_cb cmp)
{
  int i = 0;
  int* sorted = sort(numbers, count, cmp);

  if ( !sorted ) die("Failed to sort as requested");

  for ( i = 0 ; i < count ; i++ ) {
    printf("%d ", sorted[i]);
  }
  printf("\n");

  free(sorted);

  /*
  unsigned char* data = (unsigned char *)cmp;

  for ( i = 0 ; i < 25 ; i++ ) {
    printf("%02x:", data[i]);
  }
  printf("\n");
  */
}

int main(int argc, char* argv[])
{
  if ( argc < 2 ) die("USAGE: ex18 4 3 1 5 6");

  int count = argc - 1;
  int i = 0;
  char** inputs = argv + 1;

  int* numbers = malloc(count * sizeof(int));
  if ( !numbers ) die("Memory error");

  for ( i = 0 ; i < count ; i++ ) {
    numbers[i] = atoi(inputs[i]);
  }

  printf("Bubble sorts\n");
  test_sorting(numbers, count, bubble_sort, sorted_order);
  test_sorting(numbers, count, bubble_sort, reverse_order);
  test_sorting(numbers, count, bubble_sort, strange_order);
  test_sorting(numbers, count, bubble_sort, random_order);

  printf("\nSelection sorts\n");
  test_sorting(numbers, count, selection_sort, sorted_order);
  test_sorting(numbers, count, selection_sort, reverse_order);
  test_sorting(numbers, count, selection_sort, strange_order);
  test_sorting(numbers, count, selection_sort, random_order);

  free(numbers);

  return 0;
}
