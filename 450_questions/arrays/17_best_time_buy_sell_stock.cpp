/*
 * QUESTION: Best time to buy and Sell stock
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * 
 * Input: prices[] = {7, 1, 5, 3, 6, 4}
 * Output: Max Profit = 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Returns the maximum profit that can be achieved.
int maxProfit(const std::vector<int>& prices) {
    if (prices.empty()) return 0;
    
    int min_price = prices[0];
    int max_profit = 0;
    
    for (size_t i = 1; i < prices.size(); i++) {
        // If we sell today, what is the profit?
        int potential_profit = prices[i] - min_price;
        
        // Update the maximum profit
        max_profit = std::max(max_profit, potential_profit);
        
        // Keep track of the lowest buying price seen so far
        min_price = std::min(min_price, prices[i]);
    }
    
    return max_profit;
}

/*
 * DRY RUN (prices = {7, 1, 5, 3, 6, 4}):
 * Initial: min_price = 7, max_profit = 0
 * 
 * | Step | i | Price | Potential Profit = Price - min_price | max_profit Updated | min_price Updated | Action                           |
 * | :--- | :-| :---- | :---------------------------------- | :----------------- | :---------------- | :------------------------------- |
 * | Init | - | -     | -                                   | 0                  | 7                 | Start loop at index 1            |
 * | 1    | 1 | 1     | 1 - 7 = -6                          | 0                  | 1                 | min_price updated to 1           |
 * | 2    | 2 | 5     | 5 - 1 = 4                           | 4                  | 1                 | max_profit updated to 4          |
 * | 3    | 3 | 3     | 3 - 1 = 2                           | 4                  | 1                 | No update                        |
 * | 4    | 4 | 6     | 6 - 1 = 5                           | 5                  | 1                 | max_profit updated to 5          |
 * | 5    | 5 | 4     | 4 - 1 = 3                           | 5                  | 1                 | No update                        |
 * 
 * Max Profit: 5
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine tracking a stock's price history. 
 * As you scan forward in time, you remember the cheapest price you've ever seen (`min_price`). 
 * For every new price, you check if selling today yields a better profit than your previous best record.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize `min_price = prices[0]` and `max_profit = 0`.
 * - Traverse from index 1 to the end:
 *   - Update `max_profit = max(max_profit, prices[i] - min_price)`.
 *   - Update `min_price = min(min_price, prices[i])`.
 * - Return `max_profit`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1)
 */
