/*
    QUESTION    : Permutations of a given string
    Company Tags: Amazon, Microsoft, Adobe, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/permutations-of-a-given-string2041/1
    LeetCode    : https://leetcode.com/problems/permutations/
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N! * N) - Backtracking permutation generation with duplicate skipping
// S.C : O(N)      - Recursion stack depth
class Solution {
private:
    void permute(int index, string s, vector<string>& result) {
        if (index == s.length()) {
            result.push_back(s);
            return;
        }

        unordered_set<char> seen;

        for (int i = index; i < s.length(); i++) {
            if (seen.find(s[i]) != seen.end()) continue; // Skip duplicate characters at this position
            seen.insert(s[i]);

            swap(s[index], s[i]);
            permute(index + 1, s, result);
            swap(s[index], s[i]); // Backtrack
        }
    }

public:
    vector<string> find_permutation(string S) {
        vector<string> result;
        permute(0, S, result);
        sort(result.begin(), result.end()); // Return in lexicographical order
        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `for (int i = index; i < n; i++)`:
 *     - If `seen.count(s[i])` continue;
 *     - `swap(s[index], s[i]); permute(index + 1); swap(s[index], s[i]);`
 * - Time: O(N! * N), Space: O(N).
 */
