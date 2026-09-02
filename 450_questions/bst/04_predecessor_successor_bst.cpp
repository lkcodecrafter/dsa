/*
    QUESTION    : Find Inorder Predecessor and Inorder Successor in a BST
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/predecessor-and-successor/1
*/

#include <iostream>

using namespace std;

// Definition for a binary tree node
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(H) where H is height of BST (O(log N) for balanced BST)
// S.C : O(1) - Iterative search without recursion stack
class Solution {
public:
    void findPreSuc(Node* root, Node*& pre, Node*& suc, int key) {
        pre = nullptr;
        suc = nullptr;

        Node* curr = root;

        // Step 1: Search for the node while tracking potential predecessors and successors
        while (curr != nullptr) {
            if (curr->key == key) {
                // If left subtree exists, predecessor is the maximum in left subtree
                if (curr->left != nullptr) {
                    Node* temp = curr->left;
                    while (temp->right != nullptr) {
                        temp = temp->right;
                    }
                    pre = temp;
                }

                // If right subtree exists, successor is the minimum in right subtree
                if (curr->right != nullptr) {
                    Node* temp = curr->right;
                    while (temp->left != nullptr) {
                        temp = temp->left;
                    }
                    suc = temp;
                }
                return;
            } else if (key < curr->key) {
                // Current node is a potential successor (larger than key)
                suc = curr;
                curr = curr->left;
            } else {
                // Current node is a potential predecessor (smaller than key)
                pre = curr;
                curr = curr->right;
            }
        }
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF PREDECESSOR AND SUCCESSOR
 * ============================================================================
 *
 *               50
 *             /    \
 *           30      70
 *          /  \    /  \
 *        20   40  60   80
 *
 * Key = 50:
 * - Predecessor: Max in left subtree -> 40
 * - Successor  : Min in right subtree -> 60
 *
 * Key = 65 (Not present in tree):
 * - Traversal: 50 (pre=50, go right) -> 70 (suc=70, go left) -> 60 (pre=60, go right) -> null
 * - Predecessor = 60, Successor = 70!
 *
 * ============================================================================
 * DRY RUN (Key = 30)
 * ============================================================================
 * | Step | curr Node | Key vs curr->key | Action / Subtree Check | pre | suc |
 * | :--- | :-------- | :--------------- | :--------------------- | :-- | :-- |
 * | 1    | Node(50)  | 30 < 50          | suc = Node(50), go left| -   | 50  |
 * | 2    | Node(30)  | 30 == 30 (Found) | Pre = max(left)=20     | 20  | 50  |
 * |      |           |                  | Suc = min(right)=40    | 20  | 40  |
 *
 * Output: Predecessor = 20, Successor = 40.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `key < curr->key`: `suc = curr; curr = curr->left;`
 * - If `key > curr->key`: `pre = curr; curr = curr->right;`
 * - If `key == curr->key`:
 *     - `pre` = rightmost node in `curr->left`.
 *     - `suc` = leftmost node in `curr->right`.
 * - Time: O(H), Space: O(1).
 */
