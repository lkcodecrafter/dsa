/*
    QUESTION    : Word Wrap Problem
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/word-wrap1646/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Dynamic programming minimizing sum of squares of extra spaces per line
// S.C : O(N)   - DP array
class Solution {
public:
    int solveWordWrap(vector<int> nums, int k) {
        int n = nums.size();
        vector<int> dp(n, 0);

        // dp[i] represents min cost for words from index i to n - 1
        for (int i = n - 1; i >= 0; i--) {
            int currentLength = -1; // -1 accounts for single space between words
            dp[i] = INT_MAX;

            for (int j = i; j < n; j++) {
                currentLength += (nums[j] + 1);

                if (currentLength > k) break; // Exceeds line width

                // If this line includes the last word, cost is 0
                if (j == n - 1) {
                    dp[i] = 0;
                    break;
                }

                int extraSpaces = k - currentLength;
                int cost = extraSpaces * extraSpaces + dp[j + 1];
                dp[i] = min(dp[i], cost);
            }
        }

        return dp[0];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i]` = min cost from word `i` to `n-1`.
 * - Inner loop `j` from `i` to `n-1`: line includes `nums[i...j]`.
 * - If `j == n - 1`: `cost = 0`; else `cost = (k - len)^2 + dp[j + 1]`.
 * - Time: O(N^2), Space: O(N).
 */
