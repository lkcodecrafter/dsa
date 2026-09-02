/*
    QUESTION    : Reverse a String using Stack
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/reverse-a-string-using-stack/1
*/

#include <iostream>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Push all characters + Pop all characters
// S.C : O(N) - Stack storing characters
char* reverse(char *S, int len) {
    stack<char> st;

    // Push all characters to stack
    for (int i = 0; i < len; i++) {
        st.push(S[i]);
    }

    // Pop characters in reverse order back into string
    int i = 0;
    while (!st.empty()) {
        S[i++] = st.top();
        st.pop();
    }

    return S;
}

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - LIFO property of stack naturally reverses characters.
 * - Push all characters to stack, then pop sequentially into string buffer.
 * - Time: O(N), Space: O(N).
 */
