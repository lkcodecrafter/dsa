/*
    QUESTION    : Longest Common Subsequence (DP Solution)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-common-subsequence-1587115620/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - 1D Space Optimized LCS
// S.C : O(M)     - 1D DP rows
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
 * - `curr[j] = (s1[i-1] == s2[j-1]) ? 1 + prev[j-1] : max(prev[j], curr[j-1])`.
 * - Time: O(N * M), Space: O(M).
 */
