#include "minunit.h"
#include "lcthw/list.h"

static List* list = NULL;
char* test1 = "test1 data";
char* test2 = "test2 data";
char* test3 = "test3 data";

char* test_create()
{
  list = List_create();
  mu_assert(list != NULL, "Failed to create list")

  return NULL;
}

char* test_destroy()
{
  List_destroy(list);
  return NULL;
}

char* test_push_pop()
{
  List_push(list, test1);
  mu_assert(List_first(list) == test1, "1st Push failed: wrong first value");
  mu_assert(List_last(list) == test1, "1st Push failed: wrong last value");
  mu_assert(List_count(list) == 1, "1st Push failed: wrong list count");

  List_push(list, test2);
  mu_assert(List_first(list) == test1, "2nd Push failed: wrong first value");
  mu_assert(List_last(list) == test2, "2nd Push failed: wrong last value");
  mu_assert(List_count(list) == 2, "2nd Push failed: wrong list count");

  List_push(list, test3);
  mu_assert(List_first(list) == test1, "3rd Push failed: wrong first value");
  mu_assert(List_last(list) == test3, "3rd Push failed: wrong last value");
  mu_assert(List_count(list) == 3, "3rd Push failed: wrong list count");

  char* val = List_pop(list);
  mu_assert(val == test3, "Wrong value on pop");
  mu_assert(List_count(list) == 2, "1st pop failed: wrong list count");

  val = List_pop(list);
  mu_assert(val == test2, "Wrong value on pop");
  mu_assert(List_count(list) == 1, "2nd pop failed: wrong list count");

  val = List_pop(list);
  mu_assert(val == test1, "Wrong value on pop");
  mu_assert(List_count(list) == 0, "3rd pop failed: wrong list count");

  return NULL;
}

char* test_unshift()
{
  List_unshift(list, test1);
  mu_assert(List_first(list) == test1, "1st unshift. Wrong first value");

  List_unshift(list, test2);
  mu_assert(List_first(list) == test2, "2nd unshift. Wrong first value");

  List_unshift(list, test3);
  mu_assert(List_first(list) == test3, "3rd unshift. Wrong first value");
  mu_assert(List_count(list) == 3, "3rd unshift. Wrong count");

  return NULL;
}

char* test_remove()
{
  /* We only need to test the middle remove case since push/shift
   * already tests the other cases
   */

  char* val = List_remove(list, list->first->next);
  mu_assert(val == test2, "Removed wrong element");
  mu_assert(List_count(list) == 2, "Wrong count after remove");
  mu_assert(List_first(list) == test3, "Wrong first after remove");
  mu_assert(List_last(list) == test1, "Wrong last after remove");

  return NULL;
}

char* test_shift()
{
  mu_assert(List_count(list) != 0, "Wrong count before shift");

  char* val = List_shift(list);
  mu_assert(val == test3, "Wrong value on shift");

  val = List_shift(list);
  mu_assert(val == test1, "Wrong value on shift");
  mu_assert(List_count(list) == 0, "Wrong count after shift");

  return NULL;
}

char* test_split()
{
  List* new_list = List_create();
  List_push(new_list, test1);
  List_push(new_list, test2);
  List_push(new_list, test3);

  mu_assert(List_count(new_list) == 3, "List doesn't have expected size of 3");

  List* left = NULL;
  List* right = NULL;

  int rc = List_split(new_list, 4, &left, &right);
  mu_assert(rc == 1, "Split succeeded unexpectedly");
    
  rc = List_split(new_list, 2, &left, &right);
  mu_assert(rc == 0, "Split failed unexpectedly");

  mu_assert(left != NULL, "Left list still NULL");
  mu_assert(right != NULL, "Right list still NULL");

  debug("List_count(left): %d", List_count(left));
  debug("List_count(right): %d", List_count(right));

  mu_assert(List_count(left) == 2, "Left list doesn't have correct size");
  mu_assert(List_count(right) == 1, "Right list doesn't have correct size");

  mu_assert(List_first(left) == test1, "Left list first value incorrect");
  mu_assert(List_last(left) == test2, "Left list last value incorrect");

  mu_assert(List_first(right) == test3, "Right list first value incorrect");
  mu_assert(List_last(right) == test3, "Right list last value incorrect");

  List_destroy(new_list);
  List_destroy(left);
  List_destroy(right);

  return NULL;
}

char* test_print()
{
  int rc = List_print(list, "testlist");
  mu_assert(rc == 0, "Failed to print list");

  return NULL;
}

char* all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_push_pop);
  mu_run_test(test_unshift);
  mu_run_test(test_print);
  mu_run_test(test_split);
  mu_run_test(test_remove);
  mu_run_test(test_shift);
  mu_run_test(test_destroy);

  return NULL;
}

RUN_TESTS(all_tests);
