/*
    QUESTION    : Implement Queue using Stacks
    Company Tags: Amazon, Microsoft, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/queue-using-two-stacks/1
    LeetCode    : https://leetcode.com/problems/implement-queue-using-stacks/
*/

#include <iostream>
#include <stack>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : Push: O(1), Pop: Amortized O(1), Front: Amortized O(1)
// S.C : O(N) - Two stacks (inputStack and outputStack)
class MyQueue {
private:
    stack<int> inSt, outSt;

public:
    void push(int x) {
        inSt.push(x);
    }

    int pop() {
        if (empty()) return -1;

        if (outSt.empty()) {
            while (!inSt.empty()) {
                outSt.push(inSt.top());
                inSt.pop();
            }
        }

        int val = outSt.top();
        outSt.pop();
        return val;
    }

    int front() {
        if (empty()) return -1;

        if (outSt.empty()) {
            while (!inSt.empty()) {
                outSt.push(inSt.top());
                inSt.pop();
            }
        }

        return outSt.top();
    }

    bool empty() {
        return inSt.empty() && outSt.empty();
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `inSt` for push, `outSt` for pop/front.
 * - When `outSt` is empty, dump all elements from `inSt` into `outSt`.
 * - Amortized Time: O(1), Space: O(N).
 */
