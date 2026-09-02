/*
    QUESTION    : Convert BST to Min Heap (such that left and right subtrees satisfy min-heap and all left < right)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/convert-bst-min-heap/
*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for Binary Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Inorder traversal O(N) + Preorder fill O(N)
// S.C : O(N) - Vector to store inorder traversal of BST
class Solution {
private:
    // Step 1: Inorder traversal of BST gives strictly sorted array
    void inorderTraversal(Node* root, vector<int> &inorder) {
        if (root == nullptr) return;
        inorderTraversal(root->left, inorder);
        inorder.push_back(root->data);
        inorderTraversal(root->right, inorder);
    }

    // Step 2: Fill nodes in PREORDER using sorted inorder values (root, left, right)
    // Preorder filling ensures parent < left < right (Min-Heap property)
    void preorderFill(Node* root, const vector<int> &inorder, int &index) {
        if (root == nullptr) return;

        // Assign smallest available sorted value to current parent root
        root->data = inorder[index++];

        preorderFill(root->left, inorder, index);
        preorderFill(root->right, inorder, index);
    }

public:
    void convertToMinHeap(Node* root) {
        vector<int> inorder;

        // 1. Extract elements in sorted order from BST
        inorderTraversal(root, inorder);

        // 2. Overwrite tree nodes in preorder traversal
        int index = 0;
        preorderFill(root, inorder, index);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BST TO MIN-HEAP CONVERSION
 * ============================================================================
 *
 * Given BST:
 *             4
 *           /   \
 *          2     6
 *        /  \   /  \
 *       1    3 5    7
 *
 * 1. Inorder Traversal (Sorted): [ 1, 2, 3, 4, 5, 6, 7 ]
 *
 * 2. Preorder Fill (Root -> Left -> Right):
 *             1
 *           /   \
 *          2     5
 *        /  \   /  \
 *       3    4 6    7
 *
 * Notice:
 * Every parent is strictly smaller than both children (`1 < 2, 5`),
 * and left subtree values are smaller than right subtree (`2 < 5`).
 *
 * ============================================================================
 * DRY RUN (inorder = [1, 2, 3, 4, 5, 6, 7])
 * ============================================================================
 * | Preorder Step | Node Visited | Assigned Value (inorder[index]) | Next Index |
 * | :------------ | :----------- | :------------------------------ | :--------- |
 * | 1             | Root (4)     | 1                               | index = 1  |
 * | 2             | Left (2)     | 2                               | index = 2  |
 * | 3             | Left-Left(1) | 3                               | index = 3  |
 * | 4             | Left-Right(3)| 4                               | index = 4  |
 * | 5             | Right (6)    | 5                               | index = 5  |
 * | 6             | Right-Left(5)| 6                               | index = 6  |
 * | 7             | Right-Right7 | 7                               | index = 7  |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "Inorder-Extract, Preorder-Inject"
 * BST naturally gives sorted numbers when read in `Inorder`.
 * Min-Heap requires parents to be filled with the smallest numbers first (`Preorder`).
 * Read Inorder -> Write Preorder!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Store Inorder traversal of BST into array `inorder` (sorted order).
 * - Traverse BST in Preorder: assign `root->data = inorder[index++]`.
 * - Preorder traversal ensures root gets smaller value than left and right subtrees.
 * - Time: O(N), Space: O(N).
 */
