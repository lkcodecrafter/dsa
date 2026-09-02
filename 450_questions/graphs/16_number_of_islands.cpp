/*
    QUESTION    : Find the number of islands (8-directionally connected components)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/find-the-number-of-islands/1
    LeetCode    : https://leetcode.com/problems/number-of-islands/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(R * C) - DFS visits each grid cell and sinks connected islands
// S.C : O(R * C) - Recursion call stack
class Solution {
private:
    void dfs(int r, int c, vector<vector<char>>& grid) {
        if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() || grid[r][c] != '1') {
            return;
        }

        grid[r][c] = '0'; // Sink current island cell

        // Traverse all 8 directions
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr != 0 || dc != 0) {
                    dfs(r + dr, c + dc, grid);
                }
            }
        }
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        int r = grid.size();
        int c = grid[0].size();
        int islandCount = 0;

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (grid[i][j] == '1') {
                    islandCount++;
                    dfs(i, j, grid);
                }
            }
        }

        return islandCount;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `grid[i][j] == '1'`: `islandCount++; dfs(i, j)`.
 * - DFS sinks 8 connected land cells to `'0'`.
 * - Time: O(R * C), Space: O(R * C).
 */
