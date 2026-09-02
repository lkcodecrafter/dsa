/*
 * QUESTION: Partition of a set into K subsets with equal sum
 * Link: https://practice.geeksforgeeks.org/problems/partition-array-to-k-subsets/1
 * 
 * Input: arr[] = {2, 1, 4, 5, 6}, K = 3
 * Output: True (Subsets are {5, 1}, {6}, {2, 4} each summing to 6)
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Recursive backtracking helper to assign elements to K subsets
bool canPartitionKSubsetsHelper(int idx, const std::vector<int>& arr, std::vector<int>& subset_sums,
                                int target_sum) {
    // Base Case: All elements successfully placed
    if (idx == arr.size()) {
        return true;
    }
    
    // Try placing arr[idx] in each of the K subsets
    for (size_t i = 0; i < subset_sums.size(); i++) {
        // If adding current element doesn't exceed target sum for this subset
        if (subset_sums[i] + arr[idx] <= target_sum) {
            subset_sums[i] += arr[idx]; // Include in subset i
            
            if (canPartitionKSubsetsHelper(idx + 1, arr, subset_sums, target_sum)) {
                return true;
            }
            
            subset_sums[i] -= arr[idx]; // Backtrack: Exclude
        }
        
        // OPTIMIZATION: If the current subset sum is 0, trying to place the element
        // in subsequent empty subsets is redundant and leads to duplicate recursive branches.
        if (subset_sums[i] == 0) {
            break;
        }
    }
    
    return false;
}

// Wrapper function to check partition possibility
bool isKPartitionPossible(std::vector<int>& arr, int k) {
    int n = arr.size();
    if (k == 1) return true;
    if (n < k) return false;
    
    int total_sum = std::accumulate(arr.begin(), arr.end(), 0);
    if (total_sum % k != 0) return false;
    
    int target_sum = total_sum / k;
    
    // Sort array in descending order to optimize backtracking (place larger numbers first)
    std::sort(arr.begin(), arr.end(), std::greater<int>());
    
    std::vector<int> subset_sums(k, 0);
    return canPartitionKSubsetsHelper(0, arr, subset_sums, target_sum);
}

/*
 * DRY RUN (arr = {5, 4, 2, 1}, K = 2):
 * total_sum = 12 -> target_sum = 6
 * Sorted descending: {5, 4, 2, 1}
 * subset_sums = {0, 0}
 * 
 * | Step | idx | arr[idx] | subset_sums State | Action / Choice Chosen                                         | Result |
 * | :--- | :-- | :------- | :---------------- | :------------------------------------------------------------- | :----- |
 * | Init | 0   | 5        | {0, 0}            | Try placing 5 in subset 0 -> subset_sums becomes {5, 0}        | -      |
 * | 1    | 1   | 4        | {5, 0}            | Try placing 4 in subset 0 -> 5 + 4 = 9 > 6 (Fails).            | -      |
 * |      |     |          |                   | Try placing 4 in subset 1 -> subset_sums becomes {5, 4}        | -      |
 * | 2    | 2   | 2        | {5, 4}            | Try placing 2 in subset 0 -> 5 + 2 = 7 > 6 (Fails).            | -      |
 * |      |     |          |                   | Try placing 2 in subset 1 -> 4 + 2 = 6 <= 6 (Safe).            | -      |
 * |      |     |          |                   | subset_sums becomes {5, 6}                                     | -      |
 * | 3    | 3   | 1        | {5, 6}            | Try placing 1 in subset 0 -> 5 + 1 = 6 <= 6 (Safe).            | -      |
 * |      |     |          |                   | subset_sums becomes {6, 6}                                     | -      |
 * | 4    | 4   | -        | {6, 6}            | idx == arr.size() -> Base Case matches!                        | True   |
 * 
 * Result: true
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine packing suitcases of identical weight limits (`target_sum`). 
 * You have `K` suitcases. 
 * You pick the heaviest item (`descending sort` optimization) and try placing it in suitcase 1. 
 * If it fits, you place it and recurse. 
 * If suitcase 1 is empty and the item fails to fit or lead to a solution, 
 * you do not try putting it in suitcases 2, 3, etc., as they are also empty and identical.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Calculate total sum. If `total_sum % k != 0`, return `false`. Target sum = `total_sum / k`.
 * - Sort array in descending order (`std::greater<int>()`) to process larger elements first.
 * - Call `canPartitionKSubsetsHelper(0, arr, subset_sums, target_sum)`.
 * - Base Case: If `idx == arr.size()`, return `true`.
 * - Loop over each subset `i`:
 *   - If `subset_sums[i] + arr[idx] <= target_sum`, add to `subset_sums[i]` and recurse on `idx + 1`.
 *   - Backtrack: subtract `arr[idx]`.
 *   - If `subset_sums[i] == 0`, break (empty subset symmetry pruning).
 * - Time Complexity: O(K^N) worst-case (drastically reduced by pruning and sorting).
 * - Space Complexity: O(N) recursion stack.
 */
