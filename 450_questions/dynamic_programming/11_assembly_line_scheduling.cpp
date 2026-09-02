/*
    QUESTION    : Assembly Line Scheduling
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/assembly-line-scheduling-dp-34/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear DP with 2 state variables
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int carAssembly(int n, vector<vector<int>>& a, vector<vector<int>>& t, vector<int>& e, vector<int>& x) {
        // Base case: entry times
        int T1 = e[0] + a[0][0]; // Min time to leave station 0 on line 1
        int T2 = e[1] + a[1][0]; // Min time to leave station 0 on line 2

        for (int i = 1; i < n; i++) {
            int newT1 = min(T1 + a[0][i], T2 + t[1][i] + a[0][i]);
            int newT2 = min(T2 + a[1][i], T1 + t[0][i] + a[1][i]);

            T1 = newT1;
            T2 = newT2;
        }

        // Add exit times
        return min(T1 + x[0], T2 + x[1]);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `T1 = min(T1 + a[0][i], T2 + t[1][i] + a[0][i])`.
 * - `T2 = min(T2 + a[1][i], T1 + t[0][i] + a[1][i])`.
 * - Return `min(T1 + x[0], T2 + x[1])`.
 * - Time: O(N), Space: O(1).
 */
