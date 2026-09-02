/*
    QUESTION    : Minimum swaps required to convert a Binary Tree into BST
    Company Tags: Amazon, Directi
    GfG Link    : https://www.geeksforgeeks.org/minimum-swap-required-convert-binary-tree-binary-search-tree/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Inorder traversal O(N) + Array cycle detection O(N log N)
// S.C : O(N)       - Vector to store inorder and visited array for permutation cycles
class Solution {
private:
    // Helper function to extract inorder traversal of complete binary tree stored as array
    void inorder(const vector<int> &tree, int idx, int n, vector<int> &in) {
        if (idx >= n) return;
        inorder(tree, 2 * idx + 1, n, in); // Left child
        in.push_back(tree[idx]);           // Root
        inorder(tree, 2 * idx + 2, n, in); // Right child
    }

    // Computes minimum swaps to sort an array using graph cycle detection
    int minSwapsToSort(vector<int> &arr) {
        int n = arr.size();
        vector<pair<int, int>> pos(n);

        for (int i = 0; i < n; i++) {
            pos[i] = {arr[i], i};
        }

        sort(pos.begin(), pos.end());

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || pos[i].second == i) {
                continue;
            }

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = pos[j].second;
                cycleSize++;
            }

            if (cycleSize > 1) {
                swaps += (cycleSize - 1);
            }
        }

        return swaps;
    }

public:
    int minSwaps(vector<int>& tree, int n) {
        vector<int> in;
        inorder(tree, 0, n, in);
        return minSwapsToSort(in);
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF PERMUTATION CYCLES
 * ============================================================================
 *
 * Tree Inorder: [ 5, 6, 7, 8 ]
 * Sorted Inorder: [ 5, 6, 7, 8 ] -> 0 swaps needed!
 *
 * If Inorder = [ 8, 5, 6, 7 ]:
 * - Cycle: (8 -> 7 -> 6 -> 5 -> 8), length = 4 -> Swaps = 4 - 1 = 3!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Convert Tree to `inorder` array.
 * - Min swaps to make tree a BST is identical to min swaps to sort its `inorder` array!
 * - Find permutation cycles on `{inorder[i], original_index}`: `swaps += (cycleSize - 1)`.
 * - Time: O(N log N), Space: O(N).
 */
