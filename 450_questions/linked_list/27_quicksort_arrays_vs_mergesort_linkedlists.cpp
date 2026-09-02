/*
    QUESTION    : Why Quicksort is preferred for Arrays and Merge Sort for LinkedLists?
    Company Tags: Conceptual Interview Question (Amazon, Microsoft, Google, Adobe)
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
/*
 * ============================================================================
 * DETAILED ARCHITECTURAL COMPARISON
 * ============================================================================
 *
 * 1. Why is QUICKSORT preferred for ARRAYS?
 *    - Memory Locality / Cache Performance: Arrays occupy contiguous blocks in physical RAM.
 *      Quicksort exhibits excellent spatial locality of reference (scanning elements sequentially),
 *      which maximizes CPU L1/L2 cache hits.
 *    - Auxiliary Space: Quicksort is an in-place sorting algorithm requiring only O(log N) stack space,
 *      whereas Merge Sort on arrays requires O(N) auxiliary allocation.
 *    - Random Access: Quicksort relies on O(1) random index access `arr[i]`, which arrays support natively.
 *
 * 2. Why is MERGE SORT preferred for LINKED LISTS?
 *    - Pointer Manipulations with O(1) Auxiliary Space: Unlike arrays, merging two linked lists
 *      does NOT require allocating new memory. We simply rewire existing `next` pointers in O(1) space!
 *    - No Random Access Needed: Merge Sort accesses elements strictly sequentially (slow & fast pointer to find mid),
 *      which matches the natural O(1) sequential traversal of linked lists.
 *    - Cache Performance Irrelevance: Linked list nodes are scattered arbitrarily across the heap,
 *      so neither algorithm gains significant cache locality advantages.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Arrays $\rightarrow$ Quicksort: Cache locality + $O(1)$ random indexing + in-place $O(1)$ space.
 * - Linked Lists $\rightarrow$ Merge Sort: Sequential access + in-place $O(1)$ pointer merging without extra array allocation.
 */

int main() {
    cout << "Quicksort for Arrays (Cache Locality + In-place)\n";
    cout << "MergeSort for Linked Lists (Sequential Access + Pointer Merge)\n";
    return 0;
}
