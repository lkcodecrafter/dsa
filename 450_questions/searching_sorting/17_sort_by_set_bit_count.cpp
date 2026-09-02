/*
    QUESTION    : Sort array according to count of set bits (Stable Sort)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/sort-by-set-bit-count1153/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Stable sort by __builtin_popcount
// S.C : O(N)       - std::stable_sort auxiliary space
class Solution {
public:
    void sortBySetBitCount(int arr[], int n) {
        // Stable sort preserves original relative order when set bit counts are equal
        stable_sort(arr, arr + n, [](int a, int b) {
            return __builtin_popcount(a) > __builtin_popcount(b);
        });
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `std::stable_sort` with `__builtin_popcount(a) > __builtin_popcount(b)`.
 * - Time: O(N log N), Space: O(N).
 */
