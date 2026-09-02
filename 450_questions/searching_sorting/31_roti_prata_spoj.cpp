/*
    QUESTION    : PRATA - Roti Prata (SPOJ)
    Company Tags: Google
    Link        : https://www.spoj.com/problems/PRATA/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(Cooks * log(Max_Time)) - Binary Search on minimum time to make P pratas
// S.C : O(1)                     - Constant auxiliary space
class Solution {
private:
    bool isPossible(int P, const vector<int>& ranks, int timeLimit) {
        int totalPratas = 0;

        for (int r : ranks) {
            int timeSpent = 0;
            int count = 1;

            // Cook makes k pratas in r + 2r + 3r + ... + kr = r * k*(k+1)/2 time
            while (timeSpent + count * r <= timeLimit) {
                timeSpent += count * r;
                totalPratas++;
                count++;
                if (totalPratas >= P) return true;
            }
        }

        return totalPratas >= P;
    }

public:
    int minTimeToMakePratas(int P, vector<int>& ranks) {
        int low = 0;
        int maxRank = *max_element(ranks.begin(), ranks.end());
        int high = maxRank * (P * (P + 1)) / 2; // Worst case: slowest cook makes all P pratas
        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isPossible(P, ranks, mid)) {
                ans = mid;
                high = mid - 1; // Try smaller time
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Cook of rank $R$ takes $R \times \frac{k(k+1)}{2}$ minutes to bake $k$ pratas.
 * - Binary search on time $T \in [0, \text{high}]$.
 * - Time: O(C log(max_T)), Space: O(1).
 */
