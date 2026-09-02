/*
    QUESTION    : Find the median of BST in O(n) time and O(1) space (Morris Traversal)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/find-median-bst-time-o1-space/
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
// T.C : O(N) - Two passes of Morris Inorder Traversal
// S.C : O(1) - Constant auxiliary space (no recursion stack, uses threaded temporary pointers)
class Solution {
private:
    // Pass 1: Count total nodes in BST using Morris Traversal
    int countNodesMorris(Node* root) {
        int count = 0;
        Node* curr = root;

        while (curr != nullptr) {
            if (curr->left == nullptr) {
                count++;
                curr = curr->right;
            } else {
                Node* pre = curr->left;
                while (pre->right != nullptr && pre->right != curr) {
                    pre = pre->right;
                }

                if (pre->right == nullptr) {
                    pre->right = curr; // Make temporary thread
                    curr = curr->left;
                } else {
                    pre->right = nullptr; // Revert thread
                    count++;
                    curr = curr->right;
                }
            }
        }
        return count;
    }

public:
    float findMedian(struct Node *root) {
        if (root == nullptr) return 0;

        int totalNodes = countNodesMorris(root);

        // Target indices for median
        int target1 = (totalNodes + 1) / 2;
        int target2 = (totalNodes % 2 == 0) ? (totalNodes / 2 + 1) : target1;

        int count = 0;
        int val1 = 0, val2 = 0;
        Node* curr = root;

        // Pass 2: Locate values at target indices using Morris Traversal
        while (curr != nullptr) {
            if (curr->left == nullptr) {
                count++;
                if (count == target1) val1 = curr->data;
                if (count == target2) val2 = curr->data;
                curr = curr->right;
            } else {
                Node* pre = curr->left;
                while (pre->right != nullptr && pre->right != curr) {
                    pre = pre->right;
                }

                if (pre->right == nullptr) {
                    pre->right = curr;
                    curr = curr->left;
                } else {
                    pre->right = nullptr;
                    count++;
                    if (count == target1) val1 = curr->data;
                    if (count == target2) val2 = curr->data;
                    curr = curr->right;
                }
            }
        }

        return (val1 + val2) / 2.0f;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF MORRIS THREADED TRAVERSAL
 * ============================================================================
 *
 *               6
 *             /   \
 *            3     8
 *           / \   / \
 *          1   4 7   9
 *
 * 1. At Node 6: find predecessor (rightmost of left subtree) = 4.
 *    Create thread 4->right = 6. Move curr = 3.
 * 2. At Node 3: predecessor = 1.
 *    Create thread 1->right = 3. Move curr = 1.
 * 3. At Node 1: left is null -> Visit 1, follow thread to 3.
 * 4. At Node 3: thread exists -> Remove thread, Visit 3, move to 4.
 * 5. At Node 4: left is null -> Visit 4, follow thread to 6.
 * 6. At Node 6: thread exists -> Remove thread, Visit 6, move to 8...
 *
 * Traversal: 1 -> 3 -> 4 -> 6 -> 7 -> 8 -> 9 (Total = 7 nodes).
 * Median = Node at index (7+1)/2 = 4th node = 6.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Morris Inorder Traversal visits nodes in sorted order in $O(N)$ time and $O(1)$ space.
 * - Pass 1: Count total nodes $N$.
 * - Pass 2: Track current index. Capture values at index $(N+1)/2$ and $(N/2)+1$.
 * - Return `(val1 + val2) / 2.0`.
 * - Time: O(N), Space: O(1).
 */
