/*
 * QUESTION: Find Maximum number possible by doing at-most K swaps
 * Link: https://practice.geeksforgeeks.org/problems/largest-number-in-k-swaps/0
 * 
 * Input: str = "254", K = 1
 * Output: "524"
 */

#include <iostream>
#include <string>
#include <algorithm>

// Recursive backtracking helper to find the maximum number
void findMaximumNumHelper(std::string str, int k, int idx, std::string& max_str) {
    int n = str.length();
    
    // Base Case: No swaps left or index reached the end
    if (k == 0 || idx == n - 1) {
        return;
    }
    
    // Find the maximum digit in the remaining suffix str[idx...n-1]
    char max_char = str[idx];
    for (int i = idx + 1; i < n; i++) {
        if (str[i] > max_char) {
            max_char = str[i];
        }
    }
    
    // If the maximum digit is greater than the digit at current index, we must swap.
    // Otherwise, we do not need to swap at this position, we just move to the next.
    if (max_char != str[idx]) {
        // Decrement k since we are about to make a swap
        k--;
    }
    
    // If max_char equals str[idx], just recurse on the next index without swapping
    if (max_char == str[idx]) {
        findMaximumNumHelper(str, k, idx + 1, max_str);
        return;
    }
    
    // Try swapping str[idx] with all occurrences of max_char in the suffix
    for (int i = idx + 1; i < n; i++) {
        if (str[i] == max_char) {
            std::swap(str[idx], str[i]);
            
            // Update global maximum if current string is larger
            if (str > max_str) {
                max_str = str;
            }
            
            // Recurse for the next index
            findMaximumNumHelper(str, k, idx + 1, max_str);
            
            // Backtrack: Undo swap
            std::swap(str[idx], str[i]);
        }
    }
}

// Wrapper function to find the maximum number
std::string findMaximumNum(const std::string& str, int k) {
    std::string max_str = str;
    findMaximumNumHelper(str, k, 0, max_str);
    return max_str;
}

/*
 * DRY RUN (str = "1293", K = 1):
 * Initial: max_str = "1293", call helper with idx = 0
 * 
 * | Step | idx | k | str  | Max Char in Suffix | Action / Swaps Tried                                    | max_str Updated |
 * | :--- | :-- | :- | :--- | :----------------- | :------------------------------------------------------ | :-------------- |
 * | Init | 0   | 1  | 1293 | '9'                | max_char != '1' -> k decremented to 0. Swap '1' and '9'.| "9213"          |
 * | 1    | 1   | 0  | 9213 | '2' (at idx 1)     | k == 0 -> Base Case reached. Return.                    | "9213"          |
 * | 2    | -   | -  | 1293 | -                  | Backtrack: Swap back to "1293". Loop ends.              | "9213"          |
 * 
 * Max String found: "9213"
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine you want to form the largest number by swapping digits. 
 * Starting from the left, you look for the largest digit to its right. 
 * If it's larger than the current digit, you swap them. 
 * If there are multiple copies of the largest digit, you try swapping with each copy 
 * (since one placement might yield a better overall number than another after further swaps).
 * 
 * 1-MINUTE QUICK REVISION:
 * - Maintain global `max_str` initialized to `str`.
 * - For position `idx`, find the maximum digit `max_char` in `str[idx...n-1]`.
 * - If `max_char == str[idx]`, recurse on `idx + 1` with same `k`.
 * - If `max_char > str[idx]`, decrement `k`. For every index `i` from `idx + 1` where `str[i] == max_char`:
 *   - Swap `str[idx]` and `str[i]`.
 *   - Update `max_str = max(max_str, str)`.
 *   - Recurse on `idx + 1` with `k-1` swaps remaining.
 *   - Backtrack: swap back.
 * - Time Complexity: O(N^K)
 * - Space Complexity: O(N) recursion stack.
 */
