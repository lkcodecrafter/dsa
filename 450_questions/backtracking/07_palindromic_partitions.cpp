/*
 * QUESTION: Print all palindromic partitions of a string
 * Link: https://www.geeksforgeeks.org/given-a-string-print-all-possible-palindromic-partition/
 * 
 * Input: s = "geeks"
 * Output: { {"g", "e", "e", "k", "s"}, {"g", "ee", "k", "s"} }
 */

#include <iostream>
#include <vector>
#include <string>

// Helper to check if a substring s[low...high] is a palindrome.
bool isPalindrome(const std::string& s, int low, int high) {
    while (low < high) {
        if (s[low] != s[high]) return false;
        low++;
        high--;
    }
    return true;
}

// Helper backtracking function to generate palindromic partitions starting at index `start`
void solvePalindromicPartitions(int start, const std::string& s, std::vector<std::string>& current_partition,
                                 std::vector<std::vector<std::string>>& result) {
    int n = s.length();
    
    // Base Case: Reached the end of the string
    if (start == n) {
        result.push_back(current_partition);
        return;
    }
    
    for (int end = start; end < n; end++) {
        // Check if substring s[start...end] is a palindrome
        if (isPalindrome(s, start, end)) {
            // Include substring in partition
            std::string sub = s.substr(start, end - start + 1);
            current_partition.push_back(sub);
            
            // Recurse on the remaining part of the string
            solvePalindromicPartitions(end + 1, s, current_partition, result);
            
            // Backtrack: Remove substring
            current_partition.pop_back();
        }
    }
}

// Main function to return all palindromic partitions
std::vector<std::vector<std::string>> allPalindromicPartitions(const std::string& s) {
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> current_partition;
    
    solvePalindromicPartitions(0, s, current_partition, result);
    
    return result;
}

/*
 * DRY RUN (s = "nit"):
 * 
 * | Step | start | end | Substring Checked | Is Palindrome? | current_partition State | Action / Next Recursion start |
 * | :--- | :---- | :-- | :---------------- | :------------- | :---------------------- | :---------------------------- |
 * | Init | 0     | -   | -                 | -              | {}                      | Start loop                    |
 * | 1    | 0     | 0   | "n"               | Yes            | {"n"}                   | Recurse at start = 1          |
 * | 2    | 1     | 1   | "i"               | Yes            | {"n", "i"}              | Recurse at start = 2          |
 * | 3    | 2     | 2   | "t"               | Yes            | {"n", "i", "t"}         | Recurse at start = 3          |
 * | 4    | 3     | -   | -                 | -              | {"n", "i", "t"}         | start == n -> Save partition  |
 * | 5    | 2     | -   | (loops end)       | -              | {"n", "i"}              | Backtrack -> pop "t"          |
 * | 6    | 1     | 2   | "it"              | No             | {"n", "i"}              | Try next end at level 1       |
 * | 7    | 1     | -   | (loops end)       | -              | {"n"}                   | Backtrack -> pop "i"          |
 * | 8    | 0     | 1   | "ni"              | No             | {}                      | Try next end at level 0       |
 * | 9    | 0     | 2   | "nit"             | No             | {}                      | Loop ends                     |
 * 
 * Resulting partitions: { {"n", "i", "t"} }
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine slicing a sausage into portions. 
 * You only make a cut if the piece between the previous cut and this cut is symmetric (a palindrome). 
 * If it is symmetric, you place it on a plate and move the knife forward. 
 * If you make it to the end of the sausage, you take a snapshot of the plate (save partition). 
 * Then you remove the last piece from the plate (backtrack) and try slicing at a longer mark.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Start recursion from index `start = 0`.
 * - Iterate `end` from `start` to `n - 1`.
 * - If `s[start...end]` is a palindrome:
 *   - Push `s[start...end]` into `current_partition`.
 *   - Recurse on `end + 1`.
 *   - Backtrack: Pop the substring from `current_partition`.
 * - If `start == n`, add `current_partition` to result.
 * - Time Complexity: O(N * 2^N) as there are 2^(N-1) partitions, and checking palindromes is O(N).
 * - Space Complexity: O(N) recursion stack space.
 */
