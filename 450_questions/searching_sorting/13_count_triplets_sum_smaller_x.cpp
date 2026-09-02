/*
    QUESTION    : Count triplets with sum smaller than a given value X
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/count-triplets-with-sum-smaller-than-x5549/1
*/

#include <iostream>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - Sorting + Two pointers
// S.C : O(1)   - Constant auxiliary space
class Solution {
public:
    long long countTriplets(long long arr[], int n, long long sum) {
        sort(arr, arr + n);
        long long count = 0;

        for (int i = 0; i < n - 2; i++) {
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                long long currentSum = arr[i] + arr[left] + arr[right];

                if (currentSum < sum) {
                    // All elements between left and right will also have sum < sum with arr[i]
                    count += (right - left);
                    left++;
                } else {
                    right--;
                }
            }
        }

        return count;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(arr)`.
 * - For each `i`: `left = i + 1, right = n - 1`.
 * - If `arr[i] + arr[left] + arr[right] < sum`: `count += (right - left); left++;`
 * - Else: `right--;`
 * - Time: O(N^2), Space: O(1).
 */
