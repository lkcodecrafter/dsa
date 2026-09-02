/*
    QUESTION    : Longest subsequence such that difference between adjacent is one
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-subsequence-such-that-difference-between-adjacents-is-one4724/1
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Dynamic programming storing length of valid subsequence ending at index i
// S.C : O(N)   - DP array
class Solution {
public:
    int longestSubsequence(int N, int A[]) {
        vector<int> dp(N, 1);
        int maxLen = 1;

        for (int i = 1; i < N; i++) {
            for (int j = 0; j < i; j++) {
                if (abs(A[i] - A[j]) == 1) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }

        return maxLen;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i] = 1`.
 * - If `abs(A[i] - A[j]) == 1`: `dp[i] = max(dp[i], dp[j] + 1)`.
 * - Time: O(N^2), Space: O(N).
 */
