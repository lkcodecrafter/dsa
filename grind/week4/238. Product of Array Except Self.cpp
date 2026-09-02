#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
 * Problem: Product of Array Except Self (LeetCode 238)
 * Return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
 * Must run in O(n) time and without using the division operation.
 *
 * Pattern: Prefix & Suffix Products / Accumulators
 *
 * Complexity:
 * - Time Complexity: O(N) where N is the number of elements in nums. We make exactly two sequential linear passes.
 * - Space Complexity: O(1) auxiliary space (excluding the output container).
 *
 * Visualizations:
 * Input array: [1,  2,  3,  4]
 *
 * Left products (Prefix):
 *   ans[0] = 1
 *   ans[1] = 1 * nums[0] = 1
 *   ans[2] = 1 * nums[0] * nums[1] = 2
 *   ans[3] = 1 * nums[0] * nums[1] * nums[2] = 6
 *   Prefix vector: [1, 1, 2, 6]
 *
 * Right products (Suffix, accumulated via single right_prod variable):
 *   ans[3] *= 1              => 6
 *   ans[2] *= 4              => 8
 *   ans[1] *= 4 * 3 = 12     => 12
 *   ans[0] *= 4 * 3 * 2 = 24 => 24
 *   Final Result: [24, 12, 8, 6]
 *
 * Memorization Hook:
 * "Store prefix products in the output array in a forward pass. 
 * Then, maintain a running suffix product in a backward pass, multiplying it into the output array."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize result vector `ans` of size `n` with 1.
 * 2. Set prefix accumulator `left_prod = 1`.
 * 3. Traverse left-to-right: `ans[i] = left_prod`, then update `left_prod *= nums[i]`.
 * 4. Set suffix accumulator `right_prod = 1`.
 * 5. Traverse right-to-left: `ans[i] *= right_prod`, then update `right_prod *= nums[i]`.
 * 6. Return `ans`.
 *
 * Dry Run:
 * nums = [1, 2, 3, 4]
 * Output array `ans` initialized to [1, 1, 1, 1]
 *
 * Left-to-right pass:
 * | i | nums[i] | ans[i] assignment (left_prod) | left_prod update (left_prod * nums[i]) | ans state after step |
 * |---|---------|-------------------------------|----------------------------------------|----------------------|
 * | 0 | 1       | ans[0] = 1                    | left_prod = 1 * 1 = 1                  | [1, 1, 1, 1]         |
 * | 1 | 2       | ans[1] = 1                    | left_prod = 1 * 2 = 2                  | [1, 1, 1, 1]         |
 * | 2 | 3       | ans[2] = 2                    | left_prod = 2 * 3 = 6                  | [1, 1, 2, 1]         |
 * | 3 | 4       | ans[3] = 6                    | left_prod = 6 * 4 = 24                 | [1, 1, 2, 6]         |
 *
 * Right-to-left pass (starting right_prod = 1):
 * | i | nums[i] | ans[i] update (ans[i] * right_prod) | right_prod update (right_prod * nums[i]) | ans state after step |
 * |---|---------|-------------------------------------|------------------------------------------|----------------------|
 * | 3 | 4       | ans[3] = 6 * 1 = 6                  | right_prod = 1 * 4 = 4                   | [1, 1, 2, 6]         |
 * | 2 | 3       | ans[2] = 2 * 4 = 8                  | right_prod = 4 * 3 = 12                  | [1, 1, 8, 6]         |
 * | 1 | 2       | ans[1] = 1 * 12 = 12                | right_prod = 12 * 2 = 24                 | [1, 12, 8, 6]        |
 * | 0 | 1       | ans[0] = 1 * 24 = 24                | right_prod = 24 * 1 = 24                 | [24, 12, 8, 6]       |
 */
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        
        // Pass 1: Store prefix products in output array
        int left = 1;
        for (int i = 0; i < n; i++) {
            result[i] = left;
            left *= nums[i]; // Accumulate left product
        }
        
        // Pass 2: Multiply with suffix products from right to left
        int right = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= right; // Multiply by right product
            right *= nums[i]; // Accumulate right product
        }

        return result;
    }
};