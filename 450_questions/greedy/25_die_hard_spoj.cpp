/*
    QUESTION    : DIEHARD - DIE HARD (SPOJ)
    Company Tags: Google
    Link        : https://www.spoj.com/problems/DIEHARD/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(H * A) - Memoized DP state transitions (Air, Water, Fire)
// S.C : O(H * A) - 3D DP memo table
class Solution {
private:
    int dp[1005][1005][4];

    // last: 1 = Air, 2 = Water, 3 = Fire
    int solve(int h, int a, int last) {
        if (h <= 0 || a <= 0) return 0;
        if (dp[h][a][last] != -1) return dp[h][a][last];

        int ans = 0;

        // Air gives (+3 H, +2 A) -> Always optimal to move to Air whenever allowed!
        if (last != 1) {
            ans = max(ans, 1 + solve(h + 3, a + 2, 1));
        } else {
            // If currently in Air, choose between Water (-5 H, -10 A) and Fire (-20 H, +5 A)
            if (h > 5 && a > 10) {
                ans = max(ans, 1 + solve(h - 5, a - 10, 2));
            }
            if (h > 20) {
                ans = max(ans, 1 + solve(h - 20, a + 5, 3));
            }
        }

        return dp[h][a][last] = ans;
    }

public:
    int maxSurvivalTime(int h, int a) {
        for (int i = 0; i <= 1000; i++) {
            for (int j = 0; j <= 1000; j++) {
                for (int k = 0; k < 4; k++) {
                    dp[i][j][k] = -1;
                }
            }
        }

        // Start by stepping into Air
        return solve(h, a, 0);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Air (+3 H, +2 A) is always visited every alternate turn.
 * - From Air, choose between Water (-5 H, -10 A) or Fire (-20 H, +5 A).
 * - Time: O(H * A), Space: O(H * A).
 */
