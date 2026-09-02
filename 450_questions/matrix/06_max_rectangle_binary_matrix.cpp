/*
    QUESTION    : Maximum size rectangle binary sub-matrix with all 1s
    Company Tags: Amazon, Microsoft, Google, MakeMyTrip
    GfG Link    : https://practice.geeksforgeeks.org/problems/max-rectangle/1
    LeetCode    : https://leetcode.com/problems/maximal-rectangle/
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(R * C) - Each row computes Largest Rectangle in Histogram using a monotonic stack in O(C)
// S.C : O(C)     - Height array and stack of size equal to number of columns
class Solution {
private:
    // Helper function: Largest Rectangle in Histogram using Monotonic Increasing Stack
    int maxHistogramArea(const vector<int> &heights) {
        int n = heights.size();
        stack<int> st; // Stores indices of bar heights
        int maxArea = 0;

        for (int i = 0; i <= n; i++) {
            int currentHeight = (i == n) ? 0 : heights[i];

            while (!st.empty() && currentHeight < heights[st.top()]) {
                int height = heights[st.top()];
                st.pop();

                // Width is between current index `i` and previous smaller index `st.top()`
                int width = st.empty() ? i : (i - st.top() - 1);
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }

        return maxArea;
    }

public:
    int maxArea(vector<vector<int>> &M, int n, int m) {
        if (n == 0 || m == 0) return 0;

        vector<int> heights(m, 0);
        int maxRectangle = 0;

        // Process row by row as histograms
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                // If cell is 1, increment height; if 0, reset height to 0
                if (M[r][c] == 1) {
                    heights[c] += 1;
                } else {
                    heights[c] = 0;
                }
            }
            // Find max area histogram for current accumulated row
            maxRectangle = max(maxRectangle, maxHistogramArea(heights));
        }

        return maxRectangle;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF HISTOGRAM TRANSFORMATION
 * ============================================================================
 *
 * Binary Matrix (4x4):
 * Row 0: [ 0, 1, 1, 0 ] -> Heights: [0, 1, 1, 0] -> Max Area = 2 (1x2)
 * Row 1: [ 1, 1, 1, 1 ] -> Heights: [1, 2, 2, 1] -> Max Area = 4 (2x2 or 1x4)
 * Row 2: [ 1, 1, 1, 1 ] -> Heights: [2, 3, 3, 2] -> Max Area = 8 (2x4)
 * Row 3: [ 1, 1, 0, 0 ] -> Heights: [3, 4, 0, 0] -> Max Area = 6 (3x2)
 *
 * Overall Max Rectangle Area = 8!
 *
 * ============================================================================
 * DRY RUN (maxHistogramArea with heights = [2, 3, 3, 2])
 * ============================================================================
 * | i | heights[i] | Stack (Indices) | Action / Popped Index | Computed Height x Width = Area | maxArea |
 * | :- | :--------- | :-------------- | :-------------------- | :----------------------------- | :------ |
 * | 0 | 2          | {0}             | Push 0                | -                              | 0       |
 * | 1 | 3          | {0, 1}          | Push 1                | -                              | 0       |
 * | 2 | 3          | {0, 1, 2}       | Push 2                | -                              | 0       |
 * | 3 | 2          | Pop 2, Pop 1    | Pop 2: h=3, w=2-0-1=1 | 3 x 1 = 3                      | 3       |
 * |   |            |                 | Pop 1: h=3, w=3-0-1=2 | 3 x 2 = 6                      | 6       |
 * |   |            | {0, 3}          | Push 3                | -                              | 6       |
 * | 4 | 0 (Dummy)  | Pop 3, Pop 0    | Pop 3: h=2, w=4-0-1=3 | 2 x 3 = 6                      | 6       |
 * |   |            |                 | Pop 0: h=2, w=4       | 2 x 4 = 8                      | 8       |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Rising Skyline"
 * As you scan down each floor of a skyscraper blueprint, you accumulate column
 * pillars (`heights[c] += 1`). If a floor has a hole (`0`), the pillar collapses (`heights[c] = 0`).
 * At each floor, compute the largest billboard you can fit on the accumulated skyline.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Maintain a 1D `heights` array of size $C$, initialized to $0$.
 * - For each row $r$:
 *     - If `M[r][c] == 1`: `heights[c]++`.
 *     - Else: `heights[c] = 0`.
 *     - Compute Largest Rectangle in Histogram for `heights` using a monotonic stack in $O(C)$.
 * - Time Complexity: O(R * C), Space Complexity: O(C).
 */
