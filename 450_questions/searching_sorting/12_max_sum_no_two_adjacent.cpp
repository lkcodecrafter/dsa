/*
    QUESTION    : Stickler Thief (Maximum sum such that no two elements are adjacent / House Robber)
    Company Tags: Amazon, Microsoft, Flipkart, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/stickler-theif-1587115621/1
    LeetCode    : https://leetcode.com/problems/house-robber/
*/

#include <iostream>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Single pass DP with constant space optimization
// S.C : O(1) - Two variables for previous states
class Solution {
public:
    int FindMaxSum(int arr[], int n) {
        if (n == 0) return 0;
        if (n == 1) return arr[0];

        int prev2 = 0;
        int prev1 = arr[0];

        for (int i = 1; i < n; i++) {
            int includeCurrent = arr[i] + prev2;
            int excludeCurrent = prev1;

            int currentMax = max(includeCurrent, excludeCurrent);

            prev2 = prev1;
            prev1 = currentMax;
        }

        return prev1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `include = arr[i] + prev2; exclude = prev1;`
 * - `curr = max(include, exclude); prev2 = prev1; prev1 = curr;`
 * - Time: O(N), Space: O(1).
 */
