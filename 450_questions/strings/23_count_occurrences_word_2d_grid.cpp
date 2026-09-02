/*
    QUESTION    : Count of number of given string in 2D character array
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/find-count-number-given-string-present-2d-character-array/
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(R * C * 4^L) - Backtracking in 4 directions
// S.C : O(L)           - Recursion stack depth
class Solution {
private:
    int dfs(int r, int c, const vector<vector<char>>& mat, const string& target, int idx) {
        if (idx == target.length()) return 1;

        if (r < 0 || r >= mat.size() || c < 0 || c >= mat[0].size() || mat[r][c] != target[idx]) {
            return 0;
        }

        // Matched character
        if (idx == target.length() - 1) return 1;

        int found = 0;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int d = 0; d < 4; d++) {
            found += dfs(r + dr[d], c + dc[d], mat, target, idx + 1);
        }

        return found;
    }

public:
    int findOccurrence(vector<vector<char>>& mat, string target) {
        int count = 0;
        int rows = mat.size();
        int cols = mat[0].size();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (mat[i][j] == target[0]) {
                    count += dfs(i, j, mat, target, 0);
                }
            }
        }

        return count;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - DFS from each matching start character across 4 orthogonal directions.
 * - Time: O(R * C * 4^L), Space: O(L).
 */
