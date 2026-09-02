/*
    QUESTION    : Reverse a Stack using recursion
    Company Tags: Amazon, Microsoft, Paytm
    GfG Link    : https://practice.geeksforgeeks.org/problems/reverse-a-stack/1
*/

#include <iostream>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - N recursive calls, each calling insertAtBottom in O(N)
// S.C : O(N)   - Recursion stack space
class Solution {
private:
    void insertAtBottom(stack<int> &st, int x) {
        if (st.empty()) {
            st.push(x);
            return;
        }

        int topVal = st.top();
        st.pop();
        insertAtBottom(st, x);
        st.push(topVal);
    }

public:
    void Reverse(stack<int> &st) {
        if (st.empty()) return;

        int topVal = st.top();
        st.pop();

        // Reverse the remaining stack
        Reverse(st);

        // Insert the held topVal at the bottom of the reversed stack
        insertAtBottom(st, topVal);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `Reverse(st)`:
 *     - If `st.empty()`, return.
 *     - `topVal = st.top(); st.pop();`
 *     - `Reverse(st);`
 *     - `insertAtBottom(st, topVal);`
 * - Time: O(N^2), Space: O(N).
 */
