/*
 * QUESTION: m Coloring Problem
 * Link: https://practice.geeksforgeeks.org/problems/m-coloring-problem/0
 * 
 * Input: graph adjacency matrix, m (colors), V (vertices)
 * Output: True (If coloring possible)
 */

#include <iostream>
#include <vector>

// Checks if it is safe to assign color `c` to vertex `v`.
bool isColorSafe(int v, const std::vector<std::vector<bool>>& graph, const std::vector<int>& color, int c, int V) {
    for (int i = 0; i < V; i++) {
        // If there is an edge and the adjacent vertex has the same color
        if (graph[v][i] && c == color[i]) {
            return false;
        }
    }
    return true;
}

// Helper backtracking function to color the vertices of the graph starting from vertex v
bool graphColoringHelper(int v, const std::vector<std::vector<bool>>& graph, std::vector<int>& color, int m, int V) {
    // Base Case: All vertices are colored successfully
    if (v == V) {
        return true;
    }
    
    // Try coloring vertex `v` with colors 1 to m
    for (int c = 1; c <= m; c++) {
        if (isColorSafe(v, graph, color, c, V)) {
            color[v] = c; // Assign color
            
            // Recurse to color the next vertex
            if (graphColoringHelper(v + 1, graph, color, m, V)) {
                return true;
            }
            
            // Backtrack: Reset color assignment
            color[v] = 0;
        }
    }
    
    return false;
}

// Wrapper function to determine if graph can be colored with at most m colors
bool graphColoring(const std::vector<std::vector<bool>>& graph, int m, int V) {
    std::vector<int> color(V, 0); // 0 indicates no color assigned
    return graphColoringHelper(0, graph, color, m, V);
}

/*
 * DRY RUN (V = 3, m = 2, graph is a triangle K3):
 * graph = {{0, 1, 1},
 *          {1, 0, 1},
 *          {1, 1, 0}}
 * m = 2, color array: {0, 0, 0}
 * 
 * | Step | Vertex v | Tried Color c | Adjacent Checks | Safe? | Action                                      | color State |
 * | :--- | :------- | :------------ | :-------------- | :---- | :------------------------------------------ | :---------- |
 * | Init | 0        | -             | -               | -     | Start coloring                              | {0, 0, 0}   |
 * | 1    | 0        | 1             | None (all 0)    | Yes   | Assign color[0]=1; recurse at v=1           | {1, 0, 0}   |
 * | 2    | 1        | 1             | Neighbor 0 (1)  | No    | Same color; try next                        | {1, 0, 0}   |
 * | 3    | 1        | 2             | Neighbor 0 (1)  | Yes   | Assign color[1]=2; recurse at v=2           | {1, 2, 0}   |
 * | 4    | 2        | 1             | Neighbor 0 (1)  | No    | Same color; try next                        | {1, 2, 0}   |
 * | 5    | 2        | 2             | Neighbor 1 (2)  | No    | Same color; try next                        | {1, 2, 0}   |
 * | 6    | 2        | -             | (colors exhausted)| -   | Backtrack -> undo color[1]                  | {1, 0, 0}   |
 * 
 * Triangle K3 cannot be colored with m = 2 colors, so returns false.
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine drawing a map of states. 
 * You pick a state, paint it color `c`, ensuring its neighbors aren't already color `c`. 
 * If they are, you choose another paint can. 
 * If you run out of paint cans, you go back to the previous state, repaint it, and try again.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Initialize color array of size `V` with `0`s.
 * - For vertex `v` from `0` to `V - 1`:
 *   - Try colors `c` from `1` to `m`.
 *   - Check adjacency: if `graph[v][i] == true` and `color[i] == c`, color `c` is invalid.
 *   - If valid, assign color `c` to `v` and recurse on `v + 1`.
 *   - Backtrack by setting `color[v] = 0` if sub-calls fail.
 * - Return `true` if `v == V`.
 * - Time Complexity: O(M^V) worst case.
 * - Space Complexity: O(V) stack depth.
 */
