/*
 * QUESTION: Word Break Problem using Backtracking (Word Break II)
 * Link: https://practice.geeksforgeeks.org/problems/word-break-part-2/0
 * 
 * Input: s = "catsanddog", dict = {"cat", "cats", "and", "sand", "dog"}
 * Output: {"cats and dog", "cat sand dog"}
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

// Helper backtracking function to build sentences starting at index `start`
void solveWordBreak(int start, const std::string& s, const std::unordered_set<std::string>& dict,
                     std::vector<std::string>& current_words, std::vector<std::string>& result) {
    int n = s.length();
    
    // Base Case: Reached the end of the string
    if (start == n) {
        // Construct the sentence from the list of words
        std::string sentence = "";
        for (size_t i = 0; i < current_words.size(); i++) {
            sentence += current_words[i];
            if (i < current_words.size() - 1) {
                sentence += " ";
            }
        }
        result.push_back(sentence);
        return;
    }
    
    // Check all prefixes of s[start...n-1]
    for (int end = start + 1; end <= n; end++) {
        std::string word = s.substr(start, end - start);
        
        // If the prefix is in the dictionary, recurse on the remainder
        if (dict.find(word) != dict.end()) {
            current_words.push_back(word);
            
            solveWordBreak(end, s, dict, current_words, result);
            
            // Backtrack: Remove the last added word
            current_words.pop_back();
        }
    }
}

// Main function to return all possible sentences
std::vector<std::string> wordBreak(const std::string& s, const std::vector<std::string>& dict) {
    std::unordered_set<std::string> dict_set(dict.begin(), dict.end());
    std::vector<std::string> result;
    std::vector<std::string> current_words;
    
    solveWordBreak(0, s, dict_set, current_words, result);
    
    return result;
}

/*
 * DRY RUN (s = "catsanddog", dict = {"cat", "cats", "and", "sand", "dog"}):
 * 
 * | Step | start | end | Substring Checked | In Dict? | current_words State | Recursion Next start / Action |
 * | :--- | :---- | :-- | :---------------- | :------- | :------------------ | :---------------------------- |
 * | Init | 0     | -   | -                 | -        | {}                  | Start loop                    |
 * | 1    | 0     | 3   | "cat"             | Yes      | {"cat"}             | Recurse at start = 3          |
 * | 2    | 3     | 7   | "sand"            | Yes      | {"cat", "sand"}     | Recurse at start = 7          |
 * | 3    | 7     | 10  | "dog"             | Yes      | {"cat","sand","dog"}| start == n -> Result: "cat sand dog"|
 * | 4    | 7     | -   | (loops end)       | -        | {"cat", "sand"}     | Backtrack -> pop "dog"        |
 * | 5    | 3     | -   | (loops end)       | -        | {"cat"}             | Backtrack -> pop "sand"        |
 * | 6    | 0     | 4   | "cats"            | Yes      | {"cats"}            | Recurse at start = 4          |
 * | 7    | 4     | 7   | "and"             | Yes      | {"cats", "and"}     | Recurse at start = 7          |
 * | 8    | 7     | 10  | "dog"             | Yes      | {"cats","and","dog"}| start == n -> Result: "cats and dog"|
 * 
 * Final Result: {"cat sand dog", "cats and dog"}
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine reading a long banner of letters with no spaces. 
 * You slice off a piece from the beginning. 
 * If it matches a word in your dictionary, you write it down on your notepad, 
 * and ask a friend to read the rest of the banner. 
 * If your friend succeeds and reads to the end, you've spelled out a full sentence. 
 * Then you erase the word from your notepad (backtrack) and try cutting at a different length.
 * 
 * 1-MINUTE QUICK REVISION:
 * - Load the dictionary list into an `unordered_set` for O(1) lookup.
 * - Recursively test every prefix `s[start...end-1]`.
 * - If the prefix is in the dictionary, push it to `current_words` and recurse with `start = end`.
 * - Backtrack: Pop the prefix from `current_words`.
 * - Base Case: When `start == n`, join `current_words` with spaces and save to results.
 * - Time Complexity: O(2^N) in the worst case (e.g., s = "aaaa", dict = {"a", "aa", "aaa"}).
 * - Space Complexity: O(N^2) stack memory + dictionary copy.
 */
