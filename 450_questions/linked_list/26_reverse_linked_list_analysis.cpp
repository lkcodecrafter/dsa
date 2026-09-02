/*
    QUESTION    : Can we reverse a linked list in less than O(n)?
    Company Tags: Conceptual Interview Question (Amazon, Google, Microsoft)
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// Analysis & XOR Linked List Concept
/*
 * Question: Can we reverse a singly linked list in less than O(N) time?
 *
 * Direct Answer: NO for standard Singly Linked Lists, but YES (O(1)) for specialized XOR Linked Lists or wrapper views.
 *
 * Breakdown:
 * 1. Standard Singly Linked List:
 *    - To physically reverse the pointers, every single node's `next` pointer must be redirected.
 *    - Because there are N nodes, we MUST access all N nodes at least once -> Lower Bound is Ω(N).
 *
 * 2. XOR Linked List (Memory Efficient DLL):
 *    - Each node stores `npx = prev ^ next`.
 *    - To reverse an XOR linked list in O(1) time:
 *      Simply swap the global `head` and `tail` pointers!
 *      Traversing from tail automatically navigates backwards because `curr ^ prev` yields next!
 *
 * 3. Double-Ended Queue / Wrapper View:
 *    - Maintain a `reversed` boolean flag in the wrapper class.
 *    - Toggling the flag takes O(1) time without modifying individual nodes.
 */

// Demonstration of XOR Linked List Node
struct XORNode {
    int data;
    XORNode* npx; // XOR of prev and next node pointers
};

// Helper function to XOR two pointer addresses
XORNode* XOR(XORNode* a, XORNode* b) {
    return (XORNode*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

class XORLinkedList {
public:
    XORNode* head = nullptr;
    XORNode* tail = nullptr;

    // Reversing XOR Linked List takes O(1) time!
    void reverse() {
        swap(head, tail);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Singly LL: Strict lower bound is $\Omega(N)$ because $N$ pointers must be modified.
 * - XOR LL / DLL: Can be reversed in $O(1)$ by swapping `head` and `tail` pointers.
 */
