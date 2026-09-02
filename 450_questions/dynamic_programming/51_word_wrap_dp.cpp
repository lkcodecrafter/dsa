/*
    QUESTION    : Word Wrap (Minimize sum of cubes of extra spaces)
    Company Tags: Amazon, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/word-wrap1646/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Dynamic programming computing minimum line cost
// S.C : O(N)   - DP array
class Solution {
public:
    int solveWordWrap(vector<int> nums, int k) {
        int n = nums.size();
        vector<int> dp(n, INT_MAX);

        // Process from end of array backwards
        for (int i = n - 1; i >= 0; i--) {
            int len = 0;

            for (int j = i; j < n; j++) {
                len += nums[j];

                // Total length on this line including single spaces between words
                int totalLength = len + (j - i);

                if (totalLength > k) break;

                // For the last line (j == n - 1), trailing extra spaces have 0 cost!
                if (j == n - 1) {
                    dp[i] = 0;
                } else {
                    int extraSpaces = k - totalLength;
                    int cost = extraSpaces * extraSpaces + dp[j + 1];
                    dp[i] = min(dp[i], cost);
                }
            }
        }

        return dp[0];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `cost = (k - totalLength)^2 + dp[j+1]`.
 * - Last line has 0 extra cost.
 * - Time: O(N^2), Space: O(N).
 */
