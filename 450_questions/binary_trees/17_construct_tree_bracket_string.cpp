/*
    QUESTION    : Construct Binary Tree from String with Bracket Representation
    Company Tags: Amazon, Facebook
    GfG Link    : https://www.geeksforgeeks.org/construct-binary-tree-string-bracket-representation/
    LeetCode    : https://leetcode.com/problems/construct-string-from-binary-tree/
*/

#include <iostream>
#include <string>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Parses each character of the bracket string once
// S.C : O(H) - Recursion stack space
class Solution {
public:
    Node* treeFromString(const string &s, int &idx) {
        if (idx >= s.length()) return nullptr;

        // 1. Parse node value (handles negative numbers too)
        int sign = 1;
        if (s[idx] == '-') {
            sign = -1;
            idx++;
        }

        int val = 0;
        while (idx < s.length() && isdigit(s[idx])) {
            val = val * 10 + (s[idx] - '0');
            idx++;
        }
        val *= sign;

        Node* root = new Node(val);

        // 2. Check for left subtree opening '('
        if (idx < s.length() && s[idx] == '(') {
            idx++; // consume '('
            root->left = treeFromString(s, idx);
            idx++; // consume ')'
        }

        // 3. Check for right subtree opening '('
        if (idx < s.length() && s[idx] == '(') {
            idx++; // consume '('
            root->right = treeFromString(s, idx);
            idx++; // consume ')'
        }

        return root;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF BRACKET PARSING
 * ============================================================================
 *
 * String: "4(2(3)(1))(6(5))"
 *
 *              4
 *            /   \
 *           2     6
 *         /   \  /
 *        3     1 5
 *
 * - First '(' after root 4 parses left subtree "2(3)(1)"
 * - Next '(' after left completes parses right subtree "6(5)"
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Parse number $\rightarrow$ create `root = new Node(val)`.
 * - If `s[idx] == '('`: `idx++; root->left = treeFromString(s, idx); idx++;` (skip `)`).
 * - If `s[idx] == '('`: `idx++; root->right = treeFromString(s, idx); idx++;` (skip `)`).
 * - Time: O(N), Space: O(H).
 */
