/*
    QUESTION    : Check if a Binary Tree is Heap
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/is-binary-tree-heap/1
*/

#include <iostream>

using namespace std;

// Definition for Binary Tree Node
struct Node {
    int data;
    Node *left;
    Node *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Visits each node of the tree to count nodes and check completeness & heap property
// S.C : O(H) - Recursion stack space (H = height of tree <= log N for complete binary tree)
class Solution {
private:
    // Helper function to count total nodes in binary tree
    int countNodes(Node* root) {
        if (root == nullptr) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }

    // Condition 1: Check if the binary tree is a Complete Binary Tree (CBT)
    bool isComplete(Node* root, int index, int totalNodes) {
        if (root == nullptr) return true;

        // If index assigned to current node >= totalNodes, it is not complete
        if (index >= totalNodes) return false;

        return isComplete(root->left, 2 * index + 1, totalNodes) &&
               isComplete(root->right, 2 * index + 2, totalNodes);
    }

    // Condition 2: Check if every parent satisfies Max-Heap property: root->data >= children
    bool isHeapProperty(Node* root) {
        // Leaf node satisfies heap property
        if (root->left == nullptr && root->right == nullptr) {
            return true;
        }

        // Only left child exists (right is null)
        if (root->right == nullptr) {
            return (root->data >= root->left->data) && isHeapProperty(root->left);
        }

        // Both children exist
        return (root->data >= root->left->data) &&
               (root->data >= root->right->data) &&
               isHeapProperty(root->left) &&
               isHeapProperty(root->right);
    }

public:
    bool isHeap(struct Node* tree) {
        if (tree == nullptr) return true;

        int totalNodes = countNodes(tree);

        // A binary tree is a Max-Heap if it is COMPLETE and satisfies MAX-HEAP PROPERTY
        return isComplete(tree, 0, totalNodes) && isHeapProperty(tree);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF HEAP VALIDATION
 * ============================================================================
 *
 * Valid Max-Heap (CBT + Heap Property):
 *             10
 *           /    \
 *          9      8
 *        /  \
 *       7    6
 *
 * Total Nodes = 5.
 * Indices: 10(0), 9(1), 8(2), 7(3), 6(4). All indices < 5 -> Complete!
 * All parents >= children -> Valid Heap!
 *
 * Invalid Tree (Missing left child at node 9):
 *             10
 *           /    \
 *          9      8
 *           \
 *            7
 * Index for 7 = 2*1 + 2 = 4 (Total Nodes = 4) -> 4 >= 4 -> NOT COMPLETE!
 *
 * ============================================================================
 * DRY RUN
 * ============================================================================
 * | Node | Index | totalNodes | Index < totalNodes? | Data >= Children? | Status |
 * | :--- | :---- | :--------- | :------------------ | :---------------- | :----- |
 * | 10   | 0     | 5          | 0 < 5 (Yes)         | 10 >= 9 & 8 (Yes) | Valid  |
 * | 9    | 1     | 5          | 1 < 5 (Yes)         | 9 >= 7 & 6 (Yes)  | Valid  |
 * | 8    | 2     | 5          | 2 < 5 (Yes)         | Leaf Node (Yes)   | Valid  |
 * | 7    | 3     | 5          | 3 < 5 (Yes)         | Leaf Node (Yes)   | Valid  |
 * | 6    | 4     | 5          | 4 < 5 (Yes)         | Leaf Node (Yes)   | Valid  |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Strict Two-Test Exam"
 * To qualify as a Binary Heap:
 * 1. Physical Architecture Test: Must be a Complete Binary Tree (no gaps in indexing `idx < N`).
 * 2. Hierarchy Merit Test: Every parent must be greater than or equal to both children.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Count total nodes $N$.
 * - Test 1 (`isComplete`): Check that standard 0-indexed formula `2*i+1` and `2*i+2` never exceeds $N-1$.
 * - Test 2 (`isHeapProperty`): Check `root->data >= left->data && root->data >= right->data`.
 * - Return `isComplete && isHeapProperty`.
 * - Time: O(N), Space: O(H).
 */
