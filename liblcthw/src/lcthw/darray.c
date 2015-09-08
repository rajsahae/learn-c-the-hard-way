#include "lcthw/darray.h"
#include "dbg.h"

DArray* DArray_create(size_t element_size, size_t initial_max)
{
  DArray* array = malloc(sizeof(DArray));
  check_mem(array);

  array->max = initial_max;
  check(array->max > 0, "You must set an initial_max > 0");

  array->end = 0;
  array->element_size = element_size;
  check(element_size > 0, "You must set an element_size > 0");

  array->expand_rate = DEFAULT_EXPAND_RATE;
  array->contents = calloc(initial_max, sizeof(void*));

  return array;

error:
  if(array) free(array);
  return NULL;
}

void DArray_clear(DArray* array)
{
  int i = 0;
  for(i = 0; i < array->max; i++) {
    if (array->contents[i] != NULL) {
      free(array->contents[i]);
    }
  }
}

void DArray_destroy(DArray* array)
{
  if (array->contents)
    DArray_free(array->contents);

  if (array)
    DArray_free(array);
}

void DArray_clear_destroy(DArray* array)
{
  DArray_clear(array);
  DArray_destroy(array);
}

static int DArray_resize(DArray* array, int new_size)
{
  debug("Resizing array - Old size: %d, New size: %d", array->max, new_size);
  void* new_contents = realloc(array->contents, new_size * sizeof(void*));
  check_mem(new_contents);
  debug("Realloc finished");

  array->max      = new_size;
  array->contents = new_contents;

  debug("Finished resizing array - New size: %d", array->max);

  return 0;
error:
  return -1;
}


void DArray_expand(DArray* array)
{
  size_t new_max     = array->max + array->expand_rate;
  debug("Expanding array with old max: %d, new max: %ld", array->max, new_max);

  int result = DArray_resize(array, new_max);
  check(result == 0, "Could not resize darray");

  debug("Finished expanding array with new max: %d", array->max);

error:
  return;
}

void DArray_contract(DArray* array)
{
  size_t new_max = array->max - array->expand_rate;
  if (new_max < array->expand_rate) {
    new_max = array->expand_rate;
  }
  debug("Contracting array with old max: %d, new max: %ld", array->max, new_max);

  int result = DArray_resize(array, new_max);
  check(result == 0, "Could not resize darray");

  debug("Finished contracting array with new max: %d", array->max);

error:
  return;
}

void DArray_push(DArray* array, void* el)
{
  debug("Pushing onto array with end %d", array->end);

  if (array->end >= array->max) {
    DArray_expand(array);
  }
  check(array->end <= array->max,
      "DArray_push: failed to expand array. End: %d Max %d",
      array->end, array->max); 

  DArray_set(array, array->end++, el);

  debug("Finished pushing onto array with new end %d", array->end);

error:
  return;
}

void* DArray_pop(DArray* array)
{
  debug("Popping from array with end %d", array->end);

  void* el = DArray_remove(array, --array->end);

  int lower_limit = array->max - array->expand_rate;
  if (array->end < lower_limit) {
    DArray_contract(array);
  }
  check(array->end <= array->max,
      "DArray_pop: failed to contract array. End: %d Max %d, Lower Limit: %d",
      array->end, array->max, lower_limit); 

  debug("Finished popping from array with new end %d", array->end);

  return el;

error:
  return NULL;
}
