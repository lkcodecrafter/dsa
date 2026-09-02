/*
 * QUESTION: Subset Sum Problem (Partition Equal Subset Sum)
 * Link: https://practice.geeksforgeeks.org/problems/subset-sum-problem2014/1
 * 
 * Input: arr[] = {1, 5, 11, 5}
 * Output: True (Can be partitioned as {1, 5, 5} and {11})
 */

#include <iostream>
#include <vector>
#include <numeric>

// Memoized backtracking helper to check if a subset with the given target sum exists
bool checkSubsetSum(int idx, int target, const std::vector<int>& arr, std::vector<std::vector<int>>& memo) {
    // Base Cases
    if (target == 0) return true;
    if (idx < 0 || target < 0) return false;
    
    // Return cached result if already computed (-1 means uncomputed)
    if (memo[idx][target] != -1) {
        return memo[idx][target];
    }
    
    // Choice 1: Include current element arr[idx] in subset (if it doesn't exceed target)
    bool include = false;
    if (arr[idx] <= target) {
        include = checkSubsetSum(idx - 1, target - arr[idx], arr, memo);
    }
    
    // Choice 2: Exclude current element
    bool exclude = checkSubsetSum(idx - 1, target, arr, memo);
    
    // Cache and return result
    return memo[idx][target] = (include || exclude);
}

// Main function to check if the array can be partitioned into two subsets of equal sum
bool equalPartition(const std::vector<int>& arr) {
    int sum = std::accumulate(arr.begin(), arr.end(), 0);
    
    // If total sum is odd, it's impossible to partition into two equal subsets
    if (sum % 2 != 0) return false;
    
    int target = sum / 2;
    int n = arr.size();
    
    // memo[i][j] stores status of checking subset sum for first i elements with target j
    std::vector<std::vector<int>> memo(n, std::vector<int>(target + 1, -1));
    
    return checkSubsetSum(n - 1, target, arr, memo);
}

/*
 * DRY RUN (arr = {1, 5, 11, 5}, sum = 22 -> target = 11):
 * Pointers: idx starts at 3, target starts at 11
 * 
 * | Step | idx | target | Element arr[idx] | Include Branch Check (target - arr[idx]) | Exclude Branch Check | Memo Table Update | Result |
 * | :--- | :-- | :----- | :--------------- | :--------------------------------------- | :------------------- | :---------------- | :----- |
 * | Init | 3   | 11     | 5                | checkSubsetSum(2, 6)                     | checkSubsetSum(2,11) | -                 | -      |
 * | 1    | 2   | 6      | 11               | 11 > 6 -> cannot include                 | checkSubsetSum(1, 6) | -                 | -      |
 * | 2    | 1   | 6      | 5                | checkSubsetSum(0, 1)                     | checkSubsetSum(0, 6) | -                 | -      |
 * | 3    | 0   | 1      | 1                | checkSubsetSum(-1,0) -> True!            | -                    | memo[0][1] = 1    | True   |
 * | 4    | 1   | 6      | 5                | (returns True from include branch)       | -                    | memo[1][6] = 1    | True   |
 * | 5    | 2   | 6      | 11               | (returns True from exclude branch)       | -                    | memo[2][6] = 1    | True   |
 * | 6    | 3   | 11     | 5                | (returns True from include branch)       | -                    | memo[3][11] = 1   | True   |
 * 
 * Result: true
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine packing items in a bag to reach a target weight. 
 * For the last item, you can either put it in the bag (decrease target weight) 
 * or leave it out (target weight remains the same). 
 * To avoid repeating calculations for the same remaining items and weight, 
 * you log your findings in a logbook (the memo table).
 * 
 * 1-MINUTE QUICK REVISION:
 * - Calculate total `sum` of array elements. If `sum % 2 != 0`, return `false`.
 * - Find if a subset exists with target sum equal to `sum / 2` using memoized backtracking.
 * - For element `idx`, the two choices are:
 *   - Include: `checkSubsetSum(idx - 1, target - arr[idx])` (if `arr[idx] <= target`).
 *   - Exclude: `checkSubsetSum(idx - 1, target)`.
 * - Use a 2D vector `memo` of size `N x (target + 1)` initialized to `-1` to cache intermediate states.
 * - Time Complexity: O(N * Target)
 * - Space Complexity: O(N * Target)
 */
