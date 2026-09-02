/*
 * QUESTION: Tug of War
 * Link: https://www.geeksforgeeks.org/tug-of-war/
 * 
 * Input: arr[] = {3, 4, 5, -3, 100, 1, 89, 54, 23, 20}
 * Output: Two subsets of size 5 each with minimum sum difference.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <numeric>

// Helper backtracking function to partition the set
void solveTugOfWar(int idx, int curr_count, int curr_sum, int total_sum, const std::vector<int>& arr,
                   std::vector<bool>& current_selected, std::vector<bool>& best_selected, int& min_diff) {
    int n = arr.size();
    
    // Base Case: Scanned all elements
    if (idx == n) {
        // We only care about splits of size n/2
        if (curr_count == n / 2) {
            int remaining_sum = total_sum - curr_sum;
            int diff = std::abs(curr_sum - remaining_sum);
            
            if (diff < min_diff) {
                min_diff = diff;
                best_selected = current_selected;
            }
        }
        return;
    }
    
    // Check if we can prune: if remaining elements are not enough to reach n/2, or if we already exceeded n/2
    if (curr_count + (n - idx) < n / 2 || curr_count > n / 2) {
        return;
    }
    
    // Choice 1: Include arr[idx] in subset 1
    current_selected[idx] = true;
    solveTugOfWar(idx + 1, curr_count + 1, curr_sum + arr[idx], total_sum, arr, current_selected, best_selected, min_diff);
    
    // Choice 2: Exclude arr[idx] from subset 1
    current_selected[idx] = false;
    solveTugOfWar(idx + 1, curr_count, curr_sum, total_sum, arr, current_selected, best_selected, min_diff);
}

// Wrapper function that prints the partition of the array
void tugOfWar(const std::vector<int>& arr) {
    int n = arr.size();
    int total_sum = std::accumulate(arr.begin(), arr.end(), 0);
    
    std::vector<bool> current_selected(n, false);
    std::vector<bool> best_selected(n, false);
    int min_diff = INT_MAX;
    
    solveTugOfWar(0, 0, 0, total_sum, arr, current_selected, best_selected, min_diff);
    
    // Print the subsets
    std::cout << "Subset 1: ";
    for (int i = 0; i < n; i++) {
        if (best_selected[i]) std::cout << arr[i] << " ";
    }
    std::cout << "\nSubset 2: ";
    for (int i = 0; i < n; i++) {
        if (!best_selected[i]) std::cout << arr[i] << " ";
    }
    std::cout << "\nMinimum difference: " << min_diff << "\n";
}

/*
 * DRY RUN (arr = {3, 4, 5, 6}, total_sum = 18):
 * n = 4, target count for subset 1 = 4/2 = 2.
 * 
 * | Step | idx | curr_count | curr_sum | current_selected | Action / Choice                            | min_diff Updated |
 * | :--- | :-- | :--------- | :------- | :--------------- | :----------------------------------------- | :--------------- |
 * | Init | 0   | 0          | 0        | {F, F, F, F}     | Start DFS                                  | INT_MAX          |
 * | 1    | 1   | 1          | 3        | {T, F, F, F}     | Include 3                                  | INT_MAX          |
 * | 2    | 2   | 2          | 7        | {T, T, F, F}     | Include 4                                  | INT_MAX          |
 * | 3    | 3   | 2          | 7        | {T, T, F, F}     | Exclude 5 (curr_count is 2, cannot exceed) | -                |
 * | 4    | 4   | 2          | 7        | {T, T, F, F}     | Exclude 6 -> Base Case. diff = |7 - 11|=4  | min_diff = 4     |
 * | 5    | 2   | 1          | 3        | {T, F, F, F}     | Backtrack to idx=2 (Exclude 4)             | -                |
 * | 6    | 3   | 2          | 8        | {T, F, T, F}     | Include 5                                  | -                |
 * | 7    | 4   | 2          | 8        | {T, F, T, F}     | Exclude 6 -> Base Case. diff = |8 - 10|=2  | min_diff = 2     |
 * 
 * Best selection yields: Subset 1 {3, 5} and Subset 2 {4, 6} with difference = 2.
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine picking two teams for a game of Tug of War from a line of people. 
 * You walk down the line. You decide whether to put the person in Team 1 or Team 2. 
 * To be fair, Team 1 must have exactly half the people (`n / 2`). 
 * You explore all options. When a choice gives teams of equal sizes, 
 * you weigh their total weights and record the team lists if the weight difference is the lowest so far.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Calculate total sum of elements.
 * - Call `solveTugOfWar(idx, curr_count, curr_sum, total_sum, arr, current_selected, best_selected, min_diff)`.
 * - Base Case: If `idx == n`, check if `curr_count == n / 2`. If yes, calculate `diff = abs(total_sum - 2 * curr_sum)` and update `min_diff`.
 * - Pruning Case: If `curr_count + (n - idx) < n / 2` or `curr_count > n / 2`, return immediately.
 * - Recursive Choices:
 *   - Include: `current_selected[idx] = true`, recurse with `curr_count + 1`, `curr_sum + arr[idx]`.
 *   - Exclude: `current_selected[idx] = false`, recurse with same count and sum.
 * - Time Complexity: O(2^N)
 * - Space Complexity: O(N) recursion stack.
 */
