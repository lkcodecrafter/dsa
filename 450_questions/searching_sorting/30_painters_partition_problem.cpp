/*
    QUESTION    : The Painter's Partition Problem-II
    Company Tags: Amazon, Google, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/the-painters-partition-problem1535/1
*/

#include <iostream>
#include <numeric>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * log(Sum_Length)) - Binary Search on Answer
// S.C : O(1)                   - Constant auxiliary space
class Solution {
private:
    bool isPossible(int arr[], int n, int k, long long maxTime) {
        int paintersCount = 1;
        long long currentAllocated = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] > maxTime) return false;

            if (currentAllocated + arr[i] > maxTime) {
                paintersCount++;
                currentAllocated = arr[i];
                if (paintersCount > k) return false;
            } else {
                currentAllocated += arr[i];
            }
        }

        return true;
    }

public:
    long long minTime(int arr[], int n, int k) {
        long long low = *max_element(arr, arr + n);
        long long high = 0;
        for (int i = 0; i < n; i++) high += arr[i];

        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (isPossible(arr, n, k, mid)) {
                ans = mid;
                high = mid - 1; // Try minimizing max time
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Identical structure to Book Allocation: Binary Search on `[max_len, sum_len]`.
 * - Time: O(N log(sum)), Space: O(1).
 */
