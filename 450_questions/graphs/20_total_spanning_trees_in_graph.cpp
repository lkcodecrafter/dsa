/*
    QUESTION    : Total number of Spanning Trees in a Graph (Kirchhoff's Matrix Tree Theorem)
    Company Tags: Google, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/total-number-spanning-trees-graph/
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(V^3) - Kirchhoff's Theorem: Determinant of (V-1) x (V-1) Laplacian cofactor matrix
// S.C : O(V^2) - Laplacian matrix
class Solution {
private:
    // Gaussian elimination determinant calculation
    int determinantOfMatrix(vector<vector<int>> mat, int n) {
        double det = 1.0;

        for (int i = 0; i < n; i++) {
            int pivot = i;
            for (int j = i + 1; j < n; j++) {
                if (abs(mat[j][i]) > abs(mat[pivot][i])) {
                    pivot = j;
                }
            }

            if (pivot != i) {
                swap(mat[i], mat[pivot]);
                det = -det;
            }

            if (abs(mat[i][i]) == 0) return 0;

            det *= mat[i][i];

            for (int j = i + 1; j < n; j++) {
                double factor = (double)mat[j][i] / mat[i][i];
                for (int k = i + 1; k < n; k++) {
                    mat[j][k] -= factor * mat[i][k];
                }
            }
        }

        return round(abs(det));
    }

public:
    int countSpanningTrees(vector<vector<int>>& graph, int V) {
        // Step 1: Compute Degree Matrix D and Adjacency Matrix A -> Laplacian L = D - A
        vector<vector<int>> laplacian(V, vector<int>(V, 0));

        for (int i = 0; i < V; i++) {
            int deg = 0;
            for (int j = 0; j < V; j++) {
                if (graph[i][j] == 1 && i != j) {
                    deg++;
                    laplacian[i][j] = -1;
                }
            }
            laplacian[i][i] = deg;
        }

        // Step 2: Extract (V-1) x (V-1) cofactor submatrix
        vector<vector<int>> submatrix(V - 1, vector<int>(V - 1));
        for (int i = 1; i < V; i++) {
            for (int j = 1; j < V; j++) {
                submatrix[i - 1][j - 1] = laplacian[i][j];
            }
        }

        // Step 3: Return determinant of cofactor
        return determinantOfMatrix(submatrix, V - 1);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Kirchhoff's Theorem: Total Spanning Trees = $\det(\text{Cofactor of Laplacian } L)$.
 * - $L = D - A$ where $D$ is degree matrix, $A$ is adjacency matrix.
 * - Time: O(V^3), Space: O(V^2).
 */
