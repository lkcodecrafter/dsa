/*
    QUESTION    : Split the binary string into substrings with equal number of 0s and 1s
    Company Tags: Amazon
    GfG Link    : https://practice.geeksforgeeks.org/problems/split-the-binary-string-into-substrings-with-equal-number-of-0s-and-1s/1
*/

#include <iostream>
#include <string>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear greedy count of 0s and 1s
// S.C : O(1) - Constant auxiliary space
class Solution {
public:
    int maxSubStr(string str) {
        int count0 = 0;
        int count1 = 0;
        int splits = 0;

        for (char ch : str) {
            if (ch == '0') count0++;
            else count1++;

            // Whenever count of 0s and 1s becomes equal, a valid partition is formed
            if (count0 == count1) {
                splits++;
            }
        }

        // If total count of 0s and 1s was not equal across the entire string
        if (count0 != count1) {
            return -1;
        }

        return splits;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `count0++` on '0', `count1++` on '1'.
 * - If `count0 == count1`, `splits++`.
 * - If `count0 != count1` at end, return -1.
 * - Time: O(N), Space: O(1).
 */
