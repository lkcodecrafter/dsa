/*
    QUESTION    : Multiply two numbers represented by Linked Lists
    Company Tags: Amazon, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/multiply-two-linked-lists/1
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
// T.C : O(N + M) - Linear traversal to convert both linked lists into numbers modulo 10^9 + 7
// S.C : O(1)     - Constant space
class Solution {
public:
    long long multiplyTwoLists(Node *first, Node *second) {
        long long MOD = 1000000007;
        long long num1 = 0;
        long long num2 = 0;

        // Convert first linked list to integer
        while (first != nullptr) {
            num1 = ((num1 * 10) % MOD + first->data) % MOD;
            first = first->next;
        }

        // Convert second linked list to integer
        while (second != nullptr) {
            num2 = ((num2 * 10) % MOD + second->data) % MOD;
            second = second->next;
        }

        return (num1 * num2) % MOD;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `num = (num * 10 + curr->data) % MOD`.
 * - Return `(num1 * num2) % MOD`.
 * - Time: O(N + M), Space: O(1).
 */
