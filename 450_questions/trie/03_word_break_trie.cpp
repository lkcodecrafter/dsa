/*
    QUESTION    : Word Break Problem (Trie solution)
    Company Tags: Amazon, Microsoft, Google, Facebook
    GfG Link    : https://www.geeksforgeeks.org/word-break-problem-trie-solution/
    LeetCode    : https://leetcode.com/problems/word-break/
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) where N is length of string s (with memoization / DP)
// S.C : O(Dictionary Words Length * 26 + N) - Trie nodes and DP memo table
struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};

class Solution {
private:
    TrieNode* root;

    void insert(const string &word) {
        TrieNode* crawl = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (crawl->children[idx] == nullptr) {
                crawl->children[idx] = new TrieNode();
            }
            crawl = crawl->children[idx];
        }
        crawl->isEndOfWord = true;
    }

    // Helper function to check if suffix s[start...n-1] can be segmented
    bool canBreak(int start, const string &s, vector<int> &memo) {
        int n = s.length();
        if (start == n) return true; // Successfully matched to the end!

        if (memo[start] != -1) return memo[start];

        TrieNode* crawl = root;

        // Traverse the Trie character by character starting from index `start`
        for (int i = start; i < n; i++) {
            int idx = s[i] - 'a';
            if (crawl->children[idx] == nullptr) {
                break; // Prefix does not exist in dictionary
            }
            crawl = crawl->children[idx];

            // If a valid word ending is found, recursively check remainder of string
            if (crawl->isEndOfWord && canBreak(i + 1, s, memo)) {
                return memo[start] = 1;
            }
        }

        return memo[start] = 0;
    }

public:
    int wordBreak(string A, vector<string> &B) {
        root = new TrieNode();

        // 1. Build the Trie with all dictionary words
        for (const string &word : B) {
            insert(word);
        }

        // 2. Use memoized Trie traversal on string A
        vector<int> memo(A.length(), -1);
        return canBreak(0, A, memo) ? 1 : 0;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TRIE + DP WORD BREAK
 * ============================================================================
 *
 * String A = "leetcode", Dictionary B = ["leet", "code"]
 *
 * Trie:
 * Root -> 'l'->'e'->'e'->'t'*
 *      -> 'c'->'o'->'d'->'e'*
 *
 * Traversal:
 * Start = 0: Crawl 'l','e','e','t'. At 't' (idx=3), isEndOfWord=true!
 *   Recurse on start = 4:
 *     Crawl 'c','o','d','e'. At 'e' (idx=7), isEndOfWord=true!
 *       Recurse on start = 8 == length (Base Case -> True!)
 *
 * Returns 1 (True).
 *
 * ============================================================================
 * DRY RUN (A = "catsandog", B = {"cats", "dog", "sand", "and", "cat"})
 * ============================================================================
 * | start | Crawl Characters | Matched Word | Recurse Next start | Suffix Status | memo[start] |
 * | :---- | :--------------- | :----------- | :----------------- | :------------ | :---------- |
 * | 0     | 'c','a','t'      | "cat"        | canBreak(3)        | Fails         | -           |
 * | 0     | 'c','a','t','s'  | "cats"       | canBreak(4)        | "andog" Fails | -           |
 * | 4     | 'a','n','d'      | "and"        | canBreak(7)        | "og" not in B | 0           |
 * | 0     | (All fail)       | -            | -                  | Fails         | 0           |
 *
 * Result = 0 (False).
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Word Compass"
 * As you read characters left-to-right, the Trie acts like a live spellchecker compass.
 * Whenever you complete a recognized word (`isEndOfWord`), bookmark that spot (`memo`)
 * and attempt to read the next word.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Insert all dictionary words into a Trie.
 * - For index `start`, crawl characters down the Trie:
 *     - If `crawl->isEndOfWord == true`, recursively check `canBreak(i + 1)`.
 *     - If `crawl->children[idx] == nullptr`, break loop.
 * - Use a 1D `memo` table of size $N$ initialized to $-1$ to avoid recomputing visited starting indices.
 * - Time: O(N^2), Space: O(Dictionary Size + N).
 */
