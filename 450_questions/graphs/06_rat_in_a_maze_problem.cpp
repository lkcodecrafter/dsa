/*
    QUESTION    : Rat in a Maze Problem - I
    Company Tags: Amazon, Microsoft, Expedia
    GfG Link    : https://practice.geeksforgeeks.org/problems/rat-in-a-maze-problem/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(4^(N^2)) - Backtracking exploration in Lexicographical direction order 'D', 'L', 'R', 'U'
// S.C : O(N^2)     - Recursion stack depth
class Solution {
private:
    int dr[4] = {1, 0, 0, -1};
    int dc[4] = {0, -1, 1, 0};
    char dir[4] = {'D', 'L', 'R', 'U'};

    void solve(int r, int c, vector<vector<int>>& m, int n, string& path, vector<string>& result) {
        // Base case: Reached bottom-right destination
        if (r == n - 1 && c == n - 1) {
            result.push_back(path);
            return;
        }

        m[r][c] = 0; // Mark visited

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < n && m[nr][nc] == 1) {
                path.push_back(dir[i]);
                solve(nr, nc, m, n, path, result);
                path.pop_back(); // Backtrack
            }
        }

        m[r][c] = 1; // Unmark visited (Backtrack)
    }

public:
    vector<string> findPath(vector<vector<int>> &m, int n) {
        vector<string> result;
        if (m[0][0] == 0 || m[n - 1][n - 1] == 0) return result;

        string path = "";
        solve(0, 0, m, n, path, result);
        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Explore 'D', 'L', 'R', 'U' (Lexicographical).
 * - Mark `m[r][c] = 0`, recurse, unmark `m[r][c] = 1`.
 * - Time: O(4^(N^2)), Space: O(N^2).
 */
