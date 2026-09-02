/*
    QUESTION    : Edit Distance (Levenshtein Distance)
    Company Tags: Amazon, Microsoft, Google, Goldman Sachs
    GfG Link    : https://practice.geeksforgeeks.org/problems/edit-distance3702/1
    LeetCode    : https://leetcode.com/problems/edit-distance/
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - DP with Insert, Delete, and Replace operations
// S.C : O(M)     - 1D array space optimization
class Solution {
public:
    int editDistance(string s, string t) {
        int n = s.length();
        int m = t.length();

        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        for (int j = 0; j <= m; j++) {
            prev[j] = j;
        }

        for (int i = 1; i <= n; i++) {
            curr[0] = i;

            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1]) {
                    curr[j] = prev[j - 1]; // No operation required
                } else {
                    int insertOp = curr[j - 1];
                    int deleteOp = prev[j];
                    int replaceOp = prev[j - 1];

                    curr[j] = 1 + min({insertOp, deleteOp, replaceOp});
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
 * - If `s[i-1] == t[j-1]`: `curr[j] = prev[j-1]`.
 * - Else: `curr[j] = 1 + min({insert(curr[j-1]), delete(prev[j]), replace(prev[j-1])})`.
 * - Time: O(N * M), Space: O(M).
 */
