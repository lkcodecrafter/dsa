/*
    QUESTION    : GCJ101BB - Picking Up Chicks (SPOJ / Google Code Jam)
    Company Tags: Google
    Link        : https://www.spoj.com/problems/GCJ101BB/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Right-to-left scan counting slower blocking chicks
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int minSwapsForChicks(int N, int K, int B, int T, const vector<int>& X, const vector<int>& V) {
        int chicksReached = 0;
        int swaps = 0;
        int slowChicksBlocking = 0;

        // Traverse chicks from right to left (closest to barn B first)
        for (int i = N - 1; i >= 0; i--) {
            // Distance chick can travel in T seconds = V[i] * T
            // Final position = X[i] + V[i] * T
            if (X[i] + (long long)V[i] * T >= B) {
                chicksReached++;
                swaps += slowChicksBlocking; // Must swap past all slower chicks in front
                if (chicksReached == K) {
                    return swaps;
                }
            } else {
                slowChicksBlocking++; // This chick cannot reach barn; blocks faster chicks behind it
            }
        }

        return -1; // Not enough chicks can reach barn B
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Scan right-to-left.
 * - If `X[i] + V[i]*T >= B`: `reached++; swaps += blocking;`
 * - Else: `blocking++;`
 * - Time: O(N), Space: O(1).
 */
