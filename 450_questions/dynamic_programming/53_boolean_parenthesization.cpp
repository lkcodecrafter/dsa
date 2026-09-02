/*
    QUESTION    : Boolean Parenthesization (Count ways to evaluate expression to True)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/boolean-parenthesization5610/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^3) - MCM Partition Interval DP tracking True and False counts
// S.C : O(N^2) - 3D DP memo table
class Solution {
private:
    long long MOD = 1003;
    long long dp[205][205][2];

    long long solve(const string& S, int i, int j, bool isTrue) {
        if (i > j) return 0;
        if (i == j) {
            if (isTrue) return S[i] == 'T';
            else return S[i] == 'F';
        }

        if (dp[i][j][isTrue] != -1) {
            return dp[i][j][isTrue];
        }

        long long ways = 0;

        for (int k = i + 1; k < j; k += 2) {
            long long lT = solve(S, i, k - 1, true);
            long long lF = solve(S, i, k - 1, false);
            long long rT = solve(S, k + 1, j, true);
            long long rF = solve(S, k + 1, j, false);

            char op = S[k];

            if (op == '&') {
                if (isTrue) ways = (ways + (lT * rT)) % MOD;
                else ways = (ways + (lF * rT) + (lT * rF) + (lF * rF)) % MOD;
            } else if (op == '|') {
                if (isTrue) ways = (ways + (lT * rT) + (lT * rF) + (lF * rT)) % MOD;
                else ways = (ways + (lF * rF)) % MOD;
            } else if (op == '^') {
                if (isTrue) ways = (ways + (lT * rF) + (lF * rT)) % MOD;
                else ways = (ways + (lT * rT) + (lF * rF)) % MOD;
            }
        }

        return dp[i][j][isTrue] = ways % MOD;
    }

public:
    int countWays(int N, string S) {
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j <= N; j++) {
                dp[i][j][0] = -1;
                dp[i][j][1] = -1;
            }
        }

        return solve(S, 0, N - 1, true);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `dp[i][j][isTrue]` partitions at operators `k = i+1..j-1`.
 * - Combine boolean subproblems for `&`, `|`, and `^`.
 * - Time: O(N^3), Space: O(N^2).
 */
