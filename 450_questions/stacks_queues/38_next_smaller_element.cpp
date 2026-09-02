/*
    QUESTION    : Next Smaller Element (Immediate Smaller Element / Next Smaller to Right)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/next-smaller-element/
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Monotonic Increasing Stack processes each element at most twice
// S.C : O(N) - Stack storing elements
class Solution {
public:
    vector<int> nextSmallerElement(vector<int> &arr, int n) {
        vector<int> result(n);
        stack<int> st;

        // Traverse from right to left
        for (int i = n - 1; i >= 0; i--) {
            // Pop elements greater than or equal to current element
            while (!st.empty() && st.top() >= arr[i]) {
                st.pop();
            }

            // Top of stack is next smaller element
            result[i] = st.empty() ? -1 : st.top();

            st.push(arr[i]);
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Traverse right-to-left (`i = n - 1` down to `0`).
 * - While `!st.empty() && st.top() >= arr[i]`: `st.pop();`.
 * - `result[i] = st.empty() ? -1 : st.top(); st.push(arr[i]);`
 * - Time: O(N), Space: O(N).
 */
