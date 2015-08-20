#include "lcthw/list.h"
#include "dbg.h"

List* List_create()
{
  return calloc(1, sizeof(List));
}

void List_destroy(List* list)
{
  if (list == NULL) {
    return;
  }

  LIST_FOREACH(list, first, next, cur) {
    if(cur->prev) {
      free(cur->prev);
    }
  }

  if (list->last) {
    free(list->last);
  }

  if (list)
    free(list);
}

int List_count(List* list)
{
  return list->count;
}

void* List_first(List* list)
{
  return list->first != NULL ? list->first->value : NULL;
}

void* List_last(List* list)
{
  return list->last != NULL ? list->last->value : NULL;
}

void List_push(List* list, void* value)
{
  ListNode *node = calloc(1, sizeof(ListNode));
  check_mem(node);

  node->value = value;

  if (list->last == NULL) {
    list->first = node;
    list->last = node;
  } else {
    list->last->next = node;
    node->prev = list->last;
    list->last = node;
  }

  list->count++;

error:
  return;
}

void* List_pop(List* list)
{
  ListNode* node = list->last;
  return node != NULL ? List_remove(list, node) : NULL;
}

void  List_unshift(List* list, void* value)
{
  ListNode *node = calloc(1, sizeof(ListNode));
  check_mem(node);

  node->value = value;

  if (list->first == NULL) {
    list->first = node;
    list->last = node;
  } else {
    node->next = list->first;
    list->first->prev = node;
    list->first = node;
  }

  list->count++;

error:
  return;
}

void* List_shift(List* list)
{
  ListNode* node = list->first;
  return node != NULL ? List_remove(list, node) : NULL;
}

void* List_remove(List* list, ListNode* node)
{
  void* result = NULL;

  check(list->first && list->last, "List is empty");
  check(node, "node can't be NULL");

  if(node == list->first && node == list->last) {
    list->first = NULL;
    list->last = NULL;
  } else if (node == list->first) {
    check(node->next != NULL, "Invalid list. Second item was NULL somehow");
    list->first = node->next;
    list->first->prev = NULL;
  } else if (node == list->last) {
    check(node->prev != NULL, "Invalid list. Second to last item was NULL somehow");
    list->last = node->prev;
    list->last->next = NULL;
  } else {
    ListNode* after = node->next;
    ListNode* before = node->prev;
    after->prev = before;
    before->next = after;
  }

  list->count--;
  result = node->value;
  free(node);

error:
  return result;
}

/*
 * Takes a list and a count.
 * list = List to split
 * count = number of items that should be in the left list
 * left = List pointer that will be assigned to left list
 * right = List pointer that will be assigned to right list
 *
 * Original list is modified to create split lists. Old list will be empty
 * once the split is complete
 */
int List_split(List* list, int count, List** p_left, List** p_right)
{
  check(list != NULL, "List provided is NULL");
  check(count > 0, "Split count invalid: %d", count);

  int size = List_count(list);
  check(count <= size, "Split count (%d) greater than List size (%d)", count, size);

  *p_left = List_create();
  *p_right = List_create();

  List* left = *p_left;
  List* right = *p_right;

  int i = 0;
  while(i++ < count) {
    List_push(left, List_shift(list));
  }

  i = 0;
  while(i++ < size - count) {
    List_push(right, List_shift(list));
  }

  return 0;

error:
  return 1;
}

int List_print(List* list, const char* name)
{
  check(list != NULL, "Cannot print NULL list");

  int i = 1;
  LIST_FOREACH(list, first, next, cur) {
    check(cur != NULL, "Cannot print NULL ListNode");
    printf("List(%s) Node(%d): %s\n", name, i++, cur->value);
  }

  return 0;
error:
  return 1;
}
