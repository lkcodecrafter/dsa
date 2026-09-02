/*
    QUESTION    : Merge Two Sorted Arrays Without Extra Space (Gap Method / Shell Sort Intuition)
    Company Tags: Amazon, Microsoft, Goldman Sachs, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/merge-two-sorted-arrays-1587115620/1
    LeetCode    : https://leetcode.com/problems/merge-sorted-array/
*/

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O((N + M) * log(N + M)) - Gap method compares elements at gap distance
// S.C : O(1)                    - In-place merge without auxiliary memory
class Solution {
private:
    int nextGap(int gap) {
        if (gap <= 1) return 0;
        return (gap / 2) + (gap % 2); // Ceil of gap / 2
    }

public:
    void merge(long long arr1[], long long arr2[], int n, int m) {
        int gap = nextGap(n + m);

        while (gap > 0) {
            int i = 0;
            int j = gap;

            while (j < (n + m)) {
                // Case 1: Both pointers in arr1
                if (j < n) {
                    if (arr1[i] > arr1[j]) {
                        swap(arr1[i], arr1[j]);
                    }
                }
                // Case 2: i in arr1, j in arr2
                else if (i < n && j >= n) {
                    if (arr1[i] > arr2[j - n]) {
                        swap(arr1[i], arr2[j - n]);
                    }
                }
                // Case 3: Both pointers in arr2
                else {
                    if (arr2[i - n] > arr2[j - n]) {
                        swap(arr2[i - n], arr2[j - n]);
                    }
                }

                i++;
                j++;
            }

            gap = nextGap(gap);
        }
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Gap Method: `gap = ceil((n + m) / 2)`.
 * - Compare and swap `arr[i]` and `arr[j]` where `j = i + gap`.
 * - Reduce `gap = ceil(gap / 2)` until `gap == 0`.
 * - Time: O((N + M) log(N + M)), Space: O(1).
 */
