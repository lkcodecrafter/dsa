/*
    QUESTION    : Evaluation of Postfix Expression (Reverse Polish Notation)
    Company Tags: Amazon, Microsoft, Samsung
    GfG Link    : https://practice.geeksforgeeks.org/problems/evaluation-of-postfix-expression1735/1
    LeetCode    : https://leetcode.com/problems/evaluate-reverse-polish-notation/
*/

#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Single pass through postfix string
// S.C : O(N) - Stack storing operand values
class Solution {
public:
    int evaluatePostfix(string S) {
        stack<int> st;

        for (char ch : S) {
            if (isdigit(ch)) {
                st.push(ch - '0');
            } else {
                int val2 = st.top(); st.pop();
                int val1 = st.top(); st.pop();

                switch (ch) {
                    case '+': st.push(val1 + val2); break;
                    case '-': st.push(val1 - val2); break;
                    case '*': st.push(val1 * val2); break;
                    case '/': st.push(val1 / val2); break;
                }
            }
        }

        return st.top();
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - If digit: push to stack.
 * - If operator: pop `val2`, pop `val1`, compute `val1 (op) val2`, push result.
 * - Time: O(N), Space: O(N).
 */
