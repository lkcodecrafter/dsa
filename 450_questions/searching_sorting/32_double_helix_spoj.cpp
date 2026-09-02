/*
    QUESTION    : ANARC05B - The Double Helix (SPOJ)
    Company Tags: Google
    Link        : https://www.spoj.com/problems/ANARC05B/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N + M) - Two-pointer linear sweep accumulating maximum sum between intersection bridge points
// S.C : O(1)     - Constant auxiliary space
class Solution {
public:
    int maxPathSum(const vector<int>& a, const vector<int>& b) {
        int n = a.size();
        int m = b.size();

        int i = 0, j = 0;
        int sumA = 0, sumB = 0;
        int totalMaxSum = 0;

        while (i < n && j < m) {
            if (a[i] < b[j]) {
                sumA += a[i++];
            } else if (b[j] < a[i]) {
                sumB += b[j++];
            } else {
                // Intersection bridge point encountered!
                // Greedily pick the maximum sum path leading up to this bridge
                totalMaxSum += max(sumA, sumB) + a[i];
                sumA = 0;
                sumB = 0;
                i++;
                j++;
            }
        }

        // Add trailing elements
        while (i < n) sumA += a[i++];
        while (j < m) sumB += b[j++];

        totalMaxSum += max(sumA, sumB);

        return totalMaxSum;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Accumulate `sumA` and `sumB`.
 * - At bridge point (`a[i] == b[j]`): `totalMaxSum += max(sumA, sumB) + a[i]; sumA = 0; sumB = 0;`
 * - Time: O(N + M), Space: O(1).
 */
