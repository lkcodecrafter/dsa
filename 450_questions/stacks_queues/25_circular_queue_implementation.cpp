/*
    QUESTION    : Implement Circular Queue
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/circular-queue-set-1-introduction-array-implementation/
    LeetCode    : https://leetcode.com/problems/design-circular-queue/
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : EnQueue: O(1), DeQueue: O(1), Front/Rear: O(1)
// S.C : O(N) - Circular array buffer
class MyCircularQueue {
private:
    int* arr;
    int front;
    int rear;
    int size;
    int capacity;

public:
    MyCircularQueue(int k) {
        capacity = k;
        arr = new int[capacity];
        front = 0;
        rear = 0;
        size = 0;
    }

    ~MyCircularQueue() {
        delete[] arr;
    }

    bool enQueue(int value) {
        if (isFull()) return false;
        arr[rear] = value;
        rear = (rear + 1) % capacity;
        size++;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) return false;
        front = (front + 1) % capacity;
        size--;
        return true;
    }

    int Front() {
        if (isEmpty()) return -1;
        return arr[front];
    }

    int Rear() {
        if (isEmpty()) return -1;
        return arr[(rear - 1 + capacity) % capacity];
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == capacity;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `enQueue`: `arr[rear] = val; rear = (rear + 1) % cap; size++;`
 * - `deQueue`: `front = (front + 1) % cap; size--;`
 * - Time: O(1) all ops, Space: O(N).
 */
