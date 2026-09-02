/*
    QUESTION    : Check if it is possible to survive on Island
    Company Tags: Amazon, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/check-if-it-is-possible-to-survive-on-island4908/1
*/

#include <iostream>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(1) - Pure mathematical formula
// S.C : O(1) - Constant space
class Solution {
public:
    int minimumDays(int S, int N, int M) {
        // Total food needed for S days
        int totalFoodNeeded = S * M;

        // Buying days available (Cannot buy food on Sundays: 1 Sunday per 7 days)
        int buyingDays = S - (S / 7);

        // Max food we can buy
        int maxFoodPossible = buyingDays * N;

        if (maxFoodPossible < totalFoodNeeded) {
            return -1; // Survival impossible
        }

        // Min days to buy totalFoodNeeded units of food
        int minDays = (totalFoodNeeded + N - 1) / N; // Ceil(totalFoodNeeded / N)
        return minDays;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `buyingDays = S - S/7`.
 * - If `buyingDays * N < S * M`: return -1.
 * - Else return `ceil((S * M) / N)`.
 * - Time: O(1), Space: O(1).
 */
