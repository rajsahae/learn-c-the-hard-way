#ifndef __LIST_ALGOS_H
#define __LIST_ALGOS_H

#include "lcthw/list.h"

typedef int (*List_compare)(void* node1, void* node2);
int List_bubble_sort(List* list, List_compare comparator);
List* List_merge_sort(List* list, List_compare comparator);

#endif
