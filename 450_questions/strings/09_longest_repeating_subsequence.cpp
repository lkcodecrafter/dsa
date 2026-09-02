/*
    QUESTION    : Longest Repeating Subsequence
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-repeating-subsequence2004/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - LCS of string with itself with condition (i != j)
// S.C : O(N)   - Space optimized 1D DP
class Solution {
public:
    int LongestRepeatingSubsequence(string str) {
        int n = str.length();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // Characters match AND are at different indices
                if (str[i - 1] == str[j - 1] && i != j) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }

        return prev[n];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Modified LCS of `str` with `str` where `i != j`.
 * - If `str[i-1] == str[j-1] && i != j`: `curr[j] = 1 + prev[j-1]`; else `curr[j] = max(prev[j], curr[j-1])`.
 * - Time: O(N^2), Space: O(N).
 */
