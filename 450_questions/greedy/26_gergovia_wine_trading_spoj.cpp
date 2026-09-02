/*
    QUESTION    : GERGOVIA - Wine trading in Gergovia (SPOJ)
    Company Tags: Google
    Link        : https://www.spoj.com/problems/GERGOVIA/
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Prefix sum running balance accumulation
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    long long minWorkToTradeWine(int n, const vector<long long>& a) {
        long long currentBalance = 0;
        long long totalWork = 0;

        for (int i = 0; i < n; i++) {
            currentBalance += a[i];
            totalWork += abs(currentBalance); // Transporting wine over 1 unit distance
        }

        return totalWork;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `currentBalance += a[i]`.
 * - `totalWork += abs(currentBalance)`.
 * - Time: O(N), Space: O(1).
 */
