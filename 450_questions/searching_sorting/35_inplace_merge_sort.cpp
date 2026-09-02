/*
    QUESTION    : In-Place Merge Sort
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/in-place-merge-sort/
*/

#include <iostream>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log^2 N) using Gap method or O(N^2) using shifting
// S.C : O(1)          - Strictly in-place pointer/index arithmetic without extra array
class Solution {
private:
    int nextGap(int gap) {
        if (gap <= 1) return 0;
        return (gap / 2) + (gap % 2);
    }

    void inPlaceMerge(int arr[], int start, int mid, int end) {
        int gap = nextGap(end - start + 1);

        while (gap > 0) {
            for (int i = start; i + gap <= end; i++) {
                int j = i + gap;
                if (arr[i] > arr[j]) {
                    swap(arr[i], arr[j]);
                }
            }
            gap = nextGap(gap);
        }
    }

public:
    void mergeSortInPlace(int arr[], int l, int r) {
        if (l < r) {
            int mid = l + (r - l) / 2;
            mergeSortInPlace(arr, l, mid);
            mergeSortInPlace(arr, mid + 1, r);
            inPlaceMerge(arr, l, mid, r);
        }
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Uses Gap method during merge step to sort subarrays strictly in-place.
 * - Time: O(N log^2 N), Space: O(1).
 */
