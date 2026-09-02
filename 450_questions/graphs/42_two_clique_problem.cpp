/*
    QUESTION    : Two Clique Problem (Check if graph can be divided into two cliques)
    Company Tags: Google
    GfG Link    : https://www.geeksforgeeks.org/two-clique-problem-check-if-graph-can-be-divided-into-two-cliques/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V^2) - Complement graph construction + 2-Coloring BFS Bipartite check
// S.C : O(V^2) - Complement adjacency list
class Solution {
private:
    bool isBipartite(int V, const vector<vector<int>>& adj) {
        vector<int> color(V, -1);

        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;

                while (!q.empty()) {
                    int u = q.front();
                    q.pop();

                    for (int v : adj[u]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            return false; // Not bipartite
                        }
                    }
                }
            }
        }

        return true;
    }

public:
    bool canBeDividedInTwoCliques(int V, vector<vector<int>>& graph) {
        // Step 1: Construct the Complement Graph G'
        vector<vector<int>> complementAdj(V);

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j && graph[i][j] == 0) {
                    complementAdj[i].push_back(j);
                }
            }
        }

        // Step 2: A graph can be divided into 2 cliques if and only if its Complement Graph is Bipartite!
        return isBipartite(V, complementAdj);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Property: Graph $G$ can be partitioned into 2 cliques $\iff$ Complement $G'$ is Bipartite!
 * - Build $G'$: edge exists if `graph[i][j] == 0`.
 * - Run 2-Coloring BFS on $G'$.
 * - Time: O(V^2), Space: O(V^2).
 */
