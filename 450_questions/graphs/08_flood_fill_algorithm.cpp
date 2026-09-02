/*
    QUESTION    : Flood Fill Algorithm
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/flood-fill-algorithm1856/1
    LeetCode    : https://leetcode.com/problems/flood-fill/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(R * C) - DFS replaces connected component with new color
// S.C : O(R * C) - Recursion stack space
class Solution {
private:
    void dfs(int r, int c, vector<vector<int>>& image, int oldColor, int newColor) {
        if (r < 0 || r >= image.size() || c < 0 || c >= image[0].size() || image[r][c] != oldColor) {
            return;
        }

        image[r][c] = newColor;

        dfs(r + 1, c, image, oldColor, newColor);
        dfs(r - 1, c, image, oldColor, newColor);
        dfs(r, c + 1, image, oldColor, newColor);
        dfs(r, c - 1, image, oldColor, newColor);
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int oldColor = image[sr][sc];
        if (oldColor != newColor) {
            dfs(sr, sc, image, oldColor, newColor);
        }
        return image;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `image[sr][sc] == newColor`, return.
 * - DFS 4 directions changing `oldColor` to `newColor`.
 * - Time: O(R * C), Space: O(R * C).
 */
