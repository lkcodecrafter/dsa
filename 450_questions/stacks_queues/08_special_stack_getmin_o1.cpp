/*
    QUESTION    : Design a Stack that supports getMin() in O(1) time and O(1) extra space
    Company Tags: Amazon, Microsoft, Goldman Sachs, SAP Labs
    GfG Link    : https://practice.geeksforgeeks.org/problems/special-stack/1
    LeetCode    : https://leetcode.com/problems/min-stack/
*/

#include <iostream>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : Push: O(1), Pop: O(1), Top: O(1), getMin: O(1)
// S.C : O(1) Extra Space - Uses mathematical transformation (2*x - minEle) to encode previous min
class MinStack {
private:
    stack<long long> st;
    long long minEle;

public:
    void push(int val) {
        if (st.empty()) {
            st.push(val);
            minEle = val;
        } else {
            if (val < minEle) {
                // Encode previous min into the stack
                st.push(2LL * val - minEle);
                minEle = val;
            } else {
                st.push(val);
            }
        }
    }

    void pop() {
        if (st.empty()) return;

        long long topVal = st.top();
        st.pop();

        if (topVal < minEle) {
            // Restore previous minElement
            minEle = 2LL * minEle - topVal;
        }
    }

    int top() {
        if (st.empty()) return -1;

        long long topVal = st.top();
        if (topVal < minEle) {
            return minEle;
        }
        return topVal;
    }

    int getMin() {
        if (st.empty()) return -1;
        return minEle;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 2*x - minEle ENCODING
 * ============================================================================
 *
 * If incoming val < minEle:
 *   Encoded value = 2*val - minEle < val (Always strictly less than current min!)
 * On pop():
 *   If st.top() < minEle, previous min = 2*minEle - st.top()!
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `push(x)`: if `x < minEle`, push `2*x - minEle` and `minEle = x`; else push `x`.
 * - `pop()`: if `st.top() < minEle`, `minEle = 2*minEle - st.top()`.
 * - `top()`: if `st.top() < minEle`, return `minEle`; else return `st.top()`.
 * - Time: O(1) all ops, Space: O(1) auxiliary.
 */
