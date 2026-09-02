/*
    QUESTION    : Replace every element with the least greater element on its right
    Company Tags: Amazon, Directi
    GfG Link    : https://www.geeksforgeeks.org/replace-every-element-with-the-least-greater-element-on-its-right/
*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for BST Node
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) average (O(N^2) worst case if BST is skewed)
// S.C : O(N)       - Auxiliary space for BST nodes
class Solution {
private:
    // Inserts `val` into BST and updates `successor` with the least greater element seen so far
    BSTNode* insert(BSTNode* root, int val, BSTNode*& successor) {
        if (root == nullptr) {
            return new BSTNode(val);
        }

        // If val is smaller, current root is a potential least greater element (successor)
        if (val < root->data) {
            successor = root;
            root->left = insert(root->left, val, successor);
        } else if (val >= root->data) {
            // If val is greater or equal, go right without updating successor
            root->right = insert(root->right, val, successor);
        }

        return root;
    }

public:
    vector<int> findLeastGreater(vector<int>& arr, int n) {
        vector<int> result(n, -1);
        BSTNode* root = nullptr;

        // Traverse array from right to left
        for (int i = n - 1; i >= 0; i--) {
            BSTNode* successor = nullptr;
            root = insert(root, arr[i], successor);

            if (successor != nullptr) {
                result[i] = successor->data;
            } else {
                result[i] = -1;
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF RIGHT-TO-LEFT INSERTION IN BST
 * ============================================================================
 *
 * Array: [ 8, 58, 71, 18, 31, 32, 63, 92, 43, 3, 91, 93, 25, 80, 28 ], n = 15
 *
 * Traverse Right-to-Left:
 * - Insert 28: BST empty -> succ = -1
 * - Insert 80: 80 > 28 -> succ = -1
 * - Insert 25: 25 < 28 (succ = 28)
 * - Insert 93: 93 > all -> succ = -1
 * - Insert 91: 91 < 93 (succ = 93)
 * ...
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Traverse `arr` from right to left (`i = n - 1` down to `0`).
 * - Insert `arr[i]` into a BST:
 *     - Whenever you branch LEFT (`val < root->data`), `successor = root`.
 *     - Whenever you branch RIGHT, do not change `successor`.
 * - Record `result[i] = successor ? successor->data : -1`.
 * - Time: O(N log N) avg, Space: O(N).
 */
