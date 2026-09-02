/*
    QUESTION    : Edit Distance (DP Solution)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/edit-distance3702/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * M) - DP with 1D space optimization
// S.C : O(M)     - 1D DP rows
class Solution {
public:
    int editDistance(string s, string t) {
        int n = s.length();
        int m = t.length();

        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        for (int j = 0; j <= m; j++) prev[j] = j;

        for (int i = 1; i <= n; i++) {
            curr[0] = i;
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == t[j - 1]) {
                    curr[j] = prev[j - 1];
                } else {
                    curr[j] = 1 + min({curr[j - 1], prev[j], prev[j - 1]});
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
 * - `curr[j] = (s[i-1] == t[j-1]) ? prev[j-1] : 1 + min({insert(curr[j-1]), delete(prev[j]), replace(prev[j-1])})`.
 * - Time: O(N * M), Space: O(M).
 */
