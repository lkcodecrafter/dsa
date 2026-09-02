/*
    QUESTION    : Merge two BST [ V.V.V IMP ]
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://www.geeksforgeeks.org/merge-two-balanced-binary-search-trees/
    LeetCode    : https://leetcode.com/problems/all-elements-in-two-binary-search-trees/
*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(M + N) - Inorder traversals + Two-pointer merge + Balanced BST construction
// S.C : O(M + N) - Storage for inorder arrays and merged array
class Solution {
private:
    void inorder(Node* root, vector<int> &arr) {
        if (root == nullptr) return;
        inorder(root->left, arr);
        arr.push_back(root->data);
        inorder(root->right, arr);
    }

    // Merges two sorted vectors into a single sorted vector in O(M + N)
    vector<int> mergeSortedArrays(const vector<int> &a, const vector<int> &b) {
        vector<int> merged;
        merged.reserve(a.size() + b.size());

        int i = 0, j = 0;
        while (i < a.size() && j < b.size()) {
            if (a[i] <= b[j]) {
                merged.push_back(a[i++]);
            } else {
                merged.push_back(b[j++]);
            }
        }

        while (i < a.size()) merged.push_back(a[i++]);
        while (j < b.size()) merged.push_back(b[j++]);

        return merged;
    }

public:
    // Returns merged sorted elements of two BSTs
    vector<int> merge(Node *root1, Node *root2) {
        vector<int> arr1, arr2;

        // Step 1: Inorder of both BSTs
        inorder(root1, arr1);
        inorder(root2, arr2);

        // Step 2: Merge two sorted arrays
        return mergeSortedArrays(arr1, arr2);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TWO BST MERGING
 * ============================================================================
 *
 * BST 1:                BST 2:
 *       100                    80
 *      /   \                  /  \
 *     50   300               40  120
 *
 * Inorder 1: [ 50, 100, 300 ]
 * Inorder 2: [ 40, 80, 120 ]
 *
 * Two-Pointer Merged: [ 40, 50, 80, 100, 120, 300 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Extract Inorder of BST1 (`arr1`) and BST2 (`arr2`) in $O(M + N)$.
 * - Merge the two sorted arrays using two pointers in $O(M + N)$.
 * - (Optional if new tree needed: build balanced BST from merged array).
 * - Time: O(M + N), Space: O(M + N).
 */
