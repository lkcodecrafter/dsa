/*
    QUESTION    : Implement a Phone Directory (Display contacts matching each prefix character typed)
    Company Tags: Amazon, Microsoft, Snapdeal
    GfG Link    : https://practice.geeksforgeeks.org/problems/phone-directory/0
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(|query_str| * N * L) - DFS prefix matching for each character typed in query string
// S.C : O(N * L * 26)          - Trie node allocations
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

    void insert(const string &contact) {
        TrieNode* crawl = root;
        for (char ch : contact) {
            int idx = ch - 'a';
            if (crawl->children[idx] == nullptr) {
                crawl->children[idx] = new TrieNode();
            }
            crawl = crawl->children[idx];
        }
        crawl->isEndOfWord = true;
    }

    // Helper DFS to collect all contact words starting from `node` with prefix `prefix`
    void displayContactsUtil(TrieNode* node, string &prefix, vector<string> &suggestions) {
        if (node->isEndOfWord) {
            suggestions.push_back(prefix);
        }

        for (char ch = 'a'; ch <= 'z'; ch++) {
            int idx = ch - 'a';
            if (node->children[idx] != nullptr) {
                prefix.push_back(ch);
                displayContactsUtil(node->children[idx], prefix, suggestions);
                prefix.pop_back(); // Backtrack
            }
        }
    }

public:
    vector<vector<string>> displayContacts(int n, string contact[], string s) {
        root = new TrieNode();

        // 1. Insert all unique contacts into the Trie
        for (int i = 0; i < n; i++) {
            insert(contact[i]);
        }

        vector<vector<string>> result;
        TrieNode* prevNode = root;
        string prefix = "";
        bool noMatchFound = false;

        // 2. Query prefix character by character
        for (char ch : s) {
            prefix.push_back(ch);
            int idx = ch - 'a';

            // If a previous prefix had no match or current char path is null
            if (noMatchFound || prevNode->children[idx] == nullptr) {
                noMatchFound = true;
                result.push_back({"0"}); // Standard GFG output for no suggestions
                continue;
            }

            TrieNode* currNode = prevNode->children[idx];
            vector<string> suggestions;
            string tempPrefix = prefix;

            displayContactsUtil(currNode, tempPrefix, suggestions);
            result.push_back(suggestions);

            prevNode = currNode;
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF PHONE DIRECTORY AUTOCOMPLETE
 * ============================================================================
 *
 * Contacts: ["geeikistest", "geeksforgeeks", "geeksfortest"]
 * Query String s = "gee"
 *
 * Keystroke 1: 'g'
 *   Prefix: "g" -> Matches all 3: ["geeikistest", "geeksforgeeks", "geeksfortest"]
 * Keystroke 2: 'e'
 *   Prefix: "ge" -> Matches all 3: ["geeikistest", "geeksforgeeks", "geeksfortest"]
 * Keystroke 3: 'e'
 *   Prefix: "gee" -> Matches all 3: ["geeikistest", "geeksforgeeks", "geeksfortest"]
 * If Keystroke 4: 'k'
 *   Prefix: "geek" -> Matches 2: ["geeksforgeeks", "geeksfortest"]
 *
 * ============================================================================
 * DRY RUN (contact = {"code", "coder", "coding"}, s = "cod")
 * ============================================================================
 * | Char Typed | Prefix | Matched Trie Subtree | Suggestions Found in Order     |
 * | :--------- | :----- | :------------------- | :----------------------------- |
 * | 'c'        | "c"    | Node 'c'             | {"code", "coder", "coding"}    |
 * | 'o'        | "co"   | Node 'o'             | {"code", "coder", "coding"}    |
 * | 'd'        | "cod"  | Node 'd'             | {"code", "coder", "coding"}    |
 *
 * Result: { {"code","coder","coding"}, {"code","coder","coding"}, {"code","coder","coding"} }
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Search Bar Dropdown"
 * Every keystroke advances your cursor one level deeper into the Trie.
 * From that cursor, a quick DFS sweeps through all alphabetical branches
 * to collect every valid contact name in sorted order.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Insert contacts into Trie.
 * - For each character in query `s`:
 *     - Advance `currNode = prevNode->children[ch - 'a']`.
 *     - If `currNode == nullptr`, output `{"0"}` for this and subsequent chars.
 *     - Run DFS `displayContactsUtil()` from `currNode` from 'a' to 'z' to get sorted suggestions.
 * - Time: O(|s| * N * L), Space: O(N * L * 26).
 */
