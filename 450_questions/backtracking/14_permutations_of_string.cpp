/*
 * QUESTION: Print all permutations of a string (handling duplicates and sorted output)
 * Link: https://practice.geeksforgeeks.org/problems/permutations-of-a-given-string/0
 * 
 * Input: S = "ABC"
 * Output: {"ABC", "ACB", "BAC", "BCA", "CAB", "CBA"}
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

// Helper backtracking function to generate permutations in-place
void solvePermutations(int idx, std::string& s, std::vector<std::string>& result) {
    int n = s.length();
    
    // Base Case: Permuted the entire string
    if (idx == n) {
        result.push_back(s);
        return;
    }
    
    // Local set to avoid swapping duplicate characters at this position
    std::unordered_set<char> swapped;
    
    for (int i = idx; i < n; i++) {
        // If s[i] is already swapped at this index level, skip to avoid duplicates
        if (swapped.find(s[i]) == swapped.end()) {
            swapped.insert(s[i]);
            
            std::swap(s[idx], s[i]); // Swap
            
            solvePermutations(idx + 1, s, result); // Recurse
            
            std::swap(s[idx], s[i]); // Backtrack: Restore string
        }
    }
}

// Main function to return all unique sorted permutations
std::vector<std::string> find_permutation(std::string S) {
    std::vector<std::string> result;
    
    // Sort input initially to help group identical characters
    std::sort(S.begin(), S.end());
    
    solvePermutations(0, S, result);
    
    // Sort results to ensure lexicographical order
    std::sort(result.begin(), result.end());
    
    return result;
}

/*
 * DRY RUN (S = "ABA"):
 * Sorted string: "AAB"
 * Call solvePermutations with idx = 0
 * 
 * | Step | idx | Loop i | Char s[i] | Swapped Set at idx | Action / Swaps Made                       | current string | result State      |
 * | :--- | :-- | :----- | :-------- | :----------------- | :---------------------------------------- | :------------- | :---------------- |
 * | Init | 0   | -      | -         | {}                 | Start level 0                             | "AAB"          | {}                |
 * | 1    | 0   | 0      | 'A'       | {'A'}              | Swap(0,0) -> recurse at idx=1             | "AAB"          | {}                |
 * | 2    | 1   | 1      | 'A'       | {'A'}              | Swap(1,1) -> recurse at idx=2             | "AAB"          | {}                |
 * | 3    | 2   | 2      | 'B'       | {'B'}              | Swap(2,2) -> base case! Save "AAB"        | "AAB"          | {"AAB"}           |
 * | 4    | 1   | 2      | 'B'       | {'A', 'B'}         | Backtrack -> Swap(1,2) -> recurse at idx=2| "ABA"          | {"AAB"}           |
 * | 5    | 2   | 2      | 'A'       | {'A'}              | Swap(2,2) -> base case! Save "ABA"        | "ABA"          | {"AAB", "ABA"}    |
 * | 6    | 0   | 1      | 'A'       | {'A'} (dup skip)   | 'A' already in set -> Skip                | "AAB"          | {"AAB", "ABA"}    |
 * | 7    | 0   | 2      | 'B'       | {'A', 'B'}         | Swap(0,2) -> "BAA" -> recurse at idx=1    | "BAA"          | {"AAB", "ABA"}    |
 * | 8    | 1   | 1      | 'A'       | {'A'}              | Swap(1,1) -> recurse at idx=2             | "BAA"          | {"AAB", "ABA"}    |
 * | 9    | 2   | 2      | 'A'       | {'A'}              | Swap(2,2) -> base case! Save "BAA"        | "BAA"          | {"AAB","ABA","BAA"}|
 * 
 * Final unique permutations: {"AAB", "ABA", "BAA"}
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine spelling words by swapping letters in your hand. 
 * You fix the first letter at index `idx` by swapping it with one of the letters to its right. 
 * To avoid repeating yourself, if you have two 'A's in your hand, you only swap the first 'A' into the slot.
 * Once you fix the letter at `idx`, you let your friend permute the remaining letters on the right.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Call `solvePermutations(idx, s, result)`.
 * - Base Case: If `idx == n`, push `s` to `result`.
 * - For index `i` from `idx` to `n - 1`:
 *   - Use an `unordered_set<char> swapped` to track characters swapped at index `idx`.
 *   - If `s[i]` is not in the set, insert it, swap `s[idx]` and `s[i]`, recurse on `idx + 1`, and swap back.
 * - Sort the final result list to ensure lexicographical order.
 * - Time Complexity: O(N! * N)
 * - Space Complexity: O(N) recursion stack.
 */
