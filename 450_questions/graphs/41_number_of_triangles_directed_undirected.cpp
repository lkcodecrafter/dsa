/*
    QUESTION    : Number of Triangles in Directed and Undirected Graphs
    Company Tags: Google
    GfG Link    : https://www.geeksforgeeks.org/number-of-triangles-in-directed-and-undirected-graphs/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V^3) - Triple nested loop testing triangle paths i -> j -> k -> i
// S.C : O(V^2) - Adjacency matrix
class Solution {
public:
    int countTriangles(vector<vector<int>>& graph, bool isDirected) {
        int V = graph.size();
        int count = 0;

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                for (int k = 0; k < V; k++) {
                    // Check if cycle of length 3 exists: i -> j -> k -> i
                    if (graph[i][j] && graph[j][k] && graph[k][i]) {
                        count++;
                    }
                }
            }
        }

        // For directed graph, each directed triangle is counted 3 times (1 per vertex)
        // For undirected graph, each triangle is counted 6 times (3 vertices * 2 orientations)
        return isDirected ? (count / 3) : (count / 6);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Count triplets with `graph[i][j] && graph[j][k] && graph[k][i]`.
 * - Directed: `count / 3`; Undirected: `count / 6`.
 * - Time: O(V^3), Space: O(1).
 */
