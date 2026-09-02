/*
    QUESTION    : Find shortest unique prefix for every word in a given list
    Company Tags: Google, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/find-all-shortest-unique-prefixes-to-represent-each-word-in-a-given-list/
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * L) - N words of max length L: insert all words into Trie + prefix query for each word
// S.C : O(N * L * 26) - Trie memory allocation
struct TrieNode {
    TrieNode* children[26];
    int frequency; // Tracks how many words pass through this node

    TrieNode() {
        frequency = 0;
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
            crawl->frequency++; // Increment frequency of words passing through this node
        }
    }

    string getUniquePrefix(const string &word) {
        TrieNode* crawl = root;
        string prefix = "";

        for (char ch : word) {
            int idx = ch - 'a';
            prefix.push_back(ch);
            crawl = crawl->children[idx];

            // If frequency is 1, this prefix uniquely identifies the word!
            if (crawl->frequency == 1) {
                break;
            }
        }
        return prefix;
    }

public:
    vector<string> findPrefixes(string arr[], int n) {
        root = new TrieNode();
        vector<string> result;

        // Step 1: Insert all words into the Trie
        for (int i = 0; i < n; i++) {
            insert(arr[i]);
        }

        // Step 2: Find the shortest unique prefix for each word
        for (int i = 0; i < n; i++) {
            result.push_back(getUniquePrefix(arr[i]));
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF FREQUENCY TRACKING IN TRIE
 * ============================================================================
 *
 * Words: ["zebra", "dog", "duck", "dove"]
 *
 *              (Root)
 *             /      \
 *          'z'(1)    'd'(3)
 *            |         |
 *          'e'(1)*   'o'(2)   'u'(1)
 *                     /   \      |
 *                   'g'(1)* 'v'(1)* 'c'(1)*
 *
 * Prefix queries:
 * - "zebra": 'z' has freq=1 -> Unique prefix = "z"
 * - "dog"  : 'd'(3) -> 'o'(2) -> 'g'(1) -> Unique prefix = "dog"
 * - "dove" : 'd'(3) -> 'o'(2) -> 'v'(1) -> Unique prefix = "dov"
 * - "duck" : 'd'(3) -> 'u'(1) -> Unique prefix = "du"
 *
 * Output: ["z", "dog", "du", "dov"]
 *
 * ============================================================================
 * DRY RUN (arr = {"zebra", "dog", "duck", "dove"})
 * ============================================================================
 * | Word   | Traversal & Node Frequencies         | Stop Condition (Freq == 1) | Output Prefix |
 * | :----- | :----------------------------------- | :------------------------- | :------------ |
 * | "zebra"| 'z' (freq = 1)                       | Immediate stop at 'z'      | "z"           |
 * | "dog"  | 'd' (freq = 3), 'o' (2), 'g' (1)     | Stop at 'g'                | "dog"         |
 * | "duck" | 'd' (freq = 3), 'u' (1)              | Stop at 'u'                | "du"          |
 * | "dove" | 'd' (freq = 3), 'o' (2), 'v' (1)     | Stop at 'v'                | "dov"         |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Footstep Counter"
 * Every time a word is walked down the Trie, it leaves a footprint counter (`frequency++`).
 * When searching for a unique nickname, walk the path until you reach a room with
 * only 1 footprint (`frequency == 1`). That sub-path is your shortest unique prefix!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Augment `TrieNode` with an integer `frequency` field.
 * - During `insert()`, increment `crawl->frequency++` on every visited node.
 * - During query, traverse characters and stop as soon as `crawl->frequency == 1`.
 * - Time: O(N * L), Space: O(N * L * 26).
 */
