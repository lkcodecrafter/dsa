/*
    QUESTION    : Print / Count all K Sum paths in a Binary Tree (Path Sum III)
    Company Tags: Amazon, Microsoft, Directi
    GfG Link    : https://www.geeksforgeeks.org/print-k-sum-paths-binary-tree/
    LeetCode    : https://leetcode.com/problems/path-sum-iii/
*/

#include <iostream>
#include <vector>
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
// T.C : O(N) - Prefix sum hash map tracking along root-to-leaf paths
// S.C : O(H) - Prefix sum hash map and recursion stack
class Solution {
private:
    int totalPaths = 0;
    unordered_map<long long, int> prefixSumMap;

    void dfs(Node* root, long long currentSum, int k) {
        if (root == nullptr) return;

        currentSum += root->data;

        // Check if there is a prefix sum such that currentSum - prefixSum = k
        if (prefixSumMap.find(currentSum - k) != prefixSumMap.end()) {
            totalPaths += prefixSumMap[currentSum - k];
        }

        // Add current prefix sum to map
        prefixSumMap[currentSum]++;

        dfs(root->left, currentSum, k);
        dfs(root->right, currentSum, k);

        // Backtrack: Remove current prefix sum before returning to parent
        prefixSumMap[currentSum]--;
    }

public:
    int sumK(Node *root, int k) {
        totalPaths = 0;
        prefixSumMap.clear();

        // Base case: prefix sum of 0 has frequency 1
        prefixSumMap[0] = 1;

        dfs(root, 0, k);

        return totalPaths;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF PREFIX SUM PATH TRACKING
 * ============================================================================
 *
 *               1
 *             /   \
 *            3    -1
 *          /  \   /  \
 *         2    1 4    5
 *             /   \    \
 *            1     2    6
 *
 * Target K = 5:
 * Path 1: 3 -> 2 (Sum = 5)
 * Path 2: 3 -> 1 -> 1 (Sum = 5)
 * Path 3: 1 -> 4 (Sum = 5)
 * Path 4: 5 (Sum = 5)
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `prefixSumMap[0] = 1`.
 * - In DFS: `currentSum += root->data; totalPaths += prefixSumMap[currentSum - k];`.
 * - `prefixSumMap[currentSum]++`.
 * - DFS left & right.
 * - Backtrack: `prefixSumMap[currentSum]--`.
 * - Time: O(N), Space: O(H).
 */
