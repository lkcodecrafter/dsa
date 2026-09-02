/*
    QUESTION    : A Program to check if strings are rotations of each other or not
    Company Tags: Amazon, Microsoft, Adobe
    GfG Link    : https://www.geeksforgeeks.org/a-program-to-check-if-strings-are-rotations-of-each-other/
    LeetCode    : https://leetcode.com/problems/rotate-string/
*/

#include <iostream>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Substring search in concatenated string (s1 + s1)
// S.C : O(N) - Concatenated string storage
class Solution {
public:
    bool areRotations(string s1, string s2) {
        if (s1.length() != s2.length()) {
            return false;
        }

        // s2 is a rotation of s1 if and only if s2 is a substring of (s1 + s1)
        string temp = s1 + s1;
        return temp.find(s2) != string::npos;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `if (s1.length() != s2.length()) return false;`
 * - `return (s1 + s1).find(s2) != string::npos;`
 * - Time: O(N), Space: O(N).
 */
