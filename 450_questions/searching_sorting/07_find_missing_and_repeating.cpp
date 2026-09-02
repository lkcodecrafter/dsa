/*
    QUESTION    : Find Missing And Repeating
    Company Tags: Amazon, Microsoft, Samsung, Goldman Sachs
    GfG Link    : https://practice.geeksforgeeks.org/problems/find-missing-and-repeating2512/1
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - In-place array negation marks visited indices
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    vector<int> findTwoElement(vector<int> arr, int n) {
        int repeating = -1;
        int missing = -1;

        // Step 1: Find repeating element by negating visited indices
        for (int i = 0; i < n; i++) {
            int val = abs(arr[i]);
            if (arr[val - 1] < 0) {
                repeating = val; // Already visited!
            } else {
                arr[val - 1] = -arr[val - 1];
            }
        }

        // Step 2: The positive index corresponds to the missing number
        for (int i = 0; i < n; i++) {
            if (arr[i] > 0) {
                missing = i + 1;
                break;
            }
        }

        return {repeating, missing};
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Negate value at `arr[abs(arr[i]) - 1]`.
 * - If already negative $\rightarrow$ repeating.
 * - Index that remains positive $+ 1$ $\rightarrow$ missing.
 * - Time: O(N), Space: O(1).
 */
