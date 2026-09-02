/*
    QUESTION    : Largest area rectangular sub-matrix with equal number of 1’s and 0’s
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/largest-area-rectangular-sub-matrix-equal-number-1s-0s/
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(C^2 * R) - Map 0 -> -1, 1 -> +1, then find largest zero-sum submatrix
// S.C : O(R)       - Running row sums and prefix map
class Solution {
private:
    int maxZeroSumLength(const vector<int>& arr, int n) {
        unordered_map<int, int> prefixMap;
        int sum = 0;
        int maxLen = 0;

        for (int i = 0; i < n; i++) {
            sum += arr[i];

            if (sum == 0) {
                maxLen = i + 1;
            } else if (prefixMap.find(sum) != prefixMap.end()) {
                maxLen = max(maxLen, i - prefixMap[sum]);
            } else {
                prefixMap[sum] = i;
            }
        }

        return maxLen;
    }

public:
    int maxArea(vector<vector<int>>& mat) {
        int r = mat.size();
        int c = mat[0].size();

        // Convert 0s to -1s
        vector<vector<int>> transformed = mat;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (transformed[i][j] == 0) transformed[i][j] = -1;
            }
        }

        int maxRectangleArea = 0;

        for (int c1 = 0; c1 < c; c1++) {
            vector<int> rowSum(r, 0);

            for (int c2 = c1; c2 < c; c2++) {
                for (int i = 0; i < r; i++) {
                    rowSum[i] += transformed[i][c2];
                }

                int height = maxZeroSumLength(rowSum, r);
                int width = c2 - c1 + 1;

                maxRectangleArea = max(maxRectangleArea, height * width);
            }
        }

        return maxRectangleArea;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Convert 0 to -1, 1 to +1.
 * - Fix column pairs `(c1, c2)`, compress rows, find max zero-sum subarray.
 * - Time: O(C^2 * R), Space: O(R).
 */
