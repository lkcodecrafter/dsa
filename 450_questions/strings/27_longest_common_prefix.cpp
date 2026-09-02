/*
    QUESTION    : Longest Common Prefix in an Array
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-common-prefix-in-an-array5129/1
    LeetCode    : https://leetcode.com/problems/longest-common-prefix/
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * min_len) - Character-by-character vertical scanning
// S.C : O(1)           - Constant auxiliary space
class Solution {
public:
    string longestCommonPrefix(string arr[], int N) {
        if (N == 0) return "-1";
        if (N == 1) return arr[0];

        string prefix = arr[0];

        for (int i = 1; i < N; i++) {
            while (arr[i].find(prefix) != 0) {
                prefix = prefix.substr(0, prefix.length() - 1);
                if (prefix.empty()) {
                    return "-1";
                }
            }
        }

        return prefix;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `prefix = arr[0]`.
 * - While `arr[i].find(prefix) != 0`: `prefix.pop_back()`.
 * - If `prefix.empty()` return "-1".
 * - Time: O(N * L), Space: O(1).
 */
