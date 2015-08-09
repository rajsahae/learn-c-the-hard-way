#ifndef __lcthw_List_H_
#define __lcthw_List_H_

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
  struct ListNode* next;
  struct ListNode* prev;
  void* value;
} ListNode;

typedef struct List {
  int count;
  ListNode* first;
  ListNode* last;
} List;

List* List_create();
void  List_clear_destroy(List* list);

int   List_count(List* list);
void* List_first(List* list);
void* List_last(List* list);

void  List_push(List* list, void* node);
void* List_pop(List* list);

void  List_unshift(List* list, void* value);
void* List_shift(List* list);

void* List_remove(List* list, ListNode* node);

#define LIST_FOREACH(L, S, M, V) ListNode* _node = NULL;\
  ListNode* V = NULL;\
  for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
