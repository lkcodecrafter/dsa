/*
    QUESTION    : Check if given array represents valid preorder traversal of a BST
    Company Tags: Amazon, Microsoft, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/preorder-to-postorder/0
    LeetCode    : https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/
*/

#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Monotonic stack processes each element at most twice (one push, one pop)
// S.C : O(N) - Monotonic stack
class Solution {
public:
    int canRepresentBST(int arr[], int N) {
        stack<int> st; // Monotonic Decreasing Stack
        int root = INT_MIN;

        for (int i = 0; i < N; i++) {
            // If we find a number smaller than the recently popped root, it violates BST property
            if (arr[i] < root) {
                return 0; // Invalid BST preorder
            }

            // If current element is greater than stack top, it belongs to the right subtree of some ancestor
            while (!st.empty() && st.top() < arr[i]) {
                root = st.top(); // Update the lower bound (root)
                st.pop();
            }

            st.push(arr[i]);
        }

        return 1; // Valid BST preorder
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF MONOTONIC STACK LOWER-BOUND TRACKING
 * ============================================================================
 *
 * Preorder: [ 40, 30, 35, 80, 100 ]
 *
 * 1. Read 40: push 40. Stack: [40], root = -inf
 * 2. Read 30: 30 < 40 -> push 30. Stack: [40, 30], root = -inf
 * 3. Read 35: 35 > 30 -> pop 30, root = 30. Push 35. Stack: [40, 35], root = 30
 * 4. Read 80: 80 > 35, 40 -> pop 35, 40, root = 40. Push 80. Stack: [80], root = 40
 * 5. Read 100: 100 > 80 -> pop 80, root = 80. Push 100. Stack: [100], root = 80
 *
 * Every element remained > root -> Valid BST!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `root = INT_MIN`. Maintain monotonic decreasing stack `st`.
 * - For each `x` in `arr`:
 *     - If `x < root`: return `0` (Violation!).
 *     - While `!st.empty() && st.top() < x`: `root = st.top(); st.pop();`.
 *     - `st.push(x)`.
 * - Return `1`.
 * - Time: O(N), Space: O(N).
 */
