/*
    QUESTION    : Coin game winner where every player has three choices (A and B pick 1, x, or y coins)
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/coin-game-winner-every-player-three-choices/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Game Theory DP: player wins if any move forces opponent into losing state
// S.C : O(N) - Boolean winning state array
class Solution {
public:
    bool findWinner(int n, int x, int y) {
        // dp[i] = true if first player to move from state i wins
        vector<bool> dp(n + 1, false);

        dp[0] = false; // 0 coins -> previous player took last coin, current player loses
        dp[1] = true;

        for (int i = 2; i <= n; i++) {
            // If taking 1, x, or y coins leads to a losing state for opponent (!dp)
            if (i - 1 >= 0 && !dp[i - 1]) {
                dp[i] = true;
            } else if (i - x >= 0 && !dp[i - x]) {
                dp[i] = true;
            } else if (i - y >= 0 && !dp[i - y]) {
                dp[i] = true;
            } else {
                dp[i] = false;
            }
        }

        return dp[n];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i] = (!dp[i-1] || (i>=x && !dp[i-x]) || (i>=y && !dp[i-y]))`.
 * - Time: O(N), Space: O(N).
 */
