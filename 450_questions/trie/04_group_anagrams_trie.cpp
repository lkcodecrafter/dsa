/*
    QUESTION    : Given a sequence of words, print all anagrams together (Group Anagrams)
    Company Tags: Amazon, Microsoft, Snapdeal, Goldman Sachs
    GfG Link    : https://practice.geeksforgeeks.org/problems/k-anagrams-1/0
    LeetCode    : https://leetcode.com/problems/group-anagrams/
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * K log K) where N is number of words and K is maximum word length
// S.C : O(N * K)       - Hash map storage of grouped anagrams
class Solution {
public:
    vector<vector<string>> Anagrams(vector<string> &string_list) {
        vector<vector<string>> result;
        // Map canonical sorted key -> list of original anagram words
        unordered_map<string, vector<string>> mp;

        for (const string &str : string_list) {
            string sortedKey = str;
            sort(sortedKey.begin(), sortedKey.end()); // Anagrams share identical sorted signatures
            mp[sortedKey].push_back(str);
        }

        for (auto &pair : mp) {
            result.push_back(pair.second);
        }

        return result;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF ANAGRAM CANONICAL GROUPING
 * ============================================================================
 *
 * Words: ["act", "god", "cat", "dog", "tac"]
 *
 * Word      Sorted Key       Group Bucket in Hash Map
 * ----------------------------------------------------
 * "act"  -> "act"        -> mp["act"] = ["act"]
 * "god"  -> "dgo"        -> mp["dgo"] = ["god"]
 * "cat"  -> "act"        -> mp["act"] = ["act", "cat"]
 * "dog"  -> "dgo"        -> mp["dgo"] = ["god", "dog"]
 * "tac"  -> "act"        -> mp["act"] = ["act", "cat", "tac"]
 *
 * Result: [ ["act", "cat", "tac"], ["god", "dog"] ]
 *
 * ============================================================================
 * DRY RUN (string_list = {"eat", "tea", "tan", "ate", "nat", "bat"})
 * ============================================================================
 * | Word  | Sorted Key | Hash Map Group Bucket Content                  |
 * | :---- | :--------- | :--------------------------------------------- |
 * | "eat" | "aet"      | mp["aet"] = {"eat"}                            |
 * | "tea" | "aet"      | mp["aet"] = {"eat", "tea"}                     |
 * | "tan" | "ant"      | mp["ant"] = {"tan"}                            |
 * | "ate" | "aet"      | mp["aet"] = {"eat", "tea", "ate"}              |
 * | "nat" | "ant"      | mp["ant"] = {"tan", "nat"}                     |
 * | "bat" | "abt"      | mp["abt"] = {"bat"}                            |
 *
 * Result: {{"eat","tea","ate"}, {"tan","nat"}, {"bat"}}
 *
 * ============================================================================
 * MEMORIZATION / RECALL SCENARIO
 * ============================================================================
 * Scenario: "The Alphabetical Nametag"
 * Sort the letters of each word to create its standard identity nametag (e.g. `god` -> `dgo`).
 * Toss all words sharing the exact same nametag into the same bucket.
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Anagrams have the exact same character frequencies and sorted representations.
 * - Sort each word: `key = sort(word)`.
 * - Insert into `unordered_map<string, vector<string>> mp`.
 * - Collect all values `mp[key]` into the final result.
 * - Time: O(N * K log K), Space: O(N * K).
 */
