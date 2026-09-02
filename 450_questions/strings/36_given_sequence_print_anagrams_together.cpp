/*
    QUESTION    : Print Anagrams Together (Group Anagrams)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    GfG Link    : https://practice.geeksforgeeks.org/problems/print-anagrams-together/1
    LeetCode    : https://leetcode.com/problems/group-anagrams/
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * K log K) where K is string length
// S.C : O(N * K)       - Hash map storing anagram groups
class Solution {
public:
    vector<vector<string>> Anagrams(vector<string>& string_list) {
        unordered_map<string, vector<string>> anagramGroups;

        // Group strings by their sorted canonical representation
        for (const string& s : string_list) {
            string key = s;
            sort(key.begin(), key.end());
            anagramGroups[key].push_back(s);
        }

        vector<vector<string>> result;
        for (auto& entry : anagramGroups) {
            result.push_back(entry.second);
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `key = s; sort(key); anagramGroups[key].push_back(s);`
 * - Collect values of `unordered_map<string, vector<string>>`.
 * - Time: O(N * K log K), Space: O(N * K).
 */
