/*
 * QUESTION: Find if there is a path of more than k length from a source
 * Link: https://www.geeksforgeeks.org/find-if-there-is-a-path-of-more-than-k-length-from-a-source/
 * 
 * Input: Graph adjacency list, source src, K
 * Output: True (If simple path of length > K exists)
 */

#include <iostream>
#include <vector>
#include <utility>

// Helper DFS backtracking function to find a path of length > k
bool pathMoreThanKHelper(int u, int k, const std::vector<std::vector<std::pair<int, int>>>& adj,
                         std::vector<bool>& visited) {
    // Base Case: Remaining target distance k is reached or exceeded
    if (k <= 0) {
        return true;
    }
    
    // Check all adjacent vertices of u
    for (auto const& edge : adj[u]) {
        int v = edge.first;     // Adjacent vertex
        int w = edge.second;    // Edge weight
        
        // Check to avoid cycles (simple path constraint)
        if (!visited[v]) {
            visited[v] = true; // Mark as visited
            
            // Recurse with updated target distance
            if (pathMoreThanKHelper(v, k - w, adj, visited)) {
                return true;
            }
            
            visited[v] = false; // Backtrack: mark unvisited
        }
    }
    
    return false;
}

// Wrapper function to initialize tracking variables
bool pathMoreThanK(int src, int k, int V, const std::vector<std::vector<std::pair<int, int>>>& adj) {
    std::vector<bool> visited(V, false);
    
    // Mark source vertex as visited
    visited[src] = true;
    
    return pathMoreThanKHelper(src, k, adj, visited);
}

/*
 * VISUALIZATION OF GRAPH:
 * (0) --(4)--> (1) --(8)--> (2)
 *  |           |
 * (8)         (11)
 *  v           v
 * (7) --(1)--> (6)
 * 
 * DRY RUN (src = 0, k = 14, V = 3):
 * Edges: 0-1 (w=4), 1-2 (w=12)
 * adj[0] = {(1, 4)}, adj[1] = {(0, 4), (2, 12)}, adj[2] = {(1, 12)}
 * Initial visited: {T, F, F} (source 0 visited), target k = 14
 * 
 * | Step | Current u | target k | Neighbor v | Edge weight w | Visited State | Condition (k - w <= 0) | Action                                    |
 * | :--- | :-------- | :------- | :--------- | :------------ | :------------ | :--------------------- | :---------------------------------------- |
 * | Init | 0         | 14       | -          | -             | {T, F, F}     | -                      | Start DFS from 0                          |
 * | 1    | 0         | 14       | 1          | 4             | {T, T, F}     | 14 - 4 = 10 > 0        | Recurse at u=1, k=10                      |
 * | 2    | 1         | 10       | 0          | 4             | -             | 0 is visited           | Skip                                      |
 * | 3    | 1         | 10       | 2          | 12            | {T, T, T}     | 10 - 12 = -2 <= 0      | Recurse at u=2, k=-2. Base Case matches!  |
 * | 4    | 2         | -2       | -          | -             | {T, T, T}     | Target reached         | Return true                               |
 * 
 * Result: true (Path 0 -> 1 -> 2 has total length 16 > 14)
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine hiking with a minimum mileage goal of `K` miles. 
 * You start at a trailhead `src`. 
 * You hike down a trail to an intersection `v`. 
 * To avoid getting lost, you mark intersections you've visited on your map (`visited`). 
 * Subtract the trail length `w` from your goal. 
 * If you still haven't met your goal, you continue walking. 
 * If you get stuck at a dead-end, you hike back (backtrack) to try a different fork in the road.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Use standard DFS with backtracking.
 * - Set source vertex `visited[src] = true`.
 * - In recursion `pathMoreThanKHelper(u, k, adj, visited)`:
 *   - If `k <= 0`, return `true` (success).
 *   - For each unvisited neighbor `v` of `u` with weight `w`:
 *     - Set `visited[v] = true`.
 *     - Recurse `pathMoreThanKHelper(v, k - w, adj, visited)`. If `true`, propagate `true`.
 *     - Otherwise, backtrack `visited[v] = false`.
 *   - Return `false` if all paths from `u` fail.
 * - Time Complexity: O(V!) in the worst case (exploring all simple paths).
 * - Space Complexity: O(V) stack space.
 */
