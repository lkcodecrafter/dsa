/*
    QUESTION    : Next Permutation
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/next-permutation5265/1
    LeetCode    : https://leetcode.com/problems/next-permutation/
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - 3 single-pass sweeps (find dip, find successor, reverse suffix)
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    vector<int> nextPermutation(int N, vector<int> arr) {
        int idx = -1;

        // Step 1: Find the first decreasing element from right (the pivot dip)
        for (int i = N - 2; i >= 0; i--) {
            if (arr[i] < arr[i + 1]) {
                idx = i;
                break;
            }
        }

        // If no dip found, array is in descending order -> reverse to get smallest permutation
        if (idx == -1) {
            reverse(arr.begin(), arr.end());
            return arr;
        }

        // Step 2: Find the smallest element in suffix larger than arr[idx]
        for (int i = N - 1; i > idx; i--) {
            if (arr[i] > arr[idx]) {
                swap(arr[i], arr[idx]);
                break;
            }
        }

        // Step 3: Reverse the suffix from idx + 1 to end
        reverse(arr.begin() + idx + 1, arr.end());

        return arr;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Find first index `i` from right where `arr[i] < arr[i+1]`.
 * - If not found $\rightarrow$ `reverse(arr)`.
 * - Else: swap `arr[i]` with next greater element from right, then `reverse(arr.begin() + i + 1, arr.end())`.
 * - Time: O(N), Space: O(1).
 */
