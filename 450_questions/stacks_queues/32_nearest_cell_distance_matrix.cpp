/*
    QUESTION    : Distance of nearest cell having 1 in a binary matrix
    Company Tags: Amazon, Google, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/distance-of-nearest-cell-having-1-1587115620/1
    LeetCode    : https://leetcode.com/problems/01-matrix/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(R * C) - Multi-source BFS computes shortest Manhattan distance to nearest 1
// S.C : O(R * C) - Distance matrix and BFS queue
class Solution {
public:
    vector<vector<int>> nearest(vector<vector<int>> grid) {
        int r = grid.size();
        int c = grid[0].size();

        vector<vector<int>> dist(r, vector<int>(c, -1));
        queue<pair<int, int>> q;

        // Step 1: Push all cells with value 1 into the multi-source BFS queue (dist = 0)
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // Step 2: BFS outward to compute shortest distance
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            int cr = curr.first;
            int cc = curr.second;

            for (int d = 0; d < 4; d++) {
                int nr = cr + dr[d];
                int nc = cc + dc[d];

                // If unvisited cell found
                if (nr >= 0 && nr < r && nc >= 0 && nc < c && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[cr][cc] + 1;
                    q.push({nr, nc});
                }
            }
        }

        return dist;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Seed queue with all cells having `1` (`dist[i][j] = 0`).
 * - BFS level-by-level: `dist[nr][nc] = dist[cr][cc] + 1; q.push({nr, nc});`
 * - Time: O(R * C), Space: O(R * C).
 */
