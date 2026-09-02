/*
    QUESTION    : Maximize sum(arr[i]*i) of an Array
    Company Tags: Amazon, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/maximize-arrii-of-an-array0026/1
*/

#include <iostream>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Rearrangement inequality dictates sorted array maximizes dot product with [0...N-1]
// S.C : O(1)       - In-place sorting
class Solution {
public:
    int Maximize(int a[], int n) {
        sort(a, a + n); // Sort ascending

        long long totalSum = 0;
        long long MOD = 1000000007;

        for (int i = 0; i < n; i++) {
            totalSum = (totalSum + (long long)a[i] * i) % MOD;
        }

        return totalSum;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Rearrangement Inequality: `sort(a)` maximizes $\sum a[i] \times i$.
 * - Time: O(N log N), Space: O(1).
 */
