/*
    QUESTION    : Efficiently implement k queues in a single array
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/efficiently-implement-k-queues-single-array/
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : Enqueue: O(1), Dequeue: O(1)
// S.C : O(N + K) - arr, front, rear, and next arrays
class KQueues {
private:
    int* arr;
    int* front;
    int* rear;
    int* next;
    int n, k;
    int freeSpot;

public:
    KQueues(int k1, int n1) {
        k = k1;
        n = n1;
        arr = new int[n];
        front = new int[k];
        rear = new int[k];
        next = new int[n];

        for (int i = 0; i < k; i++) {
            front[i] = -1;
            rear[i] = -1;
        }

        freeSpot = 0;
        for (int i = 0; i < n - 1; i++) {
            next[i] = i + 1;
        }
        next[n - 1] = -1;
    }

    ~KQueues() {
        delete[] arr;
        delete[] front;
        delete[] rear;
        delete[] next;
    }

    void enqueue(int item, int qn) {
        if (freeSpot == -1) {
            cout << "Queue Overflow!\n";
            return;
        }

        int index = freeSpot;
        freeSpot = next[index];

        if (front[qn] == -1) {
            front[qn] = index;
        } else {
            next[rear[qn]] = index;
        }

        next[index] = -1;
        rear[qn] = index;
        arr[index] = item;
    }

    int dequeue(int qn) {
        if (front[qn] == -1) {
            cout << "Queue Underflow!\n";
            return -1;
        }

        int index = front[qn];
        front[qn] = next[index];

        if (front[qn] == -1) {
            rear[qn] = -1;
        }

        next[index] = freeSpot;
        freeSpot = index;

        return arr[index];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `front[k]`, `rear[k]`, `next[n]`, `freeSpot = 0`.
 * - Time: O(1) all ops, Space: O(N + K).
 */
