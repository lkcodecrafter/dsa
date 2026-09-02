/*
    QUESTION    : The Celebrity Problem (A celebrity knows no one, and everyone knows the celebrity)
    Company Tags: Amazon, Microsoft, Google, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/the-celebrity-problem/1
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Two-pointer / stack elimination in N steps + 1 verification pass
// S.C : O(1) - Two pointers elimination
class Solution {
public:
    int celebrity(vector<vector<int>>& M, int n) {
        int candidate1 = 0;
        int candidate2 = n - 1;

        // Step 1: Elimination phase using two pointers
        while (candidate1 < candidate2) {
            if (M[candidate1][candidate2] == 1) {
                // candidate1 knows candidate2 -> candidate1 cannot be celebrity
                candidate1++;
            } else {
                // candidate1 does not know candidate2 -> candidate2 cannot be celebrity
                candidate2--;
            }
        }

        int celebCandidate = candidate1;

        // Step 2: Verification phase (Celebrity knows no one; everyone knows celebrity)
        for (int i = 0; i < n; i++) {
            if (i != celebCandidate) {
                // celebCandidate must not know i (M[celebCandidate][i] == 0)
                // AND i must know celebCandidate (M[i][celebCandidate] == 1)
                if (M[celebCandidate][i] == 1 || M[i][celebCandidate] == 0) {
                    return -1; // No celebrity
                }
            }
        }

        return celebCandidate;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF CELEBRITY ELIMINATION
 * ============================================================================
 *
 * Matrix M (3 x 3):
 *   [0, 1, 0]
 *   [0, 0, 0]  <-- Person 1 knows no one!
 *   [0, 1, 0]  <-- Person 0 and Person 2 both know Person 1!
 *
 * Celebrity = 1.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `c1 = 0, c2 = n - 1`.
 * - `while (c1 < c2)`: `if (M[c1][c2] == 1) c1++; else c2--;`
 * - Verify candidate `c`: row `c` all 0s, column `c` all 1s (except `M[c][c]`).
 * - Time: O(N), Space: O(1).
 */
