/*
    QUESTION    : KMP Algorithm for Pattern Searching (Longest Prefix Suffix / LPS array)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/longest-prefix-suffix2527/1
    LeetCode    : https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N + M) - Knuth-Morris-Pratt avoids redundant re-comparisons using LPS preprocessing
// S.C : O(M)     - LPS array
class Solution {
private:
    vector<int> computeLPS(string pat) {
        int m = pat.length();
        vector<int> lps(m, 0);
        int len = 0; // Length of previous longest prefix suffix
        int i = 1;

        while (i < m) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1]; // Fall back without incrementing i
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        return lps;
    }

public:
    int lps(string s) {
        vector<int> lpsArr = computeLPS(s);
        return lpsArr.back();
    }

    vector<int> search(string pat, string txt) {
        vector<int> result;
        int m = pat.length();
        int n = txt.length();

        vector<int> lps = computeLPS(pat);

        int i = 0; // Index for txt
        int j = 0; // Index for pat

        while (i < n) {
            if (pat[j] == txt[i]) {
                i++;
                j++;
            }

            if (j == m) {
                result.push_back(i - j + 1); // 1-based match index
                j = lps[j - 1];
            } else if (i < n && pat[j] != txt[i]) {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - LPS Array: `if (pat[i] == pat[len]) { lps[i++] = ++len; } else if (len != 0) { len = lps[len-1]; } else { lps[i++] = 0; }`
 * - Search: On mismatch, `j = (j != 0) ? lps[j-1] : (i++, 0);`
 * - Time: O(N + M), Space: O(M).
 */
