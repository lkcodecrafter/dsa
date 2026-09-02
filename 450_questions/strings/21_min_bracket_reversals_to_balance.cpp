/*
    QUESTION    : Count the Reversals (Minimum bracket reversals to make expression balanced)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/count-the-reversals0401/1
*/

#include <iostream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear scan counting unmatched open and close braces
// S.C : O(1) - Two counter variables
class Solution {
public:
    int countRev(string s) {
        int n = s.length();
        if (n % 2 != 0) return -1; // Odd length can never be balanced

        int open = 0;
        int close = 0;

        for (char ch : s) {
            if (ch == '{') {
                open++;
            } else {
                if (open > 0) {
                    open--; // Match with existing open brace
                } else {
                    close++; // Unmatched close brace
                }
            }
        }

        // Formula: ceil(open / 2) + ceil(close / 2) = (open + 1)/2 + (close + 1)/2
        return (open + 1) / 2 + (close + 1) / 2;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If odd length $\rightarrow$ `-1`.
 * - Count unmatched `open` and `close`.
 * - Total reversals = `(open + 1) / 2 + (close + 1) / 2`.
 * - Time: O(N), Space: O(1).
 */
