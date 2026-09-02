/*
    QUESTION    : Count pairs from 2 BST whose sum is equal to given value X
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/brothers-from-different-root/1
*/

#include <iostream>
#include <stack>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N1 + N2) - Two-pointer-like bidirectional inorder traversal using two iterative stacks
// S.C : O(H1 + H2) - Stacks maintain only path from root to current node
class Solution {
public:
    int countPairs(Node* root1, Node* root2, int x) {
        if (root1 == nullptr || root2 == nullptr) return 0;

        // st1 simulates standard forward inorder (ascending) on BST 1
        stack<Node*> st1;
        // st2 simulates reverse inorder (descending) on BST 2
        stack<Node*> st2;

        Node* curr1 = root1;
        Node* curr2 = root2;

        int pairsCount = 0;

        while (true) {
            // Push left spine of BST 1
            while (curr1 != nullptr) {
                st1.push(curr1);
                curr1 = curr1->left;
            }

            // Push right spine of BST 2
            while (curr2 != nullptr) {
                st2.push(curr2);
                curr2 = curr2->right;
            }

            // If either traversal completes, no more pairs possible
            if (st1.empty() || st2.empty()) break;

            Node* top1 = st1.top();
            Node* top2 = st2.top();

            int sum = top1->data + top2->data;

            if (sum == x) {
                pairsCount++;
                st1.pop();
                st2.pop();
                curr1 = top1->right; // Move to next in BST 1
                curr2 = top2->left;  // Move to next in BST 2
            } else if (sum < x) {
                // Sum is too small -> increase value from BST 1
                st1.pop();
                curr1 = top1->right;
            } else {
                // Sum is too large -> decrease value from BST 2
                st2.pop();
                curr2 = top2->left;
            }
        }

        return pairsCount;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TWO-BST ITERATIVE TWO-POINTERS
 * ============================================================================
 *
 * BST 1 (Forward Inorder -> Ascending): 2 -> 4 -> 5 -> 7 -> 8
 * BST 2 (Reverse Inorder -> Descending): 18 -> 15 -> 11 -> 10 -> 6 -> 3
 * Target X = 16
 *
 * Step 1: 2 + 18 = 20 > 16 -> Advance BST 2 (Next is 15)
 * Step 2: 2 + 15 = 17 > 16 -> Advance BST 2 (Next is 11)
 * Step 3: 2 + 11 = 13 < 16 -> Advance BST 1 (Next is 4)
 * Step 4: 4 + 11 = 15 < 16 -> Advance BST 1 (Next is 5)
 * Step 5: 5 + 11 = 16 == 16 -> MATCH FOUND! Advance both.
 * Step 6: 7 + 10 = 17 > 16 -> Advance BST 2 (Next is 6)
 * Step 7: 7 + 6  = 13 < 16 -> Advance BST 1 (Next is 8)
 * Step 8: 8 + 6  = 14 < 16 -> Advance BST 1 (End)
 *
 * Total Pairs = 1.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Use two stacks: `st1` for BST1 forward Inorder, `st2` for BST2 reverse Inorder.
 * - If `top1->data + top2->data == x`: count++, advance both.
 * - If `< x`: advance `st1` (`curr1 = top1->right`).
 * - If `> x`: advance `st2` (`curr2 = top2->left`).
 * - Time: O(N1 + N2), Space: O(H1 + H2).
 */
