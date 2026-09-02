/*
    QUESTION    : M-Coloring Problem (Graph Coloring with M colors)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/m-coloring-problem-1587115620/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(M^V) - Backtracking exploration of M colors across V vertices
// S.C : O(V)   - Color assignment array
class Solution {
private:
    bool isSafe(int node, int color[], bool graph[101][101], int n, int col) {
        for (int k = 0; k < n; k++) {
            // If adjacent node has the same color
            if (k != node && graph[node][k] == 1 && color[k] == col) {
                return false;
            }
        }
        return true;
    }

    bool solve(int node, int color[], int m, int n, bool graph[101][101]) {
        // Base case: All vertices successfully colored
        if (node == n) return true;

        // Try assigning each color from 1 to m
        for (int c = 1; c <= m; c++) {
            if (isSafe(node, color, graph, n, c)) {
                color[node] = c;

                if (solve(node + 1, color, m, n, graph)) {
                    return true;
                }

                color[node] = 0; // Backtrack
            }
        }

        return false;
    }

public:
    bool graphColoring(bool graph[101][101], int m, int n) {
        int color[101] = {0};
        return solve(0, color, m, n, graph);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Backtracking: try colors $1..m$.
 * - `isSafe`: check no adjacent neighbor shares color `c`.
 * - `color[node] = c; if (solve(node+1)) return true; color[node] = 0;`
 * - Time: O(M^V), Space: O(V).
 */
