#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates for the first number

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});

                    // Skip duplicates for the second number
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    // Skip duplicates for the third number
                    while (left < right && nums[right] == nums[right - 1]) right--;

                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }

        return result;
    }
};

/*
Dry Run:
Consider the input array [-1, 0, 1, 2, -1, -4].
1. Sort the array: [-4, -1, -1, 0, 1, 2]
2. Iterate through the array with index `i`:
    - i = 0: nums[i] = -4
        - left = 1 (nums[left] = -1), right = 5 (nums[right] = 2)
        - sum = -4 + (-1) + 2 = -3 < 0 → move left pointer to right
        - sum = -4 + (-1) + 2 = -3 < 0 → move left pointer to right
        - Continue until left >= right
    - i = 1: nums[i] = -1
        - left = 2 (nums[left] = -1), right = 5 (nums[right] = 2)
        - sum = (-1) + (-1) + 2 = 0 → add triplet [-1, -1, 2]
        - Skip duplicates for second number and third number
        - Move pointers inward
    Continue similarly for other indices.
Explanation:
The algorithm uses a two-pointer technique after sorting the array.
1. Sort the input array.
2. Iterate through each element as a potential first element of a triplet.
3. For each first element:
    a. Use two pointers (`left` and `right`) to find pairs that sum to zero.
    b. If the sum is zero, add the triplet to the result.
    c. Skip duplicates for both second and third numbers to avoid repeated triplets.
    d. Adjust pointers based on whether the sum is less than or greater than zero.
4. Return all unique triplets that sum to zero.

*/