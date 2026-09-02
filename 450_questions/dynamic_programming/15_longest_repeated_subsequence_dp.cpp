/*
    QUESTION    : Longest Repeated Subsequence (DP Solution)
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-repeating-subsequence2004/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - LCS with i != j constraint
// S.C : O(N)   - 1D DP rows
class Solution {
public:
    int LongestRepeatingSubsequence(string str) {
        int n = str.length();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
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
 * - `str[i-1] == str[j-1] && i != j ? 1 + prev[j-1] : max(prev[j], curr[j-1])`.
 * - Time: O(N^2), Space: O(N).
 */
