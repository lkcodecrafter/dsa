/*
    QUESTION    : Oliver and the Game (Subtree Query / In-Out Time Euler Tour)
    Company Tags: Google, HackerEarth
    Link        : https://www.hackerearth.com/practice/algorithms/graphs/topological-sort/practice-problems/algorithm/oliver-and-the-game-3/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + Q) - Euler Tour In-Out discovery timestamps answer subtree queries in O(1) time
// S.C : O(V)     - inTime and outTime arrays
class Solution {
private:
    int timer = 1;

    void dfs(int u, int parent, const vector<vector<int>>& adj, vector<int>& inTime, vector<int>& outTime) {
        inTime[u] = timer++;

        for (int v : adj[u]) {
            if (v != parent) {
                dfs(v, u, adj, inTime, outTime);
            }
        }

        outTime[u] = timer++;
    }

    // Check if node u is an ancestor of node v
    bool isAncestor(int u, int v, const vector<int>& inTime, const vector<int>& outTime) {
        return inTime[u] <= inTime[v] && outTime[u] >= outTime[v];
    }

public:
    vector<bool> oliverAndGame(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<int>> adj(n + 1);
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        vector<int> inTime(n + 1, 0);
        vector<int> outTime(n + 1, 0);

        dfs(1, 0, adj, inTime, outTime);

        vector<bool> results;

        for (auto& q : queries) {
            int type = q[0];
            int x = q[1]; // Oliver
            int y = q[2]; // Bob

            if (type == 0) {
                // Bob is moving towards root: Oliver (x) must be in Bob's (y) subtree, i.e., y is ancestor of x
                results.push_back(isAncestor(y, x, inTime, outTime));
            } else {
                // Bob is moving away from root: Bob (y) must be in Oliver's (x) subtree, i.e., x is ancestor of y
                results.push_back(isAncestor(x, y, inTime, outTime));
            }
        }

        return results;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Euler Tour with `inTime[u]` and `outTime[u]`.
 * - `isAncestor(u, v) = (inTime[u] <= inTime[v] && outTime[u] >= outTime[v])`.
 * - Query 0: `isAncestor(y, x)`; Query 1: `isAncestor(x, y)`.
 * - Time: O(V + Q), Space: O(V).
 */
