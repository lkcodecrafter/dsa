/*
    QUESTION    : Strongly connected component (Tarjan's Algorithm)
    Company Tags: Google, Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/strongly-connected-component-tarjanss-algo-1587115621/1
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Single pass Tarjan's SCC algorithm with DFS stack
// S.C : O(V)     - tin, low, inStack, and DFS recursion stack
class Solution {
private:
    int timer = 1;

    void dfs(int u, vector<int> adj[], vector<int>& tin, vector<int>& low,
             stack<int>& st, vector<bool>& inStack, vector<vector<int>>& result) {
        tin[u] = low[u] = timer++;
        st.push(u);
        inStack[u] = true;

        for (int v : adj[u]) {
            if (tin[v] == -1) {
                // Forward edge
                dfs(v, adj, tin, low, st, inStack, result);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) {
                // Back edge to node currently on stack
                low[u] = min(low[u], tin[v]);
            }
        }

        // Head of SCC reached
        if (low[u] == tin[u]) {
            vector<int> scc;
            while (true) {
                int node = st.top();
                st.pop();
                inStack[node] = false;
                scc.push_back(node);
                if (node == u) break;
            }
            sort(scc.begin(), scc.end());
            result.push_back(scc);
        }
    }

public:
    vector<vector<int>> tarjans(int V, vector<int> adj[]) {
        vector<int> tin(V, -1);
        vector<int> low(V, -1);
        vector<bool> inStack(V, false);
        stack<int> st;
        vector<vector<int>> result;

        for (int i = 0; i < V; i++) {
            if (tin[i] == -1) {
                dfs(i, adj, tin, low, st, inStack, result);
            }
        }

        sort(result.begin(), result.end());
        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `tin[u] = low[u] = timer++`; push to `st`.
 * - If `inStack[v]`: `low[u] = min(low[u], tin[v])`.
 * - If `low[u] == tin[u]`: pop from `st` until `node == u` to form SCC.
 * - Time: O(V + E), Space: O(V).
 */
