/*
    QUESTION    : Balanced Parentheses (Parenthesis Checker)
    Company Tags: Amazon, Microsoft, Google
    GfG Link    : https://practice.geeksforgeeks.org/problems/parenthesis-checker2744/1
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Stack validation
// S.C : O(N) - Stack storing open bracket characters
class Solution {
public:
    bool ispar(string x) {
        stack<char> st;

        for (char ch : x) {
            if (ch == '(' || ch == '{' || ch == '[') {
                st.push(ch);
            } else {
                if (st.empty()) return false;
                char top = st.top();

                if ((ch == ')' && top == '(') ||
                    (ch == '}' && top == '{') ||
                    (ch == ']' && top == '[')) {
                    st.pop();
                } else {
                    return false;
                }
            }
        }

        return st.empty();
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Push opening brackets; on closing, verify match with `st.top()` and pop.
 * - Return `st.empty()`.
 * - Time: O(N), Space: O(N).
 */
