/*
    QUESTION    : Implement Stack from Scratch using Array
    Company Tags: Amazon, Microsoft
    Link        : https://www.tutorialspoint.com/javaexamples/data_stack.htm
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : Push: O(1), Pop: O(1), Top: O(1), IsEmpty: O(1)
// S.C : O(N) - Contiguous array storage
class MyStack {
private:
    int* arr;
    int topIdx;
    int capacity;

public:
    MyStack(int size = 1000) {
        capacity = size;
        arr = new int[capacity];
        topIdx = -1;
    }

    ~MyStack() {
        delete[] arr;
    }

    void push(int x) {
        if (topIdx >= capacity - 1) {
            cout << "Stack Overflow!\n";
            return;
        }
        arr[++topIdx] = x;
    }

    int pop() {
        if (topIdx < 0) {
            cout << "Stack Underflow!\n";
            return -1;
        }
        return arr[topIdx--];
    }

    int top() {
        if (topIdx < 0) return -1;
        return arr[topIdx];
    }

    bool empty() {
        return topIdx == -1;
    }

    int size() {
        return topIdx + 1;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `topIdx = -1`.
 * - `push(x)`: `arr[++topIdx] = x`.
 * - `pop()`: `return arr[topIdx--]`.
 * - `top()`: `return arr[topIdx]`.
 * - Time: O(1) per operation, Space: O(N).
 */
