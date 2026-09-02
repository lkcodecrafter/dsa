/*
    QUESTION    : Largest Independent Set Problem (Tree LISS)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/largest-independent-set-problem/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Tree Node
struct Node {
    int data;
    Node *left, *right;
    int liss; // Memoization field
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Post-order Tree DP returning {included_size, excluded_size}
// S.C : O(H) - Tree recursion call stack
class Solution {
private:
    // Returns pair: {max LIS including root, max LIS excluding root}
    pair<int, int> solve(Node* root) {
        if (!root) return {0, 0};

        auto left = solve(root->left);
        auto right = solve(root->right);

        // If root is included, its direct children cannot be included
        int includeRoot = 1 + left.second + right.second;

        // If root is excluded, children may or may not be included
        int excludeRoot = max(left.first, left.second) + max(right.first, right.second);

        return {includeRoot, excludeRoot};
    }

public:
    int LISS(Node *root) {
        auto res = solve(root);
        return max(res.first, res.second);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `includeRoot = 1 + left.exclude + right.exclude`.
 * - `excludeRoot = max(left) + max(right)`.
 * - Time: O(N), Space: O(H).
 */
