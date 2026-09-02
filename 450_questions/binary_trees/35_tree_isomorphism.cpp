/*
    QUESTION    : Tree Isomorphism Problem
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/check-if-tree-is-isomorphic/1
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(min(N1, N2)^2) worst case, O(N) average case
// S.C : O(min(H1, H2)) - Recursion stack space
class Solution {
public:
    bool isIsomorphic(Node *root1, Node *root2) {
        // Case 1: Both trees are empty
        if (root1 == nullptr && root2 == nullptr) return true;

        // Case 2: Exactly one of the trees is empty
        if (root1 == nullptr || root2 == nullptr) return false;

        // Case 3: Values at current roots do not match
        if (root1->data != root2->data) return false;

        // Two possible isomorphism conditions:
        // Option A: Trees are isomorphic without swapping children (left matches left, right matches right)
        bool noSwap = isIsomorphic(root1->left, root2->left) &&
                      isIsomorphic(root1->right, root2->right);

        // Option B: Trees are isomorphic with children swapped (left matches right, right matches left)
        bool swapMatch = isIsomorphic(root1->left, root2->right) &&
                         isIsomorphic(root1->right, root2->left);

        return noSwap || swapMatch;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TREE ISOMORPHISM
 * ============================================================================
 *
 * Tree 1:            Tree 2:
 *       1                   1
 *     /   \               /   \
 *    2     3             3     2
 *   /                     \
 *  4                       4
 *
 * Notice:
 * - At Node 1: Left child 2 in Tree 1 matches Right child 2 in Tree 2.
 * - At Node 1: Right child 3 in Tree 1 matches Left child 3 in Tree 2.
 * Valid Isomorphism!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If both `null` $\rightarrow$ `true`; if one `null` $\rightarrow$ `false`; if `r1->data != r2->data` $\rightarrow$ `false`.
 * - `noSwap = isIso(l1, l2) && isIso(r1, r2)`.
 * - `swapMatch = isIso(l1, r2) && isIso(r1, l2)`.
 * - Return `noSwap || swapMatch`.
 * - Time: O(N), Space: O(H).
 */
