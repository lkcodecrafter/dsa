/*
 * QUESTION: Remove Invalid Parentheses
 * Link: https://leetcode.com/problems/remove-invalid-parentheses/
 * 
 * Input: s = "()())()"
 * Output: {"()()()", "(())()"}
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

// Helper to check if a string of parentheses is valid.
bool isValid(const std::string& str) {
    int balance = 0;
    for (char c : str) {
        if (c == '(') {
            balance++;
        } else if (c == ')') {
            balance--;
            if (balance < 0) return false;
        }
    }
    return balance == 0;
}

// Backtracking function to remove minimum number of invalid parentheses
void backtrack(int idx, int rem_l, int rem_r, std::string current, const std::string& original,
               std::unordered_set<std::string>& result) {
    // Base Case
    if (rem_l == 0 && rem_r == 0) {
        // Build the potential candidate by adding the remaining suffix
        std::string candidate = current + original.substr(idx);
        if (isValid(candidate)) {
            result.insert(candidate);
        }
        return;
    }
    
    if (idx == original.length()) return;
    
    char c = original[idx];
    
    // Optimization to skip duplicate recursive branches
    // If the current character is identical to the previous one and we are deciding whether to remove it,
    // we only remove the first instance to avoid duplicate branches.
    
    // Choice 1: Remove current character c
    if (c == '(' && rem_l > 0) {
        backtrack(idx + 1, rem_l - 1, rem_r, current, original, result);
    }
    if (c == ')' && rem_r > 0) {
        backtrack(idx + 1, rem_l, rem_r - 1, current, original, result);
    }
    
    // Choice 2: Keep current character c
    backtrack(idx + 1, rem_l, rem_r, current + c, original, result);
}

// Main function to remove invalid parentheses
std::vector<std::string> removeInvalidParentheses(const std::string& s) {
    int rem_l = 0; // Number of left parentheses to remove
    int rem_r = 0; // Number of right parentheses to remove
    
    for (char c : s) {
        if (c == '(') {
            rem_l++;
        } else if (c == ')') {
            if (rem_l > 0) {
                rem_l--; // Match found
            } else {
                rem_r++; // Unmatched closing parenthesis
            }
        }
    }
    
    std::unordered_set<std::string> result_set;
    backtrack(0, rem_l, rem_r, "", s, result_set);
    
    return std::vector<std::string>(result_set.begin(), result_set.end());
}

/*
 * DRY RUN (s = "()())()"):
 * Initial count:
 * - rem_l = 0, rem_r = 1 (since we have an extra closing parenthesis)
 * 
 * | Step | idx | rem_l | rem_r | current | Action / Branch Taken                                   | result_set State      |
 * | :--- | :-- | :---- | :---- | :------ | :------------------------------------------------------ | :-------------------- |
 * | Init | 0   | 0     | 1     | ""      | c = '('. Only choice is Keep (since rem_l == 0)         | {}                    |
 * | 1    | 1   | 0     | 1     | "("     | c = ')'. Try Remove: backtrack(2, 0, 0, "(")            |                       |
 * | 2    | 2   | 0     | 0     | "("     | rem_l==0, rem_r==0. suffix from 2 is ")()()". Check "()()()". Valid!| {"()()()"} |
 * | 3    | 1   | 0     | 1     | "("     | Try Keep: backtrack(2, 0, 1, "()")                      | {"()()()"}            |
 * | 4    | 2   | 0     | 1     | "()"    | c = '('. Only choice is Keep                            |                       |
 * | 5    | 3   | 0     | 1     | "()("   | c = ')'. Try Remove: backtrack(4, 0, 0, "()(")          |                       |
 * | 6    | 4   | 0     | 0     | "()("   | rem_l==0, rem_r==0. suffix from 4 is ")()". Check "(())()". Valid!  | {"()()()", "(())()"}  |
 * 
 * Resulting vector: {"()()()", "(())()"}
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine you are editing a manuscript with unmatched parentheses. 
 * You first count exactly how many redundant '(' and ')' exist. 
 * You walk through the text character by character. 
 * If you see an unmatched symbol, you can choose to cross it out (if you still have quota to remove it) 
 * or keep it. Once you run out of deletion quota, you check if the rest of the text reads properly.
 * 
 * 1-MINUTE QUICK REVISION:
 * - First pass: Count minimum invalid left (`rem_l`) and right (`rem_r`) parentheses to remove.
 * - Backtracking takes `idx`, `rem_l`, `rem_r`, and the constructed string.
 * - If `rem_l == 0 && rem_r == 0`, append the rest of the string, check if it's valid, and save to a set.
 * - If `s[idx] == '('` and `rem_l > 0`, recurse by removing it (decrement `rem_l`).
 * - If `s[idx] == ')'` and `rem_r > 0`, recurse by removing it (decrement `rem_r`).
 * - Always try to keep the character by appending it and recursing.
 * - Time Complexity: O(2^N) in the worst case (pruned search space).
 * - Space Complexity: O(N) recursion stack.
 */
