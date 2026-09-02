/*
    QUESTION    : Find all Duplicate Subtrees in a Binary Tree
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/duplicate-subtrees/1
    LeetCode    : https://leetcode.com/problems/find-duplicate-subtrees/
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Subtree serialization with hash map
// S.C : O(N) - Hash map storing subtree string representations
class Solution {
private:
    unordered_map<string, int> subtreeCount;
    vector<Node*> duplicateRoots;

    string serialize(Node* root) {
        if (root == nullptr) {
            return "#";
        }

        string leftStr = serialize(root->left);
        string rightStr = serialize(root->right);

        string serialized = to_string(root->data) + "," + leftStr + "," + rightStr;

        subtreeCount[serialized]++;

        // Only add root to result list the FIRST time its duplicate is encountered
        if (subtreeCount[serialized] == 2) {
            duplicateRoots.push_back(root);
        }

        return serialized;
    }

public:
    vector<Node*> printAllDups(Node* root) {
        subtreeCount.clear();
        duplicateRoots.clear();

        serialize(root);

        return duplicateRoots;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF SERIALIZED DUPLICATE SUBTREES
 * ============================================================================
 *
 *               1
 *             /   \
 *            2     3
 *          /     /   \
 *         4     2     4
 *              /
 *             4
 *
 * Duplicate Subtree 1: Node(4) -> "4,#,#"
 * Duplicate Subtree 2: Subtree at Node(2) -> "2,4,#,#,#"
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `serialize(root)`: `to_string(root->data) + "," + serialize(left) + "," + serialize(right)`.
 * - `subtreeCount[serialized]++`.
 * - If `subtreeCount[serialized] == 2`: `duplicateRoots.push_back(root)`.
 * - Time: O(N), Space: O(N).
 */
