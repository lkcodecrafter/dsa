/*
    QUESTION    : Steps by Knight (Minimum steps to reach target position)
    Company Tags: Amazon, Microsoft, Directi
    GfG Link    : https://practice.geeksforgeeks.org/problems/steps-by-knight5927/1
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - BFS on N x N chessboard
// S.C : O(N^2) - Visited array and queue
class Solution {
public:
    int minStepToReachTarget(vector<int>& KnightPos, vector<int>& TargetPos, int N) {
        // 1-based indexing to 0-based indexing
        int sr = KnightPos[0] - 1, sc = KnightPos[1] - 1;
        int tr = TargetPos[0] - 1, tc = TargetPos[1] - 1;

        if (sr == tr && sc == tc) return 0;

        int dr[8] = {-2, -2, -1, -1,  1,  1,  2,  2};
        int dc[8] = {-1,  1, -2,  2, -2,  2, -1,  1};

        vector<vector<bool>> visited(N, vector<bool>(N, false));
        queue<pair<int, int>> q;

        q.push({sr, sc});
        visited[sr][sc] = true;

        int steps = 0;

        while (!q.empty()) {
            int sz = q.size();
            steps++;

            for (int k = 0; k < sz; k++) {
                auto curr = q.front();
                q.pop();

                for (int d = 0; d < 8; d++) {
                    int nr = curr.first + dr[d];
                    int nc = curr.second + dc[d];

                    if (nr >= 0 && nr < N && nc >= 0 && nc < N && !visited[nr][nc]) {
                        if (nr == tr && nc == tc) {
                            return steps;
                        }
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
        }

        return -1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - 8 Knight moves: `dr[8]`, `dc[8]`.
 * - Level-by-level BFS from `KnightPos` until `TargetPos` is reached.
 * - Time: O(N^2), Space: O(N^2).
 */
