/*
    QUESTION    : CHOCOLA - Chocolate (SPOJ)
    Company Tags: Google
    Link        : https://www.spoj.com/problems/CHOCOLA/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(M log M + N log N) - Sorting cut costs descending + greedy selection
// S.C : O(1)                - Constant auxiliary space
class Solution {
public:
    int minChocolateBreakCost(vector<int>& X, vector<int>& Y) {
        sort(X.rbegin(), X.rend());
        sort(Y.rbegin(), Y.rend());

        int hPieces = 1, vPieces = 1;
        int i = 0, j = 0;
        int totalCost = 0;

        while (i < X.size() && j < Y.size()) {
            if (X[i] >= Y[j]) {
                totalCost += X[i] * vPieces;
                hPieces++;
                i++;
            } else {
                totalCost += Y[j] * hPieces;
                vPieces++;
                j++;
            }
        }

        while (i < X.size()) {
            totalCost += X[i++] * vPieces;
        }

        while (j < Y.size()) {
            totalCost += Y[j++] * hPieces;
        }

        return totalCost;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Exact same optimal greedy strategy as board cutting: sort cuts descending.
 * - Time: O(M log M + N log N), Space: O(1).
 */
