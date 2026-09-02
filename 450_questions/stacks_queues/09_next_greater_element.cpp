/*
    QUESTION    : Next Greater Element (Next Larger Element)
    Company Tags: Amazon, Microsoft, Flipkart, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/next-larger-element-1587115620/1
    LeetCode    : https://leetcode.com/problems/next-greater-element-i/
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Monotonic stack processes each element at most twice (one push, one pop)
// S.C : O(N) - Stack storing elements
class Solution {
public:
    vector<long long> nextLargerElement(vector<long long> arr, int n) {
        vector<long long> result(n);
        stack<long long> st; // Monotonic Decreasing Stack

        // Traverse array from right to left
        for (int i = n - 1; i >= 0; i--) {
            // Pop smaller or equal elements from stack top (cannot be next greater)
            while (!st.empty() && st.top() <= arr[i]) {
                st.pop();
            }

            // Top of stack is the next greater element
            result[i] = st.empty() ? -1 : st.top();

            // Push current element to stack
            st.push(arr[i]);
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF MONOTONIC STACK (RIGHT-TO-LEFT)
 * ============================================================================
 *
 * Array: [ 1, 3, 2, 4 ]
 *
 * i = 3 (4): Stack empty -> NGE = -1. Push 4. Stack: [4]
 * i = 2 (2): Top = 4 > 2 -> NGE = 4. Push 2. Stack: [4, 2]
 * i = 1 (3): Top = 2 <= 3 -> Pop 2. Top = 4 > 3 -> NGE = 4. Push 3. Stack: [4, 3]
 * i = 0 (1): Top = 3 > 1 -> NGE = 3. Push 1. Stack: [4, 3, 1]
 *
 * Result: [ 3, 4, 4, -1 ]
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Traverse from `n - 1` down to `0`.
 * - `while (!st.empty() && st.top() <= arr[i]) st.pop();`
 * - `result[i] = st.empty() ? -1 : st.top();`
 * - `st.push(arr[i]);`
 * - Time: O(N), Space: O(N).
 */
