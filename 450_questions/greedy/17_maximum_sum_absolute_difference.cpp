/*
    QUESTION    : Maximum sum of absolute difference of any permutation
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/maximum-sum-absolute-difference-array/
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting + Interleaving smallest and largest elements
// S.C : O(N)       - Rearranged vector
class Solution {
public:
    long long MaxSumDifference(int a[], int n) {
        sort(a, a + n);

        vector<int> sequence;
        int i = 0, j = n - 1;

        // Interleave smallest and largest elements
        while (i <= j) {
            if (i == j) {
                sequence.push_back(a[i]);
                break;
            }
            sequence.push_back(a[i++]);
            sequence.push_back(a[j--]);
        }

        // Calculate circular absolute difference sum
        long long sum = 0;
        for (int k = 0; k < n; k++) {
            sum += abs(sequence[k] - sequence[(k + 1) % n]);
        }

        return sum;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(a)`. Interleave from opposite ends: `a[0], a[n-1], a[1], a[n-2]...`.
 * - Compute circular sum of `abs(seq[k] - seq[k+1])`.
 * - Time: O(N log N), Space: O(N).
 */
