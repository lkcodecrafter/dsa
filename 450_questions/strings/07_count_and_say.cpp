/*
    QUESTION    : Count and Say Problem (Look-and-Say Sequence)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/decode-the-pattern1138/1
    LeetCode    : https://leetcode.com/problems/count-and-say/
*/

#include <iostream>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N * L) where L is length of intermediate string
// S.C : O(L)     - Temporary string buffer
class Solution {
public:
    string lookandsay(int n) {
        if (n == 1) return "1";

        string result = "1";

        for (int i = 2; i <= n; i++) {
            string current = "";
            int count = 1;

            for (int j = 1; j < result.length(); j++) {
                if (result[j] == result[j - 1]) {
                    count++;
                } else {
                    current += to_string(count) + result[j - 1];
                    count = 1;
                }
            }

            current += to_string(count) + result.back();
            result = current;
        }

        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `result = "1"`.
 * - For step 2 to `n`: count contiguous runs of identical digits and append `to_string(count) + digit`.
 * - Time: O(N * L), Space: O(L).
 */
