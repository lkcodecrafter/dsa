/*
    QUESTION    : Searching in an array where adjacent differ by at most k
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/searching-array-adjacent-differ-k/
*/

#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) worst case, much faster than linear search on average
// S.C : O(1) - Step jump technique
int search(int arr[], int n, int x, int k) {
    int i = 0;

    while (i < n) {
        if (arr[i] == x) {
            return i; // Found
        }

        // Jump at least max(1, abs(arr[i] - x) / k) steps forward
        int step = max(1, abs(arr[i] - x) / k);
        i += step;
    }

    return -1;
}

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `step = max(1, abs(arr[i] - x) / k)`.
 * - Jump `i += step`.
 * - Time: O(N) worst, O(N/k) avg. Space: O(1).
 */
