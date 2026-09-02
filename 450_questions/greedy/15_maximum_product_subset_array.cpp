/*
    QUESTION    : Maximum product subset of an array
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximum-product-subset-of-an-array/1
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear pass tracking count of negatives, zeros, and largest negative
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    long long int findMaxProduct(vector<int>& a, int n) {
        if (n == 1) return a[0];

        long long MOD = 1000000007;
        int maxNegative = INT_MIN;
        int countNeg = 0;
        int countZero = 0;
        long long prod = 1;

        for (int i = 0; i < n; i++) {
            if (a[i] == 0) {
                countZero++;
                continue;
            }

            if (a[i] < 0) {
                countNeg++;
                maxNegative = max(maxNegative, a[i]);
            }

            prod = (prod * a[i]) % MOD;
        }

        // Case 1: All elements are zeros
        if (countZero == n) return 0;

        // Case 2: Only one negative element and rest are zeros
        if (countNeg == 1 && countZero + countNeg == n) return 0;

        // Case 3: Odd number of negative elements -> divide by maxNegative to make product positive
        if (countNeg % 2 != 0) {
            // Note: Since prod was computed modulo MOD, division requires standard arithmetic or excluding maxNeg during pass
            prod = 1;
            bool excluded = false;
            for (int i = 0; i < n; i++) {
                if (a[i] == 0) continue;
                if (a[i] == maxNegative && !excluded) {
                    excluded = true;
                    continue; // Skip the single least negative element
                }
                prod = (prod * a[i]) % MOD;
            }
        }

        return (prod + MOD) % MOD;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If odd negatives: exclude `maxNegative` (closest to 0).
 * - If only 1 negative and rest zeros: return 0.
 * - Multiply all non-zero elements modulo $10^9 + 7$.
 * - Time: O(N), Space: O(1).
 */
