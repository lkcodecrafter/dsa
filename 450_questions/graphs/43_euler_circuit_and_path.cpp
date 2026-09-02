/*
    QUESTION    : Eulerian Circuit and Eulerian Path in an Undirected Graph
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/euler-circuit-and-path/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - DFS connectivity check + odd degree parity counter
// S.C : O(V)     - Visited array
class Solution {
private:
    void dfs(int u, vector<int> adj[], vector<bool>& visited) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v, adj, visited);
            }
        }
    }

public:
    int isEulerCircuit(int V, vector<int> adj[]) {
        vector<bool> visited(V, false);

        int nonZeroNode = -1;
        for (int i = 0; i < V; i++) {
            if (!adj[i].empty()) {
                nonZeroNode = i;
                break;
            }
        }

        if (nonZeroNode == -1) return 2; // Empty graph is Eulerian

        dfs(nonZeroNode, adj, visited);

        // Check if all vertices with non-zero degree are connected
        for (int i = 0; i < V; i++) {
            if (!visited[i] && !adj[i].empty()) {
                return 0;
            }
        }

        int oddDegrees = 0;
        for (int i = 0; i < V; i++) {
            if (adj[i].size() % 2 != 0) {
                oddDegrees++;
            }
        }

        if (oddDegrees == 0) return 2; // Eulerian Circuit
        if (oddDegrees == 2) return 1; // Eulerian Path
        return 0;                      // Neither
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `oddDegrees == 0` $\rightarrow$ Eulerian Circuit (2).
 * - `oddDegrees == 2` $\rightarrow$ Eulerian Path (1).
 * - Else $\rightarrow$ Neither (0).
 * - Time: O(V + E), Space: O(V).
 */
