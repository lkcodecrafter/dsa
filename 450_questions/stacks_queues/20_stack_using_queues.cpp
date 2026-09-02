/*
    QUESTION    : Implement Stack using Queue
    Company Tags: Amazon, Microsoft, Adobe
    GfG Link    : https://practice.geeksforgeeks.org/problems/stack-using-two-queues/1
    LeetCode    : https://leetcode.com/problems/implement-stack-using-queues/
*/

#include <iostream>
#include <queue>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : Push: O(N) or O(1), Pop: O(1), Top: O(1)
// S.C : O(N) - Single queue implementation
class MyStack {
private:
    queue<int> q;

public:
    // Push element x onto stack using single queue rotation
    void push(int x) {
        int sz = q.size();
        q.push(x);

        // Rotate previous elements behind new element
        for (int i = 0; i < sz; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        if (q.empty()) return -1;
        int val = q.front();
        q.pop();
        return val;
    }

    int top() {
        if (q.empty()) return -1;
        return q.front();
    }

    bool empty() {
        return q.empty();
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Single Queue Rotation: `q.push(x); for (0 to size-1) { q.push(q.front()); q.pop(); }`
 * - `pop()` and `top()` are $O(1)$ from `q.front()`.
 * - Time: Push $O(N)$, Pop $O(1)$. Space: $O(N)$.
 */
