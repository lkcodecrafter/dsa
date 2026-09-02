/*
    QUESTION    : Search a Word in a 2D Grid of characters (All 8 directions)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/find-the-string-in-grid0111/1
    LeetCode    : https://leetcode.com/problems/word-search/
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(R * C * 8 * L) - Search along straight rays in 8 directions
// S.C : O(1)             - Direction vectors
class Solution {
private:
    int dr[8] = {-1, -1, -1,  0, 0,  1, 1, 1};
    int dc[8] = {-1,  0,  1, -1, 1, -1, 0, 1};

    bool search2D(const vector<vector<char>>& grid, int row, int col, const string& word) {
        int r = grid.size();
        int c = grid[0].size();
        int len = word.length();

        if (grid[row][col] != word[0]) return false;

        // Search in all 8 straight directions
        for (int dir = 0; dir < 8; dir++) {
            int k, rd = row + dr[dir], cd = col + dc[dir];

            for (k = 1; k < len; k++) {
                if (rd < 0 || rd >= r || cd < 0 || cd >= c || grid[rd][cd] != word[k]) {
                    break;
                }
                rd += dr[dir];
                cd += dc[dir];
            }

            if (k == len) return true; // Found matching straight ray
        }

        return false;
    }

public:
    vector<vector<int>> searchWord(vector<vector<char>> grid, string word) {
        vector<vector<int>> result;
        int r = grid.size();
        int c = grid[0].size();

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (search2D(grid, i, j, word)) {
                    result.push_back({i, j});
                }
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - 8 directional vectors `dr[8], dc[8]`.
 * - Verify contiguous straight-line match for all `L` characters.
 * - Time: O(R * C * 8 * L), Space: O(1).
 */
