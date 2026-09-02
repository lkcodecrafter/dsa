/*
    QUESTION    : Deletion of a node in a BST
    Company Tags: Amazon, Microsoft, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/delete-a-node-from-bst/1
    LeetCode    : https://leetcode.com/problems/delete-node-in-a-bst/
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(H) where H is height of the BST (O(log N) for balanced, O(N) worst case)
// S.C : O(H) - Recursion stack depth
class Solution {
private:
    // Helper to find the inorder successor (minimum value in right subtree)
    TreeNode* findMin(TreeNode* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return nullptr;

        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } else {
            // Node with target key found! Handle 3 deletion cases:

            // Case 1: Node has NO left child (or is a leaf)
            if (root->left == nullptr) {
                TreeNode* rightChild = root->right;
                delete root;
                return rightChild;
            }
            // Case 2: Node has NO right child
            else if (root->right == nullptr) {
                TreeNode* leftChild = root->left;
                delete root;
                return leftChild;
            }
            // Case 3: Node has TWO children
            else {
                // Find inorder successor (smallest value in right subtree)
                TreeNode* successor = findMin(root->right);
                // Copy successor value to current node
                root->val = successor->val;
                // Delete the successor node from the right subtree
                root->right = deleteNode(root->right, successor->val);
            }
        }

        return root;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 3 DELETION CASES
 * ============================================================================
 *
 * Case 1 & 2: 0 or 1 Child:
 *       5                       5
 *      / \     delete(3)       / \
 *     3   6   --------->      2   6
 *    /
 *   2
 *
 * Case 3: 2 Children:
 *       5                       6  (Successor copied)
 *      / \     delete(5)       / \
 *     3   6   --------->      3   7
 *        / \                       (Old 6 deleted)
 *       6   7
 *
 * ============================================================================
 * DRY RUN (Delete 3 from BST [5, 3, 6, 2, 4])
 * ============================================================================
 * | Call | Current Node | Key vs Node->val | Case Evaluated | Returned Subtree |
 * | :--- | :----------- | :--------------- | :------------- | :--------------- |
 * | 1    | Node(5)      | 3 < 5 (Go Left)  | -              | root->left updated |
 * | 2    | Node(3)      | 3 == 3 (Found)   | 2 Children     | Successor = 4    |
 * | 3    | Node(4)      | 4 == 4 (Found)   | Leaf Node      | Returns nullptr  |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Line of Succession"
 * If the King (a node with 2 heirs) steps down, the smallest person in the right kingdom
 * (`inorder successor`) takes the throne. Then remove the successor's old empty cabin.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - 0 children: delete node, return `nullptr`.
 * - 1 child: delete node, return non-null child.
 * - 2 children:
 *     1. Find `successor = findMin(root->right)`.
 *     2. `root->val = successor->val`.
 *     3. `root->right = deleteNode(root->right, successor->val)`.
 * - Time: O(H), Space: O(H).
 */
