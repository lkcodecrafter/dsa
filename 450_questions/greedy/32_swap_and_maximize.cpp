/*
    QUESTION    : Swap and Maximize (Maximize sum of difference between adjacent elements of circular array)
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/swap-and-maximize5859/1
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Sorting + Interleaving smallest and largest elements
// S.C : O(N)       - Interleaved sequence array
long long int maxSum(int arr[], int n) {
    sort(arr, arr + n);

    vector<int> seq;
    int i = 0, j = n - 1;

    while (i <= j) {
        if (i == j) {
            seq.push_back(arr[i]);
            break;
        }
        seq.push_back(arr[i++]);
        seq.push_back(arr[j--]);
    }

    long long sum = 0;
    for (int k = 0; k < n; k++) {
        sum += abs(seq[k] - seq[(k + 1) % n]);
    }

    return sum;
}

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(arr)`. Interleave smallest and largest: `arr[0], arr[n-1], arr[1], arr[n-2]...`.
 * - Compute circular sum `abs(seq[i] - seq[(i+1)%n])`.
 * - Time: O(N log N), Space: O(N).
 */
