/*
    QUESTION    : Largest Rectangular Area in Histogram
    Company Tags: Amazon, Microsoft, Google, Adobe, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximum-rectangular-area-in-a-histogram-1587115620/1
    LeetCode    : https://leetcode.com/problems/largest-rectangle-in-histogram/
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Single pass monotonic stack calculates width for every popped bar
// S.C : O(N) - Stack storing indices
class Solution {
public:
    long long getMaxArea(long long arr[], int n) {
        stack<int> st; // Monotonic Increasing Stack of indices
        long long maxArea = 0;

        for (int i = 0; i <= n; i++) {
            // Virtual 0-height bar at index n forces stack clearance
            long long currentHeight = (i == n) ? 0 : arr[i];

            while (!st.empty() && currentHeight < arr[st.top()]) {
                long long height = arr[st.top()];
                st.pop();

                // Width is between current index i (right boundary) and new st.top() (left boundary)
                long long width = st.empty() ? i : (i - st.top() - 1);
                maxArea = max(maxArea, height * width);
            }

            st.push(i);
        }

        return maxArea;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Monotonic stack of bar indices.
 * - Loop up to `i <= n` (virtual bar `height = 0` at `i == n`).
 * - While `currentHeight < arr[st.top()]`:
 *     - `h = arr[st.top()]; st.pop();`
 *     - `w = st.empty() ? i : (i - st.top() - 1);`
 *     - `maxArea = max(maxArea, h * w);`
 * - Time: O(N), Space: O(N).
 */
