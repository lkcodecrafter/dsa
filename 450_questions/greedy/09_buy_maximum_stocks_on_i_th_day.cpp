/*
    QUESTION    : Buy Maximum Stocks if i stocks can be bought on i-th day
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/buy-maximum-stocks-if-i-stocks-can-be-bought-on-i-th-day/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting stocks by price + greedy purchasing
// S.C : O(N)       - Vector of pairs storing {price, day}
class Solution {
public:
    int buyMaximumProducts(int n, int k, int price[]) {
        vector<pair<int, int>> stocks(n);

        // Store {price, max_stocks_can_buy} where max_stocks_can_buy = i + 1 on (i+1)-th day
        for (int i = 0; i < n; i++) {
            stocks[i] = {price[i], i + 1};
        }

        // Sort ascending by price
        sort(stocks.begin(), stocks.end());

        int totalStocksBought = 0;

        for (int i = 0; i < n; i++) {
            int stockPrice = stocks[i].first;
            int stockLimit = stocks[i].second;

            // Maximum stocks we can afford to buy at current price
            int buyCount = min(stockLimit, k / stockPrice);

            totalStocksBought += buyCount;
            k -= (buyCount * stockPrice);

            if (k <= 0) break;
        }

        return totalStocksBought;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Store `{price[i], i + 1}` and sort by price ascending.
 * - Greedily buy `count = min(day, k / price)`.
 * - Time: O(N log N), Space: O(N).
 */
