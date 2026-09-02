/*
    QUESTION    : Efficiently implement k stacks in a single array
    Company Tags: Amazon, Microsoft, Flipkart
    GfG Link    : https://www.geeksforgeeks.org/efficiently-implement-k-stacks-single-array/
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : Push: O(1), Pop: O(1)
// S.C : O(N + K) - arr of size N, top of size K, next of size N
class KStacks {
private:
    int* arr;
    int* top;
    int* next;
    int n, k;
    int freeSpot;

public:
    KStacks(int k1, int n1) {
        k = k1;
        n = n1;
        arr = new int[n];
        top = new int[k];
        next = new int[n];

        for (int i = 0; i < k; i++) {
            top[i] = -1;
        }

        freeSpot = 0;
        for (int i = 0; i < n - 1; i++) {
            next[i] = i + 1;
        }
        next[n - 1] = -1;
    }

    ~KStacks() {
        delete[] arr;
        delete[] top;
        delete[] next;
    }

    // Push item into sn-th stack (0-indexed)
    void push(int item, int sn) {
        if (freeSpot == -1) {
            cout << "Stack Overflow!\n";
            return;
        }

        int index = freeSpot;
        freeSpot = next[index]; // Update freeSpot to next available slot

        arr[index] = item;

        // Link next of this index to previous top of sn-th stack
        next[index] = top[sn];
        top[sn] = index;
    }

    // Pop item from sn-th stack (0-indexed)
    int pop(int sn) {
        if (top[sn] == -1) {
            cout << "Stack Underflow!\n";
            return -1;
        }

        int index = top[sn];
        top[sn] = next[index];

        // Attach freed index back to free list
        next[index] = freeSpot;
        freeSpot = index;

        return arr[index];
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `arr[n]`, `top[k]`, `next[n]`, `freeSpot = 0`.
 * - `push(item, sn)`:
 *     - `idx = freeSpot; freeSpot = next[idx]; arr[idx] = item; next[idx] = top[sn]; top[sn] = idx;`
 * - `pop(sn)`:
 *     - `idx = top[sn]; top[sn] = next[idx]; next[idx] = freeSpot; freeSpot = idx; return arr[idx];`
 * - Time: O(1), Space: O(N + K).
 */
