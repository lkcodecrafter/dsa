/*
    QUESTION    : Count balanced binary trees of height h (AVL Trees count)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/count-balanced-binary-trees-of-height-h/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(H) - DP recurrence: dp[h] = dp[h-1]^2 + 2 * dp[h-1] * dp[h-2]
// S.C : O(1) - Two variables for previous heights
class Solution {
public:
    long long int countBT(int h) {
        if (h == 0 || h == 1) return 1;

        long long MOD = 1000000007;
        long long prev2 = 1; // h = 0
        long long prev1 = 1; // h = 1

        for (int i = 2; i <= h; i++) {
            long long term1 = (prev1 * prev1) % MOD;
            long long term2 = (2LL * prev1 * prev2) % MOD;
            long long curr = (term1 + term2) % MOD;

            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[h] = (dp[h-1]^2 + 2 * dp[h-1] * dp[h-2]) % MOD`.
 * - Time: O(H), Space: O(1).
 */
