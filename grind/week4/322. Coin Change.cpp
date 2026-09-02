#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
 * Problem: Coin Change (LeetCode 322)
 * Find the fewest number of coins that you need to make up a given amount.
 *
 * Pattern: Dynamic Programming / 1D DP / Bottom-Up
 *
 * Complexity:
 * - Time Complexity: O(amount * N) where N is the number of coin denominations (coins.size()).
 *   For each amount from 1 to amount, we iterate through all coins.
 * - Space Complexity: O(amount) to store the DP array of size amount + 1.
 *
 * Visualizations:
 * DP Array representing the minimum coins needed for each sub-amount up to amount 5:
 * coins = [1, 2, 5], amount = 5
 *
 * Index (Amount):   0   1   2   3   4   5
 * dp[Index]:       [0,  1,  1,  2,  2,  1]
 *                   |   |   |   |   |   |
 *                   |   |   |   |   |   +--> min(dp[4]+1, dp[3]+1, dp[0]+1) = 1 (uses 5)
 *                   |   |   |   |   +------> min(dp[3]+1, dp[2]+1) = 2 (uses 2+2)
 *                   |   |   |   +----------> min(dp[2]+1, dp[1]+1) = 2 (uses 2+1)
 *                   |   |   +--------------> min(dp[1]+1, dp[0]+1) = 1 (uses 2)
 *                   |   +------------------> min(dp[0]+1) = 1 (uses 1)
 *                   +----------------------> Base Case (0 coins for amount 0)
 *
 * Memorization Hook:
 * "Initialize DP array of size amount+1 with amount+1 (representing infinity). Base case dp[0] = 0.
 * For each amount from 1 to target, try every coin denomination. If the coin is smaller than or equal 
 * to the amount, update dp[amount] = min(dp[amount], dp[amount - coin] + 1)."
 *
 * 1-Minute Quick Revision:
 * 1. Create a `dp` array of size `amount + 1` initialized to `amount + 1`.
 * 2. Set the base case: `dp[0] = 0`.
 * 3. Loop amount `i` from 1 to `amount`.
 * 4. Nested loop over each `coin` in `coins`.
 * 5. If `i - coin >= 0`, set `dp[i] = min(dp[i], dp[i - coin] + 1)`.
 * 6. Return `dp[amount]` if it was reachable (less than `amount + 1`), else return `-1`.
 *
 * Dry Run:
 * coins = [1, 2, 5], amount = 5
 * dp array initially = [0, 6, 6, 6, 6, 6] (6 is amount+1, representing infinity)
 *
 * | Amount i | Coin Option | condition: i - coin >= 0 | dp[i - coin] | Transition: min(dp[i], dp[i - coin] + 1) | dp array after processing amount i |
 * |----------|-------------|--------------------------|--------------|------------------------------------------|-----------------------------------|
 * | 1        | 1           | 1 - 1 = 0 >= 0 (true)    | dp[0] = 0    | min(6, 0 + 1) = 1                        | [0, 1, 6, 6, 6, 6]                |
 * | 1        | 2           | 1 - 2 = -1 >= 0 (false)  | -            | -                                        | [0, 1, 6, 6, 6, 6]                |
 * | 1        | 5           | 1 - 5 = -4 >= 0 (false)  | -            | -                                        | [0, 1, 6, 6, 6, 6]                |
 * | 2        | 1           | 2 - 1 = 1 >= 0 (true)    | dp[1] = 1    | min(6, 1 + 1) = 2                        | [0, 1, 2, 6, 6, 6]                |
 * | 2        | 2           | 2 - 2 = 0 >= 0 (true)    | dp[0] = 0    | min(2, 0 + 1) = 1                        | [0, 1, 1, 6, 6, 6]                |
 * | 2        | 5           | 2 - 5 = -3 >= 0 (false)  | -            | -                                        | [0, 1, 1, 6, 6, 6]                |
 * | 3        | 1           | 3 - 1 = 2 >= 0 (true)    | dp[2] = 1    | min(6, 1 + 1) = 2                        | [0, 1, 1, 2, 6, 6]                |
 * | 3        | 2           | 3 - 2 = 1 >= 0 (true)    | dp[1] = 1    | min(2, 1 + 1) = 2                        | [0, 1, 1, 2, 6, 6]                |
 * | 3        | 5           | 3 - 5 = -2 >= 0 (false)  | -            | -                                        | [0, 1, 1, 2, 6, 6]                |
 * | 4        | 1           | 4 - 1 = 3 >= 0 (true)    | dp[3] = 2    | min(6, 2 + 1) = 3                        | [0, 1, 1, 2, 3, 6]                |
 * | 4        | 2           | 4 - 2 = 2 >= 0 (true)    | dp[2] = 1    | min(3, 1 + 1) = 2                        | [0, 1, 1, 2, 2, 6]                |
 * | 4        | 5           | 4 - 5 = -1 >= 0 (false)  | -            | -                                        | [0, 1, 1, 2, 2, 6]                |
 * | 5        | 1           | 5 - 1 = 4 >= 0 (true)    | dp[4] = 2    | min(6, 2 + 1) = 3                        | [0, 1, 1, 2, 2, 3]                |
 * | 5        | 2           | 5 - 2 = 3 >= 0 (true)    | dp[3] = 2    | min(3, 2 + 1) = 3                        | [0, 1, 1, 2, 2, 3]                |
 * | 5        | 5           | 5 - 5 = 0 >= 0 (true)    | dp[0] = 0    | min(3, 0 + 1) = 1                        | [0, 1, 1, 2, 2, 1]                |
 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] will store the minimum number of coins needed to make amount i
        // Initialize with amount + 1 (representing positive infinity)
        vector<int> dp(amount + 1, amount + 1);
        
        // Base Case: 0 coins needed to make amount 0
        dp[0] = 0;
        
        // Iterate through all sub-amounts from 1 to target amount
        for (int i = 1; i <= amount; i++) {
            // Check each coin denomination
            for (int coin : coins) {
                // If current amount can accommodate the coin
                if (i - coin >= 0) {
                    // Update state to the minimum coins needed
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        // If dp[amount] remains unchanged, amount is unreachable
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }
};