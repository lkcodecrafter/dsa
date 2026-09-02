/*
    QUESTION    : Maximum profit by buying and selling a share at most twice
    Company Tags: Amazon, Microsoft, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximum-profit4657/1
    LeetCode    : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - 4-state dynamic programming
// S.C : O(1) - 4 scalar variables
class Solution {
public:
    int maxProfit(vector<int>& price) {
        int buy1 = INT_MAX, profit1 = 0;
        int buy2 = INT_MAX, profit2 = 0;

        for (int p : price) {
            buy1 = min(buy1, p);
            profit1 = max(profit1, p - buy1);

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
 * - Time: O(N), Space: O(1).
 */
