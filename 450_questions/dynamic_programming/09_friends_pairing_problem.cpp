/*
    QUESTION    : Friends Pairing Problem (f(n) = f(n-1) + (n-1)*f(n-2))
    Company Tags: Amazon, Goldman Sachs
    GfG Link    : https://practice.geeksforgeeks.org/problems/friends-pairing-problem5425/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear DP with constant auxiliary space
// S.C : O(1) - Two state variables
class Solution {
public:
    int countFriendsPairings(int n) {
        if (n <= 2) return n;

        long long MOD = 1000000007;
        long long prev2 = 1; // f(1) = 1
        long long prev1 = 2; // f(2) = 2

        for (int i = 3; i <= n; i++) {
            long long curr = (prev1 + (i - 1) * prev2) % MOD;
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
 * - `curr = (prev1 + (i - 1) * prev2) % MOD`.
 * - Time: O(N), Space: O(1).
 */
