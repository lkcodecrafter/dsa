/*
 * QUESTION: Combinational Sum
 * Link: https://practice.geeksforgeeks.org/problems/combination-sum/0
 * 
 * Input: A[] = {7, 2, 6, 5}, target = 16
 * Output: { {2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 6}, {2, 2, 2, 5, 5}, {2, 2, 5, 7}, {2, 2, 6, 6}, {2, 7, 7}, {5, 5, 6} }
 */

#include <iostream>
#include <vector>
#include <algorithm>

// Helper backtracking function
void solveCombinationSum(int idx, int target, const std::vector<int>& candidates,
                           std::vector<int>& current, std::vector<std::vector<int>>& result) {
    // Base Cases
    if (target == 0) {
        result.push_back(current);
        return;
    }
    if (idx == candidates.size() || target < 0) {
        return;
    }
    
    // Choice 1: Include candidates[idx] (can be reused, so index doesn't increment)
    if (candidates[idx] <= target) {
        current.push_back(candidates[idx]);
        solveCombinationSum(idx, target - candidates[idx], candidates, current, result);
        current.pop_back(); // Backtrack
    }
    
    // Choice 2: Exclude candidates[idx] (move to the next candidate)
    solveCombinationSum(idx + 1, target, candidates, current, result);
}

// Main function to return all combinations
std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
    std::vector<std::vector<int>> result;
    std::vector<int> current;
    
    // Step 1: Sort candidates
    std::sort(candidates.begin(), candidates.end());
    
    // Step 2: Remove duplicates to avoid duplicate combinations
    candidates.erase(std::unique(candidates.begin(), candidates.end()), candidates.end());
    
    solveCombinationSum(0, target, candidates, current, result);
    
    return result;
}

/*
 * DRY RUN (candidates = {2, 3, 5}, target = 8):
 * Sorted unique: {2, 3, 5}
 * 
 * | Step | idx | target | Element | Action / Choice Chosen                        | current State | result State                  |
 * | :--- | :-- | :----- | :------ | :-------------------------------------------- | :------------ | :---------------------------- |
 * | Init | 0   | 8      | 2       | Include 2 -> recurse with target = 6          | {2}           | {}                            |
 * | 1    | 0   | 6      | 2       | Include 2 -> recurse with target = 4          | {2, 2}        | {}                            |
 * | 2    | 0   | 4      | 2       | Include 2 -> recurse with target = 2          | {2, 2, 2}     | {}                            |
 * | 3    | 0   | 2      | 2       | Include 2 -> recurse with target = 0          | {2, 2, 2, 2}  | {}                            |
 * | 4    | 0   | 0      | -       | Base Case (target == 0) -> Save combination   | {2, 2, 2, 2}  | { {2,2,2,2} }                 |
 * | 5    | 0   | 2      | 2       | Backtrack -> pop 2; try Exclude (idx=1, target=2)| {2, 2, 2}     | { {2,2,2,2} }                 |
 * | 6    | 1   | 2      | 3       | 3 > 2 -> cannot include; try Exclude (idx=2)  | {2, 2, 2}     | { {2,2,2,2} }                 |
 * | 7    | 2   | 2      | 5       | 5 > 2 -> cannot include; try Exclude (idx=3)  | {2, 2, 2}     | { {2,2,2,2} }                 |
 * | 8    | 0   | 4      | 2       | Backtrack -> pop 2; try Exclude (idx=1, target=4)| {2, 2}        | { {2,2,2,2} }                 |
 * | 9    | 1   | 4      | 3       | Include 3 -> recurse with target = 1          | {2, 2, 3}     | { {2,2,2,2} }                 |
 * | 10   | 1   | 1      | 3       | 3 > 1 -> Exclude -> idx=2 -> 5 > 1 -> Exclude | {2, 2}        | { {2,2,2,2} }                 |
 * 
 * Result contains { {2,2,2,2}, {2,3,3}, {3,5} } etc.
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine making change for a dollar bill using coins from a tray. 
 * The tray is sorted. You try to use the smallest coin. 
 * You can keep adding the same coin until your total matches or exceeds the target. 
 * When it exceeds, you remove the last coin and move to the next larger coin on the tray.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Sort and remove duplicates from candidates.
 * - Call `solveCombinationSum(idx, target, candidates, current, result)`.
 * - Base Cases:
 *   - If `target == 0`, save `current` to `result`.
 *   - If `idx == candidates.size()` or `target < 0`, return.
 * - Inclusion Choice: If `candidates[idx] <= target`, push candidate to `current`, recurse with same `idx` and `target - candidates[idx]`, then pop (backtrack).
 * - Exclusion Choice: Recurse with `idx + 1` and same `target`.
 * - Time Complexity: O(2^T) where T is the target sum divided by minimum candidate value.
 * - Space Complexity: O(T) recursion depth.
 */
