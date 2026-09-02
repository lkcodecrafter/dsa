/*
    QUESTION    : Sort a Stack using recursion
    Company Tags: Amazon, Microsoft, Goldman Sachs, Intuit
    GfG Link    : https://practice.geeksforgeeks.org/problems/sort-a-stack/1
*/

#include <iostream>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : O(N^2) - N insertions into sorted stack, each taking O(N) in worst case
// S.C : O(N)   - Recursion stack space
class SortedStack {
private:
    void sortedInsert(stack<int> &st, int x) {
        // Base case: Stack is empty or x is greater than current top
        if (st.empty() || x >= st.top()) {
            st.push(x);
            return;
        }

        // If top is greater, pop top and recurse
        int topVal = st.top();
        st.pop();
        sortedInsert(st, x);

        // Put the held element back
        st.push(topVal);
    }

public:
    stack<int> s;

    void sort() {
        if (s.empty()) return;

        int topVal = s.top();
        s.pop();

        // Sort the remaining stack
        sort();

        // Insert topVal into sorted stack
        sortedInsert(s, topVal);
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `sort()`: pop `topVal`, `sort()`, `sortedInsert(s, topVal)`.
 * - `sortedInsert(st, x)`: if `st.empty() || x >= st.top()`, push `x`; else pop `t`, recurse, push `t`.
 * - Time: O(N^2), Space: O(N).
 */
