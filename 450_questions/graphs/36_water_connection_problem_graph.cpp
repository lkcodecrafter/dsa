/*
    QUESTION    : Water Connection Problem (Graph DFS / Pipe network component discovery)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/water-connection-problem5822/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N + P) - Tracing connected pipe networks
// S.C : O(N)     - Mapping arrays
class Solution {
private:
    void dfs(int u, const vector<int>& outgoing, const vector<int>& diameter, int& tap, int& minDiam) {
        if (outgoing[u] == 0) {
            tap = u;
            return;
        }

        minDiam = min(minDiam, diameter[u]);
        dfs(outgoing[u], outgoing, diameter, tap, minDiam);
    }

public:
    vector<vector<int>> solve(int n, int p, vector<int> a, vector<int> b, vector<int> d) {
        vector<int> incoming(n + 1, 0);
        vector<int> outgoing(n + 1, 0);
        vector<int> diameter(n + 1, 0);

        for (int i = 0; i < p; i++) {
            outgoing[a[i]] = b[i];
            diameter[a[i]] = d[i];
            incoming[b[i]] = a[i];
        }

        vector<vector<int>> result;

        for (int i = 1; i <= n; i++) {
            // Source tank node: has outgoing pipe but no incoming pipe
            if (incoming[i] == 0 && outgoing[i] > 0) {
                int tap = 0;
                int minDiam = INT_MAX;
                dfs(i, outgoing, diameter, tap, minDiam);
                result.push_back({i, tap, minDiam});
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Tank: `incoming == 0 && outgoing > 0`.
 * - DFS down outgoing edges tracking `minDiam`.
 * - Time: O(N + P), Space: O(N).
 */
