/*
    QUESTION    : Construct a Trie from scratch (Insert, Search, StartsWith)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://www.geeksforgeeks.org/trie-insert-and-search/
    LeetCode    : https://leetcode.com/problems/implement-trie-prefix-tree/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : Insert: O(L), Search: O(L), StartsWith: O(L) where L is the length of the word
// S.C : O(N * L * 26) - Trie node allocations
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

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie
    void insert(string word) {
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

    // Returns true if the word is in the trie
    bool search(string word) {
        TrieNode* crawl = root;
        for (char ch : word) {
            int idx = ch - 'a';
            if (crawl->children[idx] == nullptr) {
                return false;
            }
            crawl = crawl->children[idx];
        }
        return crawl != nullptr && crawl->isEndOfWord;
    }

    // Returns true if there is any word in the trie that starts with the given prefix
    bool startsWith(string prefix) {
        TrieNode* crawl = root;
        for (char ch : prefix) {
            int idx = ch - 'a';
            if (crawl->children[idx] == nullptr) {
                return false;
            }
            crawl = crawl->children[idx];
        }
        return crawl != nullptr;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF TRIE STRUCTURE
 * ============================================================================
 *
 * Inserted: "cat", "car", "dog"
 *
 *               (Root)
 *              /      \
 *            'c'      'd'
 *            /          \
 *          'a'          'o'
 *          / \            \
 *        't'* 'r'*        'g'*
 *
 * '*' indicates isEndOfWord = true.
 *
 * ============================================================================
 * DRY RUN
 * ============================================================================
 * | Operation            | Input   | Traversal Path    | isEndOfWord Check | Output |
 * | :------------------- | :------ | :---------------- | :---------------- | :----- |
 * | insert("cat")        | "cat"   | Root->c->a->t     | Sets t->isEnd=true| -      |
 * | insert("car")        | "car"   | Root->c->a->r     | Sets r->isEnd=true| -      |
 * | search("cat")        | "cat"   | Root->c->a->t     | t->isEnd == true  | true   |
 * | search("ca")         | "ca"    | Root->c->a        | a->isEnd == false | false  |
 * | startsWith("ca")     | "ca"    | Root->c->a        | Valid path exists | true   |
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The 26-Door Tree Hallway"
 * Each room has 26 doors labeled 'a' to 'z'.
 * To write a word, you walk down the matching letter doors, building rooms as needed,
 * and stamp the final room with a gold flag (`isEndOfWord = true`).
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `TrieNode` has `children[26]` and boolean `isEndOfWord`.
 * - Insert / Search traverses character-by-character: index = `ch - 'a'`.
 * - Search requires matching full path AND `crawl->isEndOfWord == true`.
 * - StartsWith only requires the prefix path to exist (`crawl != nullptr`).
 * - Time: O(L) for all operations, Space: O(Alphabet_Size * L * N).
 */
