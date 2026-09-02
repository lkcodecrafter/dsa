/*
    QUESTION    : Floyd Warshall Algorithm (All-Pairs Shortest Path)
    Company Tags: Amazon, Microsoft, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V^3) - Triple nested loop considering each vertex k as intermediate node
// S.C : O(1)   - In-place matrix update
class Solution {
public:
    void shortest_distance(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // Convert -1 to large value for calculation
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == -1) {
                    matrix[i][j] = 1e9;
                }
                if (i == j) matrix[i][j] = 0;
            }
        }

        // Floyd-Warshall core: k represents intermediate vertex
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (matrix[i][k] != 1e9 && matrix[k][j] != 1e9) {
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
                }
            }
        }

        // Convert unreachable values back to -1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] >= 1e9) {
                    matrix[i][j] = -1;
                }
            }
        }
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `for k: for i: for j:`
 * - `matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j])`.
 * - Time: O(V^3), Space: O(1) auxiliary.
 */
