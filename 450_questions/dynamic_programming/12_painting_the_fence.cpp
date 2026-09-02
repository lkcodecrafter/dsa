/*
    QUESTION    : Painting the Fence (No more than 2 consecutive posts have same color)
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/painting-the-fence3727/1
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear DP with constant space
// S.C : O(1) - Two state variables: same and diff
class Solution {
public:
    long long countWays(int n, int k) {
        if (n == 1) return k;

        long long MOD = 1000000007;

        long long same = k;
        long long diff = (long long)k * (k - 1) % MOD;
        long long total = (same + diff) % MOD;

        for (int i = 3; i <= n; i++) {
            same = diff;
            diff = (total * (k - 1)) % MOD;
            total = (same + diff) % MOD;
        }

        return total;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `same = diff; diff = (total * (k - 1)) % MOD; total = same + diff`.
 * - Time: O(N), Space: O(1).
 */
