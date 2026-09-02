/*
    QUESTION    : Largest rectangular sub-matrix whose sum is 0
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/largest-rectangular-sub-matrix-whose-sum-is-0/1
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(C^2 * R) - 2D Column-pair compression + 1D Zero-Sum Subarray Hash Map
// S.C : O(R)       - Running row sums and prefix map
class Solution {
private:
    bool maxZeroSumSubarray(const vector<int>& arr, int n, int& startRow, int& endRow) {
        unordered_map<int, int> prefixSumMap;
        int sum = 0;
        int maxLen = 0;

        for (int i = 0; i < n; i++) {
            sum += arr[i];

            if (sum == 0) {
                if (i + 1 > maxLen) {
                    maxLen = i + 1;
                    startRow = 0;
                    endRow = i;
                }
            } else if (prefixSumMap.find(sum) != prefixSumMap.end()) {
                if (i - prefixSumMap[sum] > maxLen) {
                    maxLen = i - prefixSumMap[sum];
                    startRow = prefixSumMap[sum] + 1;
                    endRow = i;
                }
            } else {
                prefixSumMap[sum] = i;
            }
        }

        return maxLen > 0;
    }

public:
    vector<vector<int>> zeroSumSubmat(vector<vector<int>>& mat) {
        int r = mat.size();
        int c = mat[0].size();

        int maxArea = 0;
        int fUp = 0, fDown = -1, fLeft = 0, fRight = -1;

        for (int c1 = 0; c1 < c; c1++) {
            vector<int> rowSum(r, 0);

            for (int c2 = c1; c2 < c; c2++) {
                for (int i = 0; i < r; i++) {
                    rowSum[i] += mat[i][c2];
                }

                int startRow = 0, endRow = -1;
                if (maxZeroSumSubarray(rowSum, r, startRow, endRow)) {
                    int area = (endRow - startRow + 1) * (c2 - c1 + 1);

                    if (area > maxArea) {
                        maxArea = area;
                        fUp = startRow;
                        fDown = endRow;
                        fLeft = c1;
                        fRight = c2;
                    }
                }
            }
        }

        if (maxArea == 0) return {};

        vector<vector<int>> result;
        for (int i = fUp; i <= fDown; i++) {
            vector<int> row;
            for (int j = fLeft; j <= fRight; j++) {
                row.push_back(mat[i][j]);
            }
            result.push_back(row);
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Fix column pairs `(c1, c2)`. Compress rows into `rowSum`.
 * - Run zero-sum subarray check using hash map.
 * - Time: O(C^2 * R), Space: O(R).
 */
