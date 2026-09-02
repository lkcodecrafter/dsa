/*
    QUESTION    : Count triplets in a sorted Doubly Linked List whose sum is equal to given value X
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/count-triplets-sorted-doubly-linked-list-whose-sum-equal-given-value-x/
*/

#include <iostream>

using namespace std;

// Definition for doubly-linked list node
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Outer loop selects first element, inner two pointers find pair with target (x - first)
// S.C : O(1)   - Constant auxiliary space
class Solution {
private:
    // Helper to count pairs with target sum in range [first->next, last]
    int countPairs(Node* first, Node* last, int target) {
        int count = 0;
        while (first != nullptr && last != nullptr && first != last && last->next != first) {
            int sum = first->data + last->data;
            if (sum == target) {
                count++;
                first = first->next;
                last = last->prev;
            } else if (sum < target) {
                first = first->next;
            } else {
                last = last->prev;
            }
        }
        return count;
    }

public:
    int countTriplets(Node* head, int x) {
        if (head == nullptr) return 0;

        Node* current = head;
        Node* tail = head;

        while (tail->next != nullptr) {
            tail = tail->next;
        }

        int tripletCount = 0;

        // Outer loop iterates through each possible first node
        for (current = head; current != nullptr; current = current->next) {
            Node* first = current->next;
            tripletCount += countPairs(first, tail, x - current->data);
        }

        return tripletCount;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Iterate `current` from `head` to `tail`.
 * - Run two-pointer `countPairs(current->next, tail, x - current->data)`.
 * - Time: O(N^2), Space: O(1).
 */
