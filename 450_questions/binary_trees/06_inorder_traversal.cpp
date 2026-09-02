/*
    QUESTION    : Inorder Tree Traversal (Recursive and Iterative)
    Company Tags: Amazon, Microsoft, Adobe
    Link        : https://www.techiedelight.com/inorder-tree-traversal-iterative-recursive/
    LeetCode    : https://leetcode.com/problems/binary-tree-inorder-traversal/
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
    // Iterative Inorder Traversal using explicit Stack (Left -> Root -> Right)
    vector<int> inOrder(Node* root) {
        vector<int> result;
        stack<Node*> st;
        Node* curr = root;

        while (curr != nullptr || !st.empty()) {
            // 1. Reach the leftmost node of current subtree, pushing all ancestors
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }

            // 2. curr is nullptr here; pop top node from stack (leftmost available)
            curr = st.top();
            st.pop();

            result.push_back(curr->data);

            // 3. We have visited the node and its left subtree; now move to right subtree
            curr = curr->right;
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF ITERATIVE STACK INORDER
 * ============================================================================
 *
 *               1
 *             /   \
 *            2     3
 *          /   \
 *         4     5
 *
 * 1. Push 1, 2, 4 -> st: [1, 2, 4]
 * 2. Pop 4 -> Result: [4]. curr = 4->right (null)
 * 3. Pop 2 -> Result: [4, 2]. curr = 2->right (5) -> push 5
 * 4. Pop 5 -> Result: [4, 2, 5]. curr = 5->right (null)
 * 5. Pop 1 -> Result: [4, 2, 5, 1]. curr = 1->right (3) -> push 3
 * 6. Pop 3 -> Result: [4, 2, 5, 1, 3]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `while (curr != nullptr || !st.empty())`:
 *     - `while (curr != nullptr) { st.push(curr); curr = curr->left; }`
 *     - `curr = st.top(); st.pop(); result.push_back(curr->data);`
 *     - `curr = curr->right;`
 * - Time: O(N), Space: O(H).
 */
