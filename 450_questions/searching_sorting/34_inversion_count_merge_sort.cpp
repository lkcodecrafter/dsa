/*
    QUESTION    : Count Inversions (Inversion Count of an Array)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/inversion-of-array-1587115620/1
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Modified Merge Sort counts cross inversions during merge
// S.C : O(N)       - Auxiliary array for merge
class Solution {
private:
    long long merge(long long arr[], long long temp[], int left, int mid, int right) {
        int i = left;    // Left subarray pointer
        int j = mid + 1; // Right subarray pointer
        int k = left;    // Temp array pointer
        long long invCount = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
                // Since left subarray is sorted, arr[i] > arr[j] implies all elements from i to mid are > arr[j]!
                invCount += (mid - i + 1);
            }
        }

        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];

        for (i = left; i <= right; i++) {
            arr[i] = temp[i];
        }

        return invCount;
    }

    long long mergeSortAndCount(long long arr[], long long temp[], int left, int right) {
        long long invCount = 0;
        if (left < right) {
            int mid = left + (right - left) / 2;

            invCount += mergeSortAndCount(arr, temp, left, mid);
            invCount += mergeSortAndCount(arr, temp, mid + 1, right);
            invCount += merge(arr, temp, left, mid, right);
        }
        return invCount;
    }

public:
    long long int inversionCount(long long arr[], long long N) {
        long long* temp = new long long[N];
        long long totalInversions = mergeSortAndCount(arr, temp, 0, N - 1);
        delete[] temp;
        return totalInversions;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - During merge, if `arr[i] > arr[j]`: `invCount += (mid - i + 1)`.
 * - Time: O(N log N), Space: O(N).
 */
