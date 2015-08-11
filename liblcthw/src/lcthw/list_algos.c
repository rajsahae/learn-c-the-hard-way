#include "list_algos.h"

int List_bubble_sort(List* list, List_compare comparator)
{
/*
 * procedure bubbleSort( A : list of sortable items )
 *    n = length(A)
 *    repeat 
 *      swapped = false
 *      for i = 1 to n-1 inclusive do
 *        // if this pair is out of order
 *        if A[i-1] > A[i] then
 *          // swap them and remember something changed
 *          swap( A[i-1], A[i] )
 *          swapped = true
 *        end if
 *      end for
 *    until not swapped
 * End procedure
 */
  return 0;
}

List* List_merge_sort(List* list, List_compare comparator)
{
  /*
   * function merge_sort(list m)
   *  // Base case. A list of zero or one elements is sorted, by definition.
   *  if length(m) <= 1
   *      return m

   *  // Recursive case. First, *divide* the list into equal-sized sublists.
   *  var list left, right
   *  var integer middle = length(m) / 2
   *  for each x in m before middle
   *       add x to left
   *  for each x in m after or equal middle
   *       add x to right

   *  // Recursively sort both sublists
   *  left = merge_sort(left)
   *  right = merge_sort(right)
   *  
   *  // Then merge the now-sorted sublists.
   *  return merge(left, right)
   */
  return NULL;
}
