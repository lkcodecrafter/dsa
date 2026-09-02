/*
    QUESTION    : Space Optimized LCS (Longest Common Subsequence using 2 rows)
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/space-optimized-approaches-for-longest-common-subsequence/
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - LCS with 2 rows of size min(N, M)
// S.C : O(min(N, M)) - Exact 2 rows
class Solution {
public:
    int lcs(string s1, string s2) {
        if (s1.length() < s2.length()) swap(s1, s2); // Ensure s2 is the smaller string

        int n = s1.length();
        int m = s2.length();

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
 * - Ensure $s2$ is smaller string $\rightarrow$ space reduces to $O(\min(N, M))$.
 * - Time: O(N * M), Space: O(min(N, M)).
 */
