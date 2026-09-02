/*
 * QUESTION: Find Longest Consecutive Subsequence
 * Link: https://practice.geeksforgeeks.org/problems/longest-consecutive-subsequence/0
 * 
 * Input: arr[] = {2, 6, 1, 9, 4, 5, 3}
 * Output: 6
 * Explanation: The consecutive numbers here are {1, 2, 3, 4, 5, 6}, length is 6.
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

// Returns the length of the longest consecutive subsequence.
int findLongestConseqSubseq(const std::vector<int>& arr) {
    std::unordered_set<int> num_set(arr.begin(), arr.end());
    int longest_streak = 0;
    
    for (int num : num_set) {
        // If num - 1 is not in the set, then num is the starting point of a subsequence
        if (num_set.find(num - 1) == num_set.end()) {
            int current_num = num;
            int current_streak = 1;
            
            // Count consecutive elements following current_num
            while (num_set.find(current_num + 1) != num_set.end()) {
                current_num += 1;
                current_streak += 1;
            }
            
            longest_streak = std::max(longest_streak, current_streak);
        }
    }
    
    return longest_streak;
}

/*
 * DRY RUN (arr = {2, 6, 1, 9, 4, 5, 3}):
 * num_set = {1, 2, 3, 4, 5, 6, 9}
 * 
 * | Step | num | num-1 in Set? | Streak Counting Sequence                      | Streak Length | longest_streak Updated |
 * | :--- | :-- | :------------ | :-------------------------------------------- | :------------ | :--------------------- |
 * | 1    | 2   | Yes (1 is in) | Skip (not start of sequence)                  | -             | 0                      |
 * | 2    | 6   | Yes (5 is in) | Skip (not start of sequence)                  | -             | 0                      |
 * | 3    | 1   | No            | Starts streak: 1 -> 2 -> 3 -> 4 -> 5 -> 6      | 6             | max(0, 6) = 6          |
 * | 4    | 9   | No            | Starts streak: 9                              | 1             | max(6, 1) = 6          |
 * | 5    | 4   | Yes (3 is in) | Skip                                          | -             | 6                      |
 * | 6    | 5   | Yes (4 is in) | Skip                                          | -             | 6                      |
 * | 7    | 3   | Yes (2 is in) | Skip                                          | -             | 6                      |
 * 
 * Longest Consecutive Subsequence Length = 6
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine finding chains of consecutive room numbers. 
 * To avoid repeating work, you only count a chain if you are standing at the absolute beginning of it 
 * (meaning there is no room with number `num - 1`). 
 * From there, you walk forward as far as the consecutive rooms go, record the chain length, and move on.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Insert all elements into an `unordered_set`.
 * - Iterate through each unique number `num` in the set:
 *   - If `num - 1` is NOT in the set, start a chain from `num`.
 *   - Keep incrementing `num` while checking its presence in the set to count the length of the chain.
 *   - Update `longest_streak = max(longest_streak, current_streak)`.
 * - Time Complexity: O(N) because each element is visited at most twice.
 * - Space Complexity: O(N) to store the set.
 */
