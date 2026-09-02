/*
    QUESTION    : Expression contains redundant bracket or not
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/expression-contains-redundant-bracket-not/
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Linear pass through expression
// S.C : O(N) - Stack storing characters
class Solution {
public:
    bool checkRedundancy(string& s) {
        stack<char> st;

        for (char ch : s) {
            if (ch == ')') {
                char top = st.top();
                st.pop();

                bool hasOperator = false;

                // Check if any operator exists between matching '(' and ')'
                while (top != '(') {
                    if (top == '+' || top == '-' || top == '*' || top == '/') {
                        hasOperator = true;
                    }
                    top = st.top();
                    st.pop();
                }

                // If no operator found inside brackets, brackets are redundant!
                if (!hasOperator) {
                    return true;
                }
            } else {
                st.push(ch);
            }
        }

        return false;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If closing `)`: pop until `(`. If no operator (`+`, `-`, `*`, `/`) was popped, return `true` (Redundant).
 * - Else: `st.push(ch)`.
 * - Return `false`.
 * - Time: O(N), Space: O(N).
 */
