/*
    QUESTION    : Paths to travel each nodes using each edge (Eulerian Path / Circuit)
    Company Tags: Google
    GfG Link    : https://www.geeksforgeeks.org/paths-travel-nodes-using-edges-directed-graph/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - Hierholzer's Algorithm check (Degree parity verification + connectivity)
// S.C : O(V + E) - Adjacency list and in/out-degree arrays
class Solution {
private:
    void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v, adj, visited);
            }
        }
    }

public:
    // 0 = No Euler path/circuit, 1 = Euler Path, 2 = Euler Circuit
    int isEulerian(int V, vector<vector<int>>& adj) {
        // Step 1: Check connectivity of non-zero degree vertices
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

        for (int i = 0; i < V; i++) {
            if (!visited[i] && !adj[i].empty()) {
                return 0; // Graph is disconnected!
            }
        }

        // Step 2: Count vertices with odd degrees
        int oddDegreeCount = 0;
        for (int i = 0; i < V; i++) {
            if (adj[i].size() % 2 != 0) {
                oddDegreeCount++;
            }
        }

        if (oddDegreeCount == 0) return 2; // Euler Circuit (all even degrees)
        if (oddDegreeCount == 2) return 1; // Euler Path (exactly 2 odd degrees)
        return 0;                          // Non-Eulerian
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Connected non-zero degree components + degree parity:
 *     - `odd == 0` $\rightarrow$ Eulerian Circuit (2)
 *     - `odd == 2` $\rightarrow$ Eulerian Path (1)
 *     - Else $\rightarrow$ Not Eulerian (0).
 * - Time: O(V + E), Space: O(V).
 */
