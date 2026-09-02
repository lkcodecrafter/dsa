/*
    QUESTION    : Permutation Coefficient Problem (P(n, k) = n! / (n - k)!)
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/permutation-coefficient/
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(K) - P(n, k) = n * (n - 1) * ... * (n - k + 1)
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    long long permutationCoeff(int n, int k) {
        long long P = 1;
        long long MOD = 1000000007;

        for (int i = 0; i < k; i++) {
            P = (P * (n - i)) % MOD;
        }

        return P;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `P = (P * (n - i)) % MOD` for `i` from `0` to `k - 1`.
 * - Time: O(K), Space: O(1).
 */
