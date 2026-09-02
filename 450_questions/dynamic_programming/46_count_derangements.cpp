/*
    QUESTION    : Count Derangements (Permutations such that no element appears in original position)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/count-derangements/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Recurrence: D(n) = (n - 1) * (D(n - 1) + D(n - 2))
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    long long int countDerangements(int n) {
        if (n == 1) return 0;
        if (n == 2) return 1;

        long long MOD = 1000000007;
        long long prev2 = 0; // D(1) = 0
        long long prev1 = 1; // D(2) = 1

        for (int i = 3; i <= n; i++) {
            long long curr = ((i - 1) * (prev1 + prev2)) % MOD;
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
 * - `curr = ((i - 1) * (prev1 + prev2)) % MOD`.
 * - Time: O(N), Space: O(1).
 */
