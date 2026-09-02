/*
    QUESTION    : Kth smallest element in a row-column sorted matrix
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/kth-element-in-matrix/1
    LeetCode    : https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * log(Max - Min)) - Binary search on the answer value range [matrix[0][0], matrix[n-1][n-1]]
// S.C : O(1)                  - Constant auxiliary space
class Solution {
private:
    // Counts elements in matrix <= mid in O(N) using staircase walk from bottom-left
    int countLessOrEqual(const vector<vector<int>> &matrix, int mid, int n) {
        int count = 0;
        int row = n - 1;
        int col = 0;

        while (row >= 0 && col < n) {
            if (matrix[row][col] <= mid) {
                count += (row + 1); // All elements above in this column are also <= mid
                col++;              // Move to next column
            } else {
                row--;              // Value too big, move up
            }
        }
        return count;
    }

public:
    int kthSmallest(vector<vector<int>> &matrix, int k) {
        int n = matrix.size();
        int low = matrix[0][0];
        int high = matrix[n - 1][n - 1];
        int ans = low;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (countLessOrEqual(matrix, mid, n) >= k) {
                ans = mid;
                high = mid - 1; // Try to find a smaller value that satisfies >= k
            } else {
                low = mid + 1;  // Too few elements <= mid, increase lower bound
            }
        }

        return ans;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF STAIRCASE COUNTING
 * ============================================================================
 *
 * Matrix (3x3):
 * [  1,  5,  9 ]
 * [ 10, 11, 13 ]
 * [ 12, 13, 15 ]
 *
 * If mid = 11:
 * Start at bottom-left (row=2, col=0) -> val=12 > 11 -> move up (row=1)
 * At (row=1, col=0) -> val=10 <= 11 -> count += (1+1)=2 -> move right (col=1)
 * At (row=1, col=1) -> val=11 <= 11 -> count += (1+1)=2 -> move right (col=2)
 * At (row=1, col=2) -> val=13 > 11 -> move up (row=0)
 * At (row=0, col=2) -> val=9 <= 11 -> count += (0+1)=1 -> move right (col=3 -> stop)
 *
 * Total elements <= 11 = 2 + 2 + 1 = 5.
 *
 * ============================================================================
 * DRY RUN (k = 8, Matrix 3x3)
 * ============================================================================
 * | Step | low | high | mid | countLessOrEqual(mid) | Comparison (count >= 8) | Next Range        |
 * | :--- | :-- | :--- | :-- | :-------------------- | :---------------------- | :---------------- |
 * | 1    | 1   | 15   | 8   | 2                     | 2 < 8                   | low = 8 + 1 = 9   |
 * | 2    | 9   | 15   | 12  | 6                     | 6 < 8                   | low = 12 + 1 = 13 |
 * | 3    | 13  | 15   | 14  | 8                     | 8 >= 8 -> ans = 14      | high = 14 - 1 = 13|
 * | 4    | 13  | 13   | 13  | 8                     | 8 >= 8 -> ans = 13      | high = 13 - 1 = 12|
 * | End  | low=13, high=12 (low > high) -> Result ans = 13.                                   |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Price Ceiling Gauge"
 * Guess a price ceiling `mid`. Count how many items in the store are affordable
 * (`<= mid`) by walking the staircase from bottom-left corner in $O(N)$.
 * If you have at least $K$ affordable items, adjust your ceiling down to find the
 * exact threshold.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Search range: `low = matrix[0][0]`, `high = matrix[n-1][n-1]`.
 * - For guess `mid`, count elements `<= mid` in $O(N)$ starting at bottom-left `(n-1, 0)`:
 *     - If `matrix[r][c] <= mid`: `count += (r + 1); c++;`
 *     - Else: `r--;`
 * - If `count >= k`: record `ans = mid` and search left (`high = mid - 1`).
 * - Else: search right (`low = mid + 1`).
 * - Time: O(N * log(Max - Min)), Space: O(1).
 */
