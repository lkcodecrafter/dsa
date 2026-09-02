/*
    QUESTION    : Maximum subsequence sum such that no three are consecutive
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/maximum-subsequence-sum-such-that-no-three-are-consecutive/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - 1D DP considering 3 mutual exclusion scenarios
// S.C : O(N) - DP array
class Solution {
public:
    int maxSumWO3Consec(vector<int>& arr, int n) {
        if (n == 0) return 0;
        if (n == 1) return arr[0];
        if (n == 2) return arr[0] + arr[1];

        vector<int> dp(n, 0);

        dp[0] = arr[0];
        dp[1] = arr[0] + arr[1];
        dp[2] = max({dp[1], arr[0] + arr[2], arr[1] + arr[2]});

        for (int i = 3; i < n; i++) {
            dp[i] = max({
                dp[i - 1],                          // Exclude arr[i]
                dp[i - 2] + arr[i],                 // Include arr[i], exclude arr[i-1]
                dp[i - 3] + arr[i - 1] + arr[i]     // Include arr[i] and arr[i-1], exclude arr[i-2]
            });
        }

        return dp[n - 1];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i] = max({dp[i-1], dp[i-2] + arr[i], dp[i-3] + arr[i-1] + arr[i]})`.
 * - Time: O(N), Space: O(N).
 */
