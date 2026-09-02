/*
    QUESTION    : Parenthesis Checker (Valid Parentheses)
    Company Tags: Amazon, Microsoft, Flipkart, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/parenthesis-checker2744/1
    LeetCode    : https://leetcode.com/problems/valid-parentheses/
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Single pass through string
// S.C : O(N) - Stack storing open brackets
class Solution {
public:
    bool ispar(string x) {
        stack<char> st;

        for (char ch : x) {
            // Push opening brackets to stack
            if (ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            } else {
                // If closing bracket arrives with empty stack -> Unbalanced!
                if (st.empty()) return false;

                char topChar = st.top();

                // Check matching pair
                if ((ch == ')' && topChar == '(') ||
                    (ch == '}' && topChar == '{') ||
                    (ch == ']' && topChar == '[')) {
                    st.pop();
                } else {
                    return false; // Mismatched bracket type
                }
            }
        }

        // Stack must be completely empty for balanced expression
        return st.empty();
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Push `(`, `{`, `[`.
 * - On closing bracket: if stack empty or `st.top()` doesn't match pair $\rightarrow$ `false`, else `st.pop()`.
 * - Return `st.empty()`.
 * - Time: O(N), Space: O(N).
 */
