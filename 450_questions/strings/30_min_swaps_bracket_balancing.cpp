/*
    QUESTION    : Minimum Swaps for Bracket Balancing
    Company Tags: Amazon, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-swaps-for-bracket-balancing2704/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear greedy bracket balance swap counter
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int minimumNumberOfSwaps(string S) {
        int countOpen = 0;
        int countClose = 0;
        int imbalance = 0;
        int totalSwaps = 0;

        for (char ch : S) {
            if (ch == '[') {
                countOpen++;
                if (imbalance > 0) {
                    totalSwaps += imbalance; // Swapping brings open bracket forward
                    imbalance--;
                }
            } else {
                countClose++;
                imbalance = countClose - countOpen;
            }
        }

        return totalSwaps;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If `[`: `countOpen++; if (imbalance > 0) { totalSwaps += imbalance; imbalance--; }`
 * - If `]`: `countClose++; imbalance = countClose - countOpen;`
 * - Time: O(N), Space: O(1).
 */
