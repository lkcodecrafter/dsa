/*
 * QUESTION: Maximum profit by buying and selling a share atmost twice
 * Link: https://www.geeksforgeeks.org/maximum-profit-by-buying-and-selling-a-share-at-most-twice/
 * 
 * Input: prices[] = {10, 22, 5, 75, 65, 80}
 * Output: Max Profit = 87
 * Explanation: Buy at 10, sell at 22 (profit 12). Buy at 5, sell at 80 (profit 75). Total profit = 12 + 75 = 87.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// Returns the maximum profit that can be made by buying and selling at most twice.
int maxProfitTwice(const std::vector<int>& prices) {
    if (prices.empty()) return 0;
    
    // Four states representing max profit at different stages:
    // buy1: max profit after buying the 1st stock (negative as we spent money)
    // sell1: max profit after selling the 1st stock
    // buy2: max profit after buying the 2nd stock
    // sell2: max profit after selling the 2nd stock
    int buy1 = INT_MIN;
    int sell1 = 0;
    int buy2 = INT_MIN;
    int sell2 = 0;
    
    for (int p : prices) {
        buy1 = std::max(buy1, -p);
        sell1 = std::max(sell1, buy1 + p);
        buy2 = std::max(buy2, sell1 - p);
        sell2 = std::max(sell2, buy2 + p);
    }
    
    return sell2;
}

/*
 * DRY RUN (prices = {10, 22, 5, 75}):
 * Initial: buy1 = INT_MIN, sell1 = 0, buy2 = INT_MIN, sell2 = 0
 * 
 * | Step | Price p | buy1 = max(buy1, -p) | sell1 = max(sell1, buy1+p) | buy2 = max(buy2, sell1-p) | sell2 = max(sell2, buy2+p) |
 * | :--- | :------ | :------------------- | :------------------------- | :------------------------ | :------------------------- |
 * | 1    | 10      | max(INT_MIN, -10)=-10| max(0, -10+10) = 0         | max(INT_MIN, 0-10) = -10  | max(0, -10+10) = 0         |
 * | 2    | 22      | max(-10, -22) = -10  | max(0, -10+22) = 12        | max(-10, 12-22) = -10     | max(0, -10+22) = 12        |
 * | 3    | 5       | max(-10, -5) = -5    | max(12, -5+5) = 12         | max(-10, 12-5) = 7        | max(12, 7+5) = 12          |
 * | 4    | 75      | max(-5, -75) = -5    | max(12, -5+75) = 70        | max(7, 12-75) = 7         | max(12, 7+75) = 82         |
 * 
 * Max Profit: 82
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Think of it as four piggy banks you carry. 
 * Bank 1 (`buy1`) holds your money after buying stock 1. 
 * Bank 2 (`sell1`) holds cash after selling stock 1. 
 * Bank 3 (`buy2`) is money left after using Bank 2 cash to buy stock 2. 
 * Bank 4 (`sell2`) is your final wealth after selling stock 2. 
 * On each day, you update each bank to maximize its contents based on the current stock price.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize `buy1 = INT_MIN`, `sell1 = 0`, `buy2 = INT_MIN`, `sell2 = 0`.
 * - Iterate through each price `p`:
 *   - Update `buy1 = max(buy1, -p)`.
 *   - Update `sell1 = max(sell1, buy1 + p)`.
 *   - Update `buy2 = max(buy2, sell1 - p)`.
 *   - Update `sell2 = max(sell2, buy2 + p)`.
 * - Return `sell2`.
 * - Time Complexity: O(N)
 * - Space Complexity: O(1)
 */
