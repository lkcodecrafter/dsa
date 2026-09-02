/*
    QUESTION    : Minimum Cost to cut a board into squares (Chocolate Distribution / Board Cutting)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-cost-to-cut-a-board-into-squares/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(M log M + N log N) - Sorting cut costs descending + greedy cut selection
// S.C : O(1)                - Constant auxiliary space
class Solution {
public:
    int minimumCostOfBreaking(vector<int> X, vector<int> Y, int M, int N) {
        // Sort cut costs descending so expensive cuts are made early with fewer segment multiplications
        sort(X.rbegin(), X.rend());
        sort(Y.rbegin(), Y.rend());

        int horizontalPieces = 1;
        int verticalPieces = 1;

        int i = 0, j = 0;
        int totalCost = 0;

        while (i < X.size() && j < Y.size()) {
            if (X[i] >= Y[j]) {
                totalCost += X[i] * verticalPieces;
                horizontalPieces++;
                i++;
            } else {
                totalCost += Y[j] * horizontalPieces;
                verticalPieces++;
                j++;
            }
        }

        // Add remaining cuts
        while (i < X.size()) {
            totalCost += X[i] * verticalPieces;
            i++;
        }

        while (j < Y.size()) {
            totalCost += Y[j] * horizontalPieces;
            j++;
        }

        return totalCost;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Sort cuts descending.
 * - Greedily pick largest cut:
 *     - If vertical: `cost += X[i] * verticalPieces; horizontalPieces++;`
 *     - If horizontal: `cost += Y[j] * horizontalPieces; verticalPieces++;`
 * - Time: O(M log M + N log N), Space: O(1).
 */
