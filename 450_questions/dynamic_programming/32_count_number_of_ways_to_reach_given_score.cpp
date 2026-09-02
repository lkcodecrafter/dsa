/*
    QUESTION    : Reach a given score (Scores: 3, 5, and 10)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/reach-a-given-score-1587115621/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Coin change DP with denominations {3, 5, 10}
// S.C : O(N) - 1D DP table
long long int count(long long int n) {
    vector<long long int> dp(n + 1, 0);
    dp[0] = 1;

    // Denominations: 3, 5, 10
    int scores[] = {3, 5, 10};

    for (int s : scores) {
        for (int i = s; i <= n; i++) {
            dp[i] += dp[i - s];
        }
    }

    return dp[n];
}

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[0] = 1`.
 * - Run 1D coin change for `{3, 5, 10}`.
 * - Time: O(N), Space: O(N).
 */
