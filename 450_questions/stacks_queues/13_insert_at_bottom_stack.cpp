/*
    QUESTION    : Insert an element at the bottom of a stack without using extra data structures
    Company Tags: Amazon, Microsoft
    Link        : https://stackoverflow.com/questions/45130465/inserting-at-the-end-of-stack
*/

#include <iostream>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Recursion empties stack and pushes element at base case
// S.C : O(N) - Recursion call stack
class Solution {
public:
    stack<int> insertAtBottom(stack<int> st, int x) {
        // Base case: Stack is empty -> push x
        if (st.empty()) {
            st.push(x);
            return st;
        }

        // Pop current top element
        int topVal = st.top();
        st.pop();

        // Recursively insert x at the bottom of the remaining stack
        st = insertAtBottom(st, x);

        // Put the stored top element back
        st.push(topVal);

        return st;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Base `st.empty()`: `st.push(x); return st;`
 * - `topVal = st.top(); st.pop();`
 * - `st = insertAtBottom(st, x); st.push(topVal);`
 * - Time: O(N), Space: O(N).
 */
