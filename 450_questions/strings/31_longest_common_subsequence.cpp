/*
    QUESTION    : Longest Common Subsequence (LCS)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-common-subsequence-1587115620/1
    LeetCode    : https://leetcode.com/problems/longest-common-subsequence/
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - Classic 2D DP
// S.C : O(M)     - Space optimized 1D DP rows
class Solution {
public:
    int lcs(int n, int m, string s1, string s2) {
        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }

        return prev[m];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `s1[i-1] == s2[j-1]`: `curr[j] = 1 + prev[j-1]`.
 * - Else: `curr[j] = max(prev[j], curr[j-1])`.
 * - Time: O(N * M), Space: O(M).
 */
