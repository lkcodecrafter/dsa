/*
    QUESTION    : Longest Palindromic Subsequence (LPS = LCS(S, reverse(S)))
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-palindromic-subsequence-1612327878/1
    LeetCode    : https://leetcode.com/problems/longest-palindromic-subsequence/
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - LCS between S and reversed S with 1D space optimization
// S.C : O(N)   - 1D DP rows
class Solution {
public:
    int longestPalinSubseq(string A) {
        string B = A;
        reverse(B.begin(), B.end());

        int n = A.length();
        vector<int> prev(n + 1, 0), curr(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (A[i - 1] == B[j - 1]) {
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
 * - `B = reverse(A)`.
 * - Run space-optimized LCS on `A` and `B`.
 * - Time: O(N^2), Space: O(N).
 */
