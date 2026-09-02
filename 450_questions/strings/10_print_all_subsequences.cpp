/*
    QUESTION    : Print all Subsequences of a string (Power Set)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/print-subsequences-string/
    LeetCode    : https://leetcode.com/problems/subsets/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(2^N) - Backtracking include/exclude decisions generate all 2^N subsequences
// S.C : O(N)   - Recursion stack depth
class Solution {
private:
    void generateSubsequences(int index, const string& s, string& current, vector<string>& result) {
        if (index == s.length()) {
            if (!current.empty()) {
                result.push_back(current);
            }
            return;
        }

        // Choice 1: Include current character
        current.push_back(s[index]);
        generateSubsequences(index + 1, s, current, result);

        // Backtrack
        current.pop_back();

        // Choice 2: Exclude current character
        generateSubsequences(index + 1, s, current, result);
    }

public:
    vector<string> AllSubsequences(string s) {
        vector<string> result;
        string current = "";
        generateSubsequences(0, s, current, result);
        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Choice 1: `current.push_back(s[i]); recurse(i+1); current.pop_back();`
 * - Choice 2: `recurse(i+1);`
 * - Time: O(2^N), Space: O(N).
 */
