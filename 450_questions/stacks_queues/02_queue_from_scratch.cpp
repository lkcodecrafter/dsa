/*
    QUESTION    : Implement Queue from Scratch using Array
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : Push: O(1), Pop: O(1), Front: O(1)
// S.C : O(N) - Circular buffer array storage
class MyQueue {
private:
    int* arr;
    int frontIdx;
    int rearIdx;
    int count;
    int capacity;

public:
    MyQueue(int size = 1000) {
        capacity = size;
        arr = new int[capacity];
        frontIdx = 0;
        rearIdx = 0;
        count = 0;
    }

    ~MyQueue() {
        delete[] arr;
    }

    void push(int x) {
        if (count == capacity) {
            cout << "Queue Overflow!\n";
            return;
        }
        arr[rearIdx] = x;
        rearIdx = (rearIdx + 1) % capacity;
        count++;
    }

    int pop() {
        if (count == 0) {
            cout << "Queue Underflow!\n";
            return -1;
        }
        int val = arr[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;
        count--;
        return val;
    }

    int front() {
        if (count == 0) return -1;
        return arr[frontIdx];
    }

    bool empty() {
        return count == 0;
    }

    int size() {
        return count;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Circular Buffer: `rearIdx = (rearIdx + 1) % capacity`, `frontIdx = (frontIdx + 1) % capacity`.
 * - `push(x)`: `arr[rearIdx] = x; rearIdx = (rearIdx + 1) % cap; count++;`
 * - `pop()`: `val = arr[frontIdx]; frontIdx = (frontIdx + 1) % cap; count--; return val;`
 * - Time: O(1) per operation, Space: O(N).
 */
