/*
    QUESTION    : Minimize Cash Flow among a given set of friends who have borrowed money from each other
    Company Tags: Amazon, Google
    GfG Link    : https://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Greedy settlement between maximum creditor and maximum debtor
// S.C : O(N)   - Net balance array
class Solution {
private:
    int getMin(const vector<int>& amount, int n) {
        int minIdx = 0;
        for (int i = 1; i < n; i++) {
            if (amount[i] < amount[minIdx]) minIdx = i;
        }
        return minIdx;
    }

    int getMax(const vector<int>& amount, int n) {
        int maxIdx = 0;
        for (int i = 1; i < n; i++) {
            if (amount[i] > amount[maxIdx]) maxIdx = i;
        }
        return maxIdx;
    }

    void minCashFlowRecur(vector<int>& amount, int n, vector<vector<int>>& resultGraph) {
        int mxCredit = getMax(amount, n);
        int mxDebit = getMin(amount, n);

        // If all amounts are settled to 0
        if (amount[mxCredit] == 0 && amount[mxDebit] == 0) return;

        // Minimum of amount to be paid by max debtor or received by max creditor
        int minAmt = min(-amount[mxDebit], amount[mxCredit]);

        amount[mxCredit] -= minAmt;
        amount[mxDebit] += minAmt;

        resultGraph[mxDebit][mxCredit] = minAmt;

        minCashFlowRecur(amount, n, resultGraph);
    }

public:
    vector<vector<int>> minCashFlow(vector<vector<int>>& graph, int n) {
        vector<int> amount(n, 0);

        // Calculate net balance: (Total incoming - Total outgoing)
        for (int p = 0; p < n; p++) {
            for (int i = 0; i < n; i++) {
                amount[p] += (graph[i][p] - graph[p][i]);
            }
        }

        vector<vector<int>> resultGraph(n, vector<int>(n, 0));
        minCashFlowRecur(amount, n, resultGraph);
        return resultGraph;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Net Balance `amount[p] = incoming - outgoing`.
 * - Find max debtor `mxDebit` and max creditor `mxCredit`.
 * - Settle `min(-amount[mxDebit], amount[mxCredit])` and recurse.
 * - Time: O(N^2), Space: O(N).
 */
