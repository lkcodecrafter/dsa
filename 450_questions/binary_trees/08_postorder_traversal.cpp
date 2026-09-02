/*
    QUESTION    : Postorder Tree Traversal (Recursive and Iterative)
    Company Tags: Amazon, Microsoft, Adobe
    Link        : https://www.techiedelight.com/postorder-tree-traversal-iterative-recursive/
    LeetCode    : https://leetcode.com/problems/binary-tree-postorder-traversal/
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Visits each node once
// S.C : O(H) - Stack depth
class Solution {
public:
    // Iterative Postorder Traversal using 2 Stacks / Reversed Preorder (Left -> Right -> Root)
    vector<int> postOrder(Node* node) {
        vector<int> result;
        if (node == nullptr) return result;

        stack<Node*> st;
        st.push(node);

        // Traverse Root -> Right -> Left (Modified Preorder)
        while (!st.empty()) {
            Node* curr = st.top();
            st.pop();

            result.push_back(curr->data);

            if (curr->left != nullptr) {
                st.push(curr->left);
            }
            if (curr->right != nullptr) {
                st.push(curr->right);
            }
        }

        // Reverse the modified preorder result to obtain Postorder (Left -> Right -> Root)
        reverse(result.begin(), result.end());

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF POSTORDER REVERSED-PREORDER TRICK
 * ============================================================================
 *
 * Modified Preorder (Root -> Right -> Left):
 *               1
 *             /   \
 *            2     3
 *          /   \
 *         4     5
 *
 * Modified Preorder Output: [ 1, 3, 2, 5, 4 ]
 * Reversed:                 [ 4, 5, 2, 3, 1 ]  <-- True Postorder Traversal!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Modified Preorder (`Root -> Right -> Left`) is the exact mirror of Postorder (`Left -> Right -> Root`).
 * - Push `left` then `right` to stack, pop to `result`, then `std::reverse(result)`.
 * - Time: O(N), Space: O(H).
 */
