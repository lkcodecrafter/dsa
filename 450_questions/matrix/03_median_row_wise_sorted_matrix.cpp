/*
    QUESTION    : Find median in row wise sorted matrix
    Company Tags: Amazon, Microsoft, Samsung, Payu
    GfG Link    : https://practice.geeksforgeeks.org/problems/median-in-a-row-wise-sorted-matrix1527/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(32 * R * log(C)) - Binary search on the answer range [1, 2000] with upper_bound on each row
// S.C : O(1)               - Constant auxiliary space
class Solution {
private:
    // Counts how many elements in the matrix are <= target
    int countSmallerOrEqual(const vector<vector<int>> &matrix, int target, int R, int C) {
        int count = 0;
        for (int r = 0; r < R; r++) {
            // upper_bound returns iterator to first element > target
            count += upper_bound(matrix[r].begin(), matrix[r].end(), target) - matrix[r].begin();
        }
        return count;
    }

public:
    int median(vector<vector<int>> &matrix, int R, int C) {
        int low = 1;
        int high = 2000; // As per standard GFG matrix value constraints (or min/max elements)

        // Find min and max values in the matrix
        for (int r = 0; r < R; r++) {
            low = min(low, matrix[r][0]);
            high = max(high, matrix[r][C - 1]);
        }

        // The median element has at least (R * C + 1) / 2 elements <= itself
        int desiredCount = (R * C + 1) / 2;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = countSmallerOrEqual(matrix, mid, R, C);

            if (count < desiredCount) {
                low = mid + 1; // Need more elements <= mid
            } else {
                high = mid - 1; // Try to find a smaller valid candidate
            }
        }

        return low;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF MEDIAN IN ROW-WISE SORTED MATRIX
 * ============================================================================
 *
 * Matrix:
 * Row 0: [ 1, 3, 5 ]
 * Row 1: [ 2, 6, 9 ]
 * Row 2: [ 3, 6, 9 ]
 * Total Elements = 9. Desired Count of elements <= Median = (9 + 1) / 2 = 5.
 *
 * If we pick mid = 5:
 * Row 0: elements <= 5 -> {1, 3, 5} (3 elements)
 * Row 1: elements <= 5 -> {2}       (1 element)
 * Row 2: elements <= 5 -> {3}       (1 element)
 * Total count <= 5 = 3 + 1 + 1 = 5 (Matches desired count 5!).
 *
 * ============================================================================
 * DRY RUN (Matrix 3x3, Desired Count = 5)
 * ============================================================================
 * | Step | low | high | mid | Count <= mid across all rows | Comparison (count vs desired) | Next Search Range |
 * | :--- | :-- | :--- | :-- | :--------------------------- | :---------------------------- | :---------------- |
 * | 1    | 1   | 9    | 5   | Row0: 3, Row1: 1, Row2: 1 = 5| count >= 5                    | high = 5 - 1 = 4  |
 * | 2    | 1   | 4    | 2   | Row0: 1, Row1: 1, Row2: 0 = 2| count < 5                     | low = 2 + 1 = 3   |
 * | 3    | 3   | 4    | 3   | Row0: 2, Row1: 1, Row2: 1 = 4| count < 5                     | low = 3 + 1 = 4   |
 * | 4    | 4   | 4    | 4   | Row0: 2, Row1: 1, Row2: 1 = 4| count < 5                     | low = 4 + 1 = 5   |
 * | End  | low=5, high=4 (low > high) -> Loop ends. Answer = low = 5.                                              |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Median Census"
 * To find the median test score in a school with sorted classroom lists:
 * Guess a test score `mid`. Count how many students across all classes scored `<= mid`
 * (using binary search in each class). If at least 50% scored `<= mid`, try a lower guess;
 * otherwise raise your guess.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Median has at least `(R * C + 1) / 2` elements smaller than or equal to it.
 * - Perform Binary Search on the VALUE RANGE `[min_element, max_element]`.
 * - For a guess `mid`, count elements `<= mid` using `upper_bound()` on each row in `O(R * log(C))`.
 * - If `count < (R * C + 1) / 2`: `low = mid + 1`.
 * - Else: `high = mid - 1`.
 * - Answer is `low` when loop terminates.
 * - Time: O(32 * R * log C), Space: O(1).
 */
