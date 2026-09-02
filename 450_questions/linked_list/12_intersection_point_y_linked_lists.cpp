/*
    QUESTION    : Intersection Point of two Linked Lists (Y shaped)
    Company Tags: Amazon, Microsoft, Qualcomm, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/intersection-point-in-y-shapped-linked-lists/1
    LeetCode    : https://leetcode.com/problems/intersection-of-two-linked-lists/
*/

#include <iostream>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N + M) - Two pointers traverse (N + M) nodes each to synchronize at intersection
// S.C : O(1)     - Constant space
class Solution {
public:
    int intersectPoint(Node* head1, Node* head2) {
        if (head1 == nullptr || head2 == nullptr) return -1;

        Node* ptr1 = head1;
        Node* ptr2 = head2;

        // When ptr1 reaches end, redirect it to head2; when ptr2 reaches end, redirect to head1
        // Both will travel exactly (len1 + len2) distance and meet at the intersection point!
        while (ptr1 != ptr2) {
            ptr1 = (ptr1 == nullptr) ? head2 : ptr1->next;
            ptr2 = (ptr2 == nullptr) ? head1 : ptr2->next;
        }

        return (ptr1 != nullptr) ? ptr1->data : -1;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 2-POINTER SYNCHRONIZED TRAVERSAL
 * ============================================================================
 *
 * List 1: a1 -> a2 \
 *                   c1 -> c2 -> c3 (Intersection at c1)
 * List 2: b1 -> b2 -> b3 /
 *
 * ptr1 travels: a1 -> a2 -> c1 -> c2 -> c3 -> b1 -> b2 -> b3 -> [c1]
 * ptr2 travels: b1 -> b2 -> b3 -> c1 -> c2 -> c3 -> a1 -> a2 -> [c1]
 * Total steps before meeting = len(A) + len(B) - len(Common)!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `while (ptr1 != ptr2)`:
 *     - `ptr1 = (ptr1 == nullptr) ? head2 : ptr1->next;`
 *     - `ptr2 = (ptr2 == nullptr) ? head1 : ptr2->next;`
 * - Return `ptr1 ? ptr1->data : -1`.
 * - Time: O(N + M), Space: O(1).
 */
