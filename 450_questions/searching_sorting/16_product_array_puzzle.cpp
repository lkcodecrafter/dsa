/*
    QUESTION    : Product Array Puzzle (Product of array except self without division)
    Company Tags: Amazon, Microsoft, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/product-array-puzzle4525/1
    LeetCode    : https://leetcode.com/problems/product-of-array-except-self/
*/

#include <iostream>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Prefix and suffix product passes without division operator
// S.C : O(1) - Result array only (no extra prefix/suffix arrays allocated)
class Solution {
public:
    vector<long long int> productExceptSelf(vector<long long int>& nums, int n) {
        vector<long long int> result(n, 1);

        // Pass 1: Prefix products from left
        long long int prefix = 1;
        for (int i = 0; i < n; i++) {
            result[i] = prefix;
            prefix *= nums[i];
        }

        // Pass 2: Suffix products from right multiplied into result
        long long int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= suffix;
            suffix *= nums[i];
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Pass 1 (Left): `result[i] = prefix; prefix *= nums[i];`
 * - Pass 2 (Right): `result[i] *= suffix; suffix *= nums[i];`
 * - Time: O(N), Space: O(1) auxiliary.
 */
