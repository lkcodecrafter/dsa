/*
    QUESTION    : Wildcard String Matching ('?' matches 1 char, '*' matches 0 or more chars)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/wildcard-string-matching1126/1
    LeetCode    : https://leetcode.com/problems/wildcard-matching/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - 2D DP
// S.C : O(M)     - Space optimized 1D DP rows
class Solution {
public:
    bool match(string wild, string pattern) {
        int n = wild.length();
        int m = pattern.length();

        vector<bool> prev(m + 1, false), curr(m + 1, false);

        prev[0] = true;

        for (int i = 1; i <= n; i++) {
            // '*' can match empty sequence if previous prefix matched
            curr[0] = prev[0] && (wild[i - 1] == '*');

            for (int j = 1; j <= m; j++) {
                if (wild[i - 1] == pattern[j - 1] || wild[i - 1] == '?') {
                    curr[j] = prev[j - 1];
                } else if (wild[i - 1] == '*') {
                    // Match 0 characters (prev[j]) OR match 1+ characters (curr[j - 1])
                    curr[j] = prev[j] || curr[j - 1];
                } else {
                    curr[j] = false;
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
 * - If `wild[i-1] == pattern[j-1] || wild[i-1] == '?'`: `curr[j] = prev[j-1]`.
 * - If `wild[i-1] == '*'`: `curr[j] = prev[j] || curr[j-1]`.
 * - Time: O(N * M), Space: O(M).
 */
