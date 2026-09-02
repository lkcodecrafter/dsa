/*
    QUESTION    : Find pairs with a given sum in a sorted Doubly Linked List
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/find-pairs-given-sum-doubly-linked-list/
*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for doubly-linked list node
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Two-pointer technique (left starts at head, right starts at tail)
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    vector<pair<int, int>> findPairsWithGivenSum(Node *head, int target) {
        vector<pair<int, int>> result;
        if (head == nullptr) return result;

        Node* left = head;
        Node* right = head;

        // Move right pointer to the tail of the DLL
        while (right->next != nullptr) {
            right = right->next;
        }

        // Two-pointer sweep until left and right pointers cross
        while (left != right && right->next != left) {
            int currentSum = left->data + right->data;

            if (currentSum == target) {
                result.push_back({left->data, right->data});
                left = left->next;
                right = right->prev;
            } else if (currentSum < target) {
                left = left->next;
            } else {
                right = right->prev;
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `left = head`, `right = tail`.
 * - While `left != right && right->next != left`:
 *     - If `left->data + right->data == target`: add pair, `left = left->next; right = right->prev;`
 *     - If `< target`: `left = left->next;`
 *     - Else: `right = right->prev;`
 * - Time: O(N), Space: O(1).
 */
