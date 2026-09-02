/*
    QUESTION    : Minimum characters to be added at front to make string palindrome
    Company Tags: Amazon, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/minimum-characters-to-be-added-at-front-to-make-string-palindrome/1
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - KMP LPS array on concatenated string (s + "$" + rev_s)
// S.C : O(N) - LPS array
class Solution {
private:
    vector<int> computeLPS(const string& str) {
        int n = str.length();
        vector<int> lps(n, 0);
        int len = 0;
        int i = 1;

        while (i < n) {
            if (str[i] == str[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }

        return lps;
    }

public:
    int minChar(string str) {
        string revStr = str;
        reverse(revStr.begin(), revStr.end());

        // Concat: str + "$" + revStr
        string concat = str + "$" + revStr;

        // Longest palindromic prefix is given by LPS value of last character
        vector<int> lps = computeLPS(concat);

        return str.length() - lps.back();
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `concat = str + "$" + rev(str)`.
 * - `lps = computeLPS(concat)`.
 * - Result = `str.length() - lps.back()`.
 * - Time: O(N), Space: O(N).
 */
