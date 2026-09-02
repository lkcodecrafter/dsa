/*
    QUESTION    : Implement Stack and Queue using Deque
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/implement-stack-queue-using-deque/
*/

#include <iostream>
#include <deque>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : All Stack and Queue operations O(1)
// S.C : O(N) - Deque storage
class StackUsingDeque {
private:
    deque<int> dq;
public:
    void push(int x) { dq.push_back(x); }
    int pop() {
        if (dq.empty()) return -1;
        int val = dq.back();
        dq.pop_back();
        return val;
    }
    int top() { return dq.empty() ? -1 : dq.back(); }
    bool empty() { return dq.empty(); }
};

class QueueUsingDeque {
private:
    deque<int> dq;
public:
    void push(int x) { dq.push_back(x); }
    int pop() {
        if (dq.empty()) return -1;
        int val = dq.front();
        dq.pop_front();
        return val;
    }
    int front() { return dq.empty() ? -1 : dq.front(); }
    bool empty() { return dq.empty(); }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Stack via Deque: `push_back()` & `pop_back()`.
 * - Queue via Deque: `push_back()` & `pop_front()`.
 * - Time: O(1) all ops, Space: O(N).
 */
