/*
 * QUESTION: Find if there is any subarray with sum equal to 0
 * Link: https://practice.geeksforgeeks.org/problems/subarray-with-0-sum/0
 * 
 * Input: arr[] = {4, 2, -3, 1, 6}
 * Output: Yes (Subarray {2, -3, 1} has sum 0)
 */

#include <iostream>
#include <vector>
#include <unordered_set>

// Returns true if there is a subarray with sum equal to 0, else false.
bool hasZeroSumSubarray(const std::vector<int>& arr) {
    std::unordered_set<int> prefix_sums;
    int current_sum = 0;
    
    for (int num : arr) {
        current_sum += num;
        
        // If current prefix sum is 0, or if we have seen this prefix sum before,
        // then the subarray between that point and current index sums to 0.
        if (current_sum == 0 || prefix_sums.find(current_sum) != prefix_sums.end()) {
            return true;
        }
        
        prefix_sums.insert(current_sum);
    }
    
    return false;
}

/*
 * DRY RUN (arr = {4, 2, -3, 1, 6}):
 * 
 * | Step | Element | current_sum | Seen in prefix_sums? | Action / Result                 | prefix_sums State |
 * | :--- | :------ | :---------- | :------------------- | :------------------------------ | :---------------- |
 * | Init | -       | 0           | -                    | Start loop                      | {}                |
 * | 1    | 4       | 4           | No                   | Insert 4                        | {4}               |
 * | 2    | 2       | 6           | No                   | Insert 6                        | {4, 6}            |
 * | 3    | -3      | 3           | No                   | Insert 3                        | {4, 6, 3}         |
 * | 4    | 1       | 4           | Yes (4 is in set)    | Match found! Return true        | {4, 6, 3}         |
 * 
 * Result: true
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine walking on a path, counting your net altitude change. 
 * If you reach the exact same altitude you were at earlier, 
 * the path you walked in between must have had a net height change of 0.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Use an `unordered_set` to store all running prefix sums.
 * - Initialize `current_sum = 0`.
 * - Iterate through the array:
 *   - Add the element to `current_sum`.
 *   - If `current_sum == 0` or `current_sum` exists in the set, return `true`.
 *   - Insert `current_sum` into the set.
 * - Return `false` if the loop ends.
 * - Time Complexity: O(N)
 * - Space Complexity: O(N)
 */
