/*
    QUESTION    : Find All Four Sum Numbers (4Sum)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/find-all-four-sum-numbers1732/1
    LeetCode    : https://leetcode.com/problems/4sum/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^3) - Two nested loops + Two pointers with duplicate skipping
// S.C : O(1)   - Quadruplets result storage
class Solution {
public:
    vector<vector<int>> fourSum(vector<int> &arr, int k) {
        vector<vector<int>> result;
        int n = arr.size();
        if (n < 4) return result;

        sort(arr.begin(), arr.end());

        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && arr[i] == arr[i - 1]) continue; // Skip duplicate i

            for (int j = i + 1; j < n - 2; j++) {
                if (j > i + 1 && arr[j] == arr[j - 1]) continue; // Skip duplicate j

                int left = j + 1;
                int right = n - 1;

                while (left < right) {
                    long long sum = (long long)arr[i] + arr[j] + arr[left] + arr[right];

                    if (sum == k) {
                        result.push_back({arr[i], arr[j], arr[left], arr[right]});

                        // Skip duplicates for left and right
                        while (left < right && arr[left] == arr[left + 1]) left++;
                        while (left < right && arr[right] == arr[right - 1]) right--;

                        left++;
                        right--;
                    } else if (sum < k) {
                        left++;
                    } else {
                        right--;
                    }
                }
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort(arr)`.
 * - Nested loops `i` and `j`, inner two-pointer `left` and `right`.
 * - Skip duplicates at each level.
 * - Time: O(N^3), Space: O(1).
 */
