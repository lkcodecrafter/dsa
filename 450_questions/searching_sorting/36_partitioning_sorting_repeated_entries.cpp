/*
    QUESTION    : 3-Way QuickSort (Partitioning and Sorting Arrays with Many Repeated Entries - Dutch National Flag Partition)
    Company Tags: Google, Amazon
    GfG Link    : https://www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/
    LeetCode    : https://leetcode.com/problems/sort-colors/
*/

#include <iostream>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) average, O(N) when array contains many duplicate keys
// S.C : O(log N) - Recursion call stack
class Solution {
private:
    // 3-way partition (Dutch National Flag) around pivot value
    void partition3Way(int arr[], int l, int r, int &i, int &j) {
        i = l - 1;
        j = r;
        int p = l - 1, q = r;
        int v = arr[r]; // Pivot

        while (true) {
            while (arr[++i] < v);
            while (v < arr[--j]) {
                if (j == l) break;
            }

            if (i >= j) break;

            swap(arr[i], arr[j]);

            if (arr[i] == v) {
                p++;
                swap(arr[p], arr[i]);
            }
            if (arr[j] == v) {
                q--;
                swap(arr[j], arr[q]);
            }
        }

        swap(arr[i], arr[r]);

        j = i - 1;
        for (int k = l; k < p; k++, j--) {
            swap(arr[k], arr[j]);
        }

        i = i + 1;
        for (int k = r - 1; k > q; k--, i++) {
            swap(arr[i], arr[k]);
        }
    }

public:
    void quickSort3Way(int arr[], int l, int r) {
        if (l >= r) return;

        int i, j;
        partition3Way(arr, l, r, i, j);

        quickSort3Way(arr, l, j);
        quickSort3Way(arr, i, r);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - 3-Way QuickSort partitions array into: `< pivot`, `== pivot`, `> pivot`.
 * - Skips entire range `== pivot` in recursive calls, achieving $O(N)$ for duplicate arrays!
 * - Time: O(N log N) / O(N), Space: O(log N).
 */
