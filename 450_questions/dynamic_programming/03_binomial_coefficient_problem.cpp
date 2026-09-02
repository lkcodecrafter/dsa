/*
    QUESTION    : nCr (Binomial Coefficient Problem)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/ncr1019/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * R) - Pascal's Triangle identity: C(n, r) = C(n-1, r-1) + C(n-1, r)
// S.C : O(R)     - Space optimized 1D DP row
class Solution {
public:
    int nCr(int n, int r) {
        if (r > n) return 0;
        if (r == 0 || r == n) return 1;

        // Symmetry property: C(n, r) = C(n, n - r)
        if (r > n / 2) r = n - r;

        long long MOD = 1000000007;
        vector<long long> dp(r + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = min(i, r); j > 0; j--) {
                dp[j] = (dp[j] + dp[j - 1]) % MOD;
            }
        }

        return dp[r];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Pascal's identity: `dp[j] = (dp[j] + dp[j - 1]) % MOD`.
 * - Inner loop `j` from `min(i, r)` down to 1.
 * - Time: O(N * R), Space: O(R).
 */
