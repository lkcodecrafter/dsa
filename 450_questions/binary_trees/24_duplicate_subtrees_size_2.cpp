/*
    QUESTION    : Check if a Binary Tree contains duplicate subtrees of size 2 or more
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/duplicate-subtree-in-binary-tree/1
*/

#include <iostream>
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
// T.C : O(N) - Subtree serialization with hash map frequency tracking
// S.C : O(N) - Hash map storing serialized string signatures
class Solution {
private:
    unordered_map<string, int> subtreeFreq;
    bool hasDuplicate = false;

    // Serializes subtree into a unique string signature
    string serialize(Node* root) {
        if (root == nullptr) {
            return "#";
        }

        string leftStr = serialize(root->left);
        string rightStr = serialize(root->right);

        string serializedSubtree = to_string(root->data) + "," + leftStr + "," + rightStr;

        // Only consider subtrees of size 2 or more (leaf node serialization is "val,#,#")
        if (root->left != nullptr || root->right != nullptr) {
            subtreeFreq[serializedSubtree]++;
            if (subtreeFreq[serializedSubtree] == 2) {
                hasDuplicate = true;
            }
        }

        return serializedSubtree;
    }

public:
    int dupSub(Node *root) {
        subtreeFreq.clear();
        hasDuplicate = false;
        serialize(root);
        return hasDuplicate ? 1 : 0;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF SUBTREE SERIALIZATION
 * ============================================================================
 *
 *              1
 *            /   \
 *           2     2
 *         /  \   /  \
 *        4    5 4    5
 *
 * Subtree 1 at Left 2:  "2,4,#,#,5,#,#"
 * Subtree 2 at Right 2: "2,4,#,#,5,#,#"
 *
 * Frequency of "2,4,#,#,5,#,#" reaches 2 -> Duplicate Subtree Detected!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Serialize each subtree: `to_string(root->data) + "," + serialize(left) + "," + serialize(right)`.
 * - If non-leaf (`left != null || right != null`): `freq[serialized]++`.
 * - If any frequency reaches 2, return `1`.
 * - Time: O(N), Space: O(N).
 */
