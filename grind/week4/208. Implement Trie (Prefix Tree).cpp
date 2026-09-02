#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
 * Problem: Implement Trie (Prefix Tree) (LeetCode 208)
 * Implement a trie with insert, search, and startsWith methods.
 *
 * Pattern: Trie / Prefix Tree / Tree Traversal
 *
 * Complexity:
 * - Time Complexity:
 *   - insert(word): O(L) where L is the length of the word. We traverse or create L nodes.
 *   - search(word): O(L) where L is the length of the word. We traverse at most L nodes.
 *   - startsWith(prefix): O(L) where L is the length of the prefix. We traverse at most L nodes.
 * - Space Complexity:
 *   - Worst case: O(N * L * 26) where N is the number of inserted words, L is the maximum length of a word.
 *   - Auxiliary space: O(1) for search and startsWith operations.
 *
 * Visualizations:
 * Trie containing "cat" and "car":
 *
 *          [root]
 *             | 'c'
 *           [node]
 *             | 'a'
 *           [node]
 *          /      \
 *     't' /        \ 'r'
 *      [node]     [node]
 *    (eow=true)  (eow=true)
 *
 * Memorization Hook:
 * "Trie node holds an array of 26 child pointers and a boolean 'eow' (End of Word).
 * Insertion allocates nodes along character path; search expects path existence + eow; 
 * startsWith just expects path existence."
 *
 * 1-Minute Quick Revision:
 * 1. Define children array `Trie* children[26]` (initialized to nullptr) and bool `eow` (initialized to false).
 * 2. `insert(word)`: Loop each character `c` of word. If `node->children[c-'a']` is nullptr, create a new Trie node. Move `node = node->children[c-'a']`. Set `node->eow = true` at the end.
 * 3. `search(word)`: Loop each character. If `node->children[c-'a']` is nullptr, return false. Otherwise move. Return `node->eow`.
 * 4. `startsWith(prefix)`: Loop each character. If `node->children[c-'a']` is nullptr, return false. Otherwise move. Return true.
 *
 * Dry Run:
 * Operations: insert("cat"), search("cat"), search("ca"), startsWith("ca")
 *
 * | Operation        | Argument | Characters Checked | Trie Path & Nodes Found / Created | Final Result / End of Word State |
 * |------------------|----------|--------------------|-----------------------------------|----------------------------------|
 * | insert("cat")    | "cat"    | 'c', 'a', 't'      | Creates new nodes for 'c', 'a', 't'| Marks node 't' -> eow = true     |
 * | search("cat")    | "cat"    | 'c', 'a', 't'      | Traverses node 'c' -> 'a' -> 't'  | Returns t->eow (true)            |
 * | search("ca")     | "ca"     | 'c', 'a'           | Traverses node 'c' -> 'a'         | Returns a->eow (false)           |
 * | startsWith("ca") | "ca"     | 'c', 'a'           | Traverses node 'c' -> 'a'         | Returns true (path exists)       |
 */
class Trie {
private:
    Trie* children[26];
    bool eow; // End of word marker

public:
    // Initialize the Trie node
    Trie() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        eow = false;   
    }
    
    // Inserts a word into the trie
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            int index = c - 'a';
            // Create a new trie node if it doesn't exist for the current character
            if (node->children[index] == nullptr) {
                node->children[index] = new Trie();
            }
            node = node->children[index]; // Move to the child node
        }
        node->eow = true; // Mark the end of the word
    }
    
    // Returns if the word is in the trie
    bool search(string word) {
        Trie* node = this;
        for (char c : word) {
            int index = c - 'a';
            // Character path doesn't exist
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index]; // Move to the child node
        }
        return node->eow; // Return if it's the exact end of a word
    }
    
    // Returns if there is any word in the trie that starts with the given prefix
    bool startsWith(string prefix) {
        Trie* node = this;
        for (char c : prefix) {
            int index = c - 'a';
            // Prefix character path doesn't exist
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index]; // Move to the child node
        }
        return true; // We successfully traversed the prefix path
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */