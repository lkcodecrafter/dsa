/*
    QUESTION    : Longest Common Substring
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-common-substring1452/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - 1D Space Optimized DP
// S.C : O(M)     - 1D DP row
class Solution {
public:
    int longestCommonSubstr (string S1, string S2, int n, int m) {
        vector<int> prev(m + 1, 0), curr(m + 1, 0);
        int maxLen = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (S1[i - 1] == S2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                    maxLen = max(maxLen, curr[j]);
                } else {
                    curr[j] = 0; // Substring continuity reset
                }
            }
            prev = curr;
        }

        return maxLen;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `curr[j] = (S1[i-1] == S2[j-1]) ? 1 + prev[j-1] : 0`.
 * - Track global `maxLen`.
 * - Time: O(N * M), Space: O(M).
 */
