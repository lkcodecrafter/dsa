/*
    QUESTION    : Maximum and minimum of an array using minimum number of comparisons
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/maximum-and-minimum-in-an-array/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Pair struct for min and max
struct Pair {
    int min;
    int max;
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Uses pair-wise comparison (Total comparisons = 3 * (N / 2) instead of 2 * N)
// S.C : O(1) - Constant auxiliary space
Pair getMinMax(long long int a[], int n) {
    Pair minmax;
    int i = 0;

    // If array has even elements, initialize min and max with first 2 elements (1 comparison)
    if (n % 2 == 0) {
        if (a[0] > a[1]) {
            minmax.max = a[0];
            minmax.min = a[1];
        } else {
            minmax.min = a[0];
            minmax.max = a[1];
        }
        i = 2;
    } else {
        // If odd, initialize min and max with first element (0 comparisons)
        minmax.min = a[0];
        minmax.max = a[0];
        i = 1;
    }

    // Process elements in pairs (3 comparisons for every 2 elements)
    while (i < n - 1) {
        if (a[i] > a[i + 1]) {
            if (a[i] > minmax.max) minmax.max = a[i];
            if (a[i + 1] < minmax.min) minmax.min = a[i + 1];
        } else {
            if (a[i + 1] > minmax.max) minmax.max = a[i + 1];
            if (a[i] < minmax.min) minmax.min = a[i];
        }
        i += 2;
    }

    return minmax;
}

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Compare elements in pairs: larger against `max`, smaller against `min`.
 * - Requires only $3 \times \lfloor N/2 \rfloor$ total comparisons!
 * - Time: O(N), Space: O(1).
 */
