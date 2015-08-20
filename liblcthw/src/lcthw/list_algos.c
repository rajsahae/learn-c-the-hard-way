#include "dbg.h"
#include "list_algos.h"

// Helper method to swap node values.
// We don't need to move the actual nodes around. Just swap the values
void swap_list_nodes(ListNode* node1, ListNode* node2)
{
  void* temp_value = node1->value;
  node1->value = node2->value;
  node2->value = temp_value;
}

int List_bubble_sort(List* list, List_compare comparator)
{
  int swapped = 1;

  while(List_count(list) > 0 && swapped) {
    swapped = 0;
    LIST_FOREACH(list, first->next, next, cur) {
      if (comparator(cur->prev->value, cur->value) > 0) {
        swap_list_nodes(cur->prev, cur);
        swapped = 1;
      }
    }
  }

  return 0;
}

/*
 * This assumes we are given two sorted lists
 * We should return a List pointer to a single sorted list
 * The function also assumes that neither list is empty
 */
List* List_merge(List* left, List* right, List_compare comparator)
{
  check(left != NULL, "left List* should not be NULL");
  check(right != NULL, "right List* should not be NULL");

  check(List_count(left),  "left List should not be empty");
  check(List_count(right),  "right List should not be empty");

  List* result = List_create();

  while (List_count(left) > 0 && List_count(right) > 0) {
    if (comparator(List_first(left), List_first(right)) <= 0) {
      List_push(result, List_shift(left));
    } else {
      List_push(result, List_shift(right));
    }
  }

  while (List_count(left) > 0) {
    List_push(result, List_shift(left));
  }

  while (List_count(right) > 0) {
    List_push(result, List_shift(right));
  }

  return result;

error:
  return NULL;
}

/*
 * Takes a List and a comparator function pointer and performs
 * a merge sort on the List. List is modified by the function.
 */
List* List_merge_sort(List* list, List_compare comparator)
{
  int size = List_count(list);
  if (List_count(list) <= 1) {
    return list;
  }
   
  List* left;
  List* right;
  int left_count = size / 2;

  List_split(list, left_count, &left, &right); 

  left = List_merge_sort(left, comparator);
  right = List_merge_sort(right, comparator);

  List* merged = List_merge(left, right, comparator);

  List_destroy(left);
  List_destroy(right);

  return merged;
}
