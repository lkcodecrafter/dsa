/*
    QUESTION    : Length of the Longest Valid Substring of Parentheses
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/valid-substring0624/1
    LeetCode    : https://leetcode.com/problems/longest-valid-parentheses/
*/

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Single pass through string
// S.C : O(N) - Stack storing indices
class Solution {
public:
    int findMaxLen(string s) {
        stack<int> st;
        st.push(-1); // Base index for length calculation

        int maxLen = 0;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();

                if (st.empty()) {
                    // Current closing bracket has no match; serves as new base index
                    st.push(i);
                } else {
                    // Valid substring from st.top() to i
                    maxLen = max(maxLen, i - st.top());
                }
            }
        }

        return maxLen;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `st.push(-1);`
 * - If `(`: `st.push(i)`.
 * - If `)`:
 *     - `st.pop();`
 *     - If `st.empty()`: `st.push(i);`
 *     - Else: `maxLen = max(maxLen, i - st.top());`
 * - Time: O(N), Space: O(N).
 */
