/*
    QUESTION    : Maximum profit by buying and selling a share at most twice (Best Time to Buy and Sell Stock III)
    Company Tags: Amazon, Microsoft, Google, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximum-profit4657/1
    LeetCode    : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - 4-state DP in a single linear pass
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int maxProfit(vector<int>& price) {
        int buy1 = INT_MAX;
        int profit1 = 0;
        int buy2 = INT_MAX;
        int profit2 = 0;

        for (int p : price) {
            // First transaction
            buy1 = min(buy1, p);
            profit1 = max(profit1, p - buy1);

            // Second transaction (reinvesting profit from first transaction)
            buy2 = min(buy2, p - profit1);
            profit2 = max(profit2, p - buy2);
        }

        return profit2;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `buy1 = min(buy1, p); profit1 = max(profit1, p - buy1);`
 * - `buy2 = min(buy2, p - profit1); profit2 = max(profit2, p - buy2);`
 * - Return `profit2`.
 * - Time: O(N), Space: O(1).
 */
