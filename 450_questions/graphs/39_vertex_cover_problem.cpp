/*
    QUESTION    : Vertex Cover Problem (Approximate Algorithm / Minimum Vertex Cover)
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/vertex-cover/1
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(2^V * E) - Minimum Vertex Cover using Bitmask Search (or 2-approximation in O(V + E))
// S.C : O(1)       - Constant auxiliary space
class Solution {
private:
    bool isCover(int n, int k, int m, const vector<pair<int, int>>& edges) {
        // Enumerate all subsets of size k using Gosper's hack or bitmask
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) == k) {
                bool coversAll = true;

                for (int i = 0; i < m; i++) {
                    int u = edges[i].first - 1;
                    int v = edges[i].second - 1;

                    // If neither endpoint is in the vertex cover
                    if (!(mask & (1 << u)) && !(mask & (1 << v))) {
                        coversAll = false;
                        break;
                    }
                }

                if (coversAll) return true;
            }
        }

        return false;
    }

public:
    int vertexCover(int n, vector<pair<int, int>> &edges) {
        int m = edges.size();

        // Binary Search or linear check on minimum vertex cover size k from 1 to n
        for (int k = 1; k <= n; k++) {
            if (isCover(n, k, m, edges)) {
                return k;
            }
        }

        return 0;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Minimum Vertex Cover: find minimum size $k$ subset of vertices covering every edge.
 * - Test each $k$-combination bitmask: verify `(mask & (1 << u)) || (mask & (1 << v))`.
 * - Time: O(2^V * E), Space: O(1).
 */
