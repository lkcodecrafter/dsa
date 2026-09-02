/*
    QUESTION    : Recursively remove all adjacent duplicates
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/consecutive-elements2306/1
*/

#include <iostream>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear single pass string filtering
// S.C : O(1) - Result string buffer
class Solution {
public:
    string removeConsecutiveCharacter(string S) {
        if (S.empty()) return "";

        string result = "";
        result += S[0];

        for (int i = 1; i < S.length(); i++) {
            if (S[i] != S[i - 1]) {
                result += S[i];
            }
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `result += S[0]`.
 * - If `S[i] != S[i-1]`: `result += S[i]`.
 * - Time: O(N), Space: O(1).
 */
