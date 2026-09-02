/*
    QUESTION    : Preorder Tree Traversal (Recursive and Iterative)
    Company Tags: Amazon, Microsoft
    Link        : https://www.techiedelight.com/preorder-tree-traversal-iterative-recursive/
    LeetCode    : https://leetcode.com/problems/binary-tree-preorder-traversal/
*/

#include <iostream>
#include <vector>
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
// T.C : O(N) - Visits each node once
// S.C : O(H) - Stack depth equals height of binary tree
class Solution {
public:
    // Iterative Preorder Traversal using explicit Stack (Root -> Left -> Right)
    vector<int> preorder(Node* root) {
        vector<int> result;
        if (root == nullptr) return result;

        stack<Node*> st;
        st.push(root);

        while (!st.empty()) {
            Node* curr = st.top();
            st.pop();

            // Visit root first
            result.push_back(curr->data);

            // Push RIGHT child first so that LEFT child is processed first from stack top
            if (curr->right != nullptr) {
                st.push(curr->right);
            }
            if (curr->left != nullptr) {
                st.push(curr->left);
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF ITERATIVE STACK PREORDER
 * ============================================================================
 *
 *               1
 *             /   \
 *            2     3
 *          /   \
 *         4     5
 *
 * 1. Push 1 -> Pop 1, visit 1. Push 3, then 2. (st: [3, 2])
 * 2. Pop 2, visit 2. Push 5, then 4. (st: [3, 5, 4])
 * 3. Pop 4, visit 4. (st: [3, 5])
 * 4. Pop 5, visit 5. (st: [3])
 * 5. Pop 3, visit 3. (st: [])
 *
 * Result: [ 1, 2, 4, 5, 3 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `stack<Node*> st; st.push(root);`
 * - While `!st.empty()`:
 *     - `curr = st.top(); st.pop(); result.push_back(curr->data);`
 *     - If `curr->right` exists: `st.push(curr->right);`
 *     - If `curr->left` exists: `st.push(curr->left);`
 * - Time: O(N), Space: O(H).
 */
