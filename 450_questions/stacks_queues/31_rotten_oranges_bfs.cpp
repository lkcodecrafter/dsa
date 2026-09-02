/*
    QUESTION    : Minimum time required to rot all oranges (Rotten Oranges BFS)
    Company Tags: Amazon, Microsoft, Google, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/rotten-oranges2536/1
    LeetCode    : https://leetcode.com/problems/rotting-oranges/
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(R * C) - Multi-source BFS visits each grid cell once
// S.C : O(R * C) - Queue storing coordinates
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int r = grid.size();
        int c = grid[0].size();

        queue<pair<int, int>> q;
        int freshCount = 0;

        // Step 1: Push all initially rotten oranges into the multi-source BFS queue
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                } else if (grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }

        if (freshCount == 0) return 0;

        int time = 0;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // Step 2: Multi-source BFS level-by-level
        while (!q.empty() && freshCount > 0) {
            int sz = q.size();
            time++;

            for (int k = 0; k < sz; k++) {
                auto curr = q.front();
                q.pop();

                int cr = curr.first;
                int cc = curr.second;

                for (int d = 0; d < 4; d++) {
                    int nr = cr + dr[d];
                    int nc = cc + dc[d];

                    if (nr >= 0 && nr < r && nc >= 0 && nc < c && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2; // Rot the fresh orange
                        freshCount--;
                        q.push({nr, nc});
                    }
                }
            }
        }

        return (freshCount == 0) ? time : -1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Push all initial `grid[i][j] == 2` into `queue`. Count `freshCount`.
 * - While `!q.empty() && freshCount > 0`: expand 4 directions, rot adjacent fresh oranges, `freshCount--`.
 * - Return `(freshCount == 0) ? time : -1`.
 * - Time: O(R * C), Space: O(R * C).
 */
