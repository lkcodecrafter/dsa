/*
    QUESTION    : Implement two stacks in an array
    Company Tags: Amazon, Microsoft, Samsung, 24*7 Innovation Labs
    GfG Link    : https://practice.geeksforgeeks.org/problems/implement-two-stacks-in-an-array/1
*/

#include <iostream>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : Push1/Push2: O(1), Pop1/Pop2: O(1)
// S.C : O(N) - Two stacks growing towards each other from opposite ends of a single array
class twoStacks {
private:
    int* arr;
    int size;
    int top1;
    int top2;

public:
    twoStacks(int n = 100) {
        size = n;
        arr = new int[n];
        top1 = -1;
        top2 = size;
    }

    // Push into Stack 1 (grows from left to right)
    void push1(int x) {
        if (top1 < top2 - 1) {
            arr[++top1] = x;
        }
    }

    // Push into Stack 2 (grows from right to left)
    void push2(int x) {
        if (top1 < top2 - 1) {
            arr[--top2] = x;
        }
    }

    // Pop from Stack 1
    int pop1() {
        if (top1 >= 0) {
            return arr[top1--];
        }
        return -1;
    }

    // Pop from Stack 2
    int pop2() {
        if (top2 < size) {
            return arr[top2++];
        }
        return -1;
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF 2 STACKS IN SINGLE ARRAY
 * ============================================================================
 *
 * Array: [ S1_Bottom -> ... S1_Top | Space Available | S2_Top ... <- S2_Bottom ]
 * Indices: 0                          top1             top2                    size-1
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `top1 = -1`, `top2 = size`.
 * - `push1(x)`: `if (top1 < top2 - 1) arr[++top1] = x`.
 * - `push2(x)`: `if (top1 < top2 - 1) arr[--top2] = x`.
 * - `pop1()`: `top1 >= 0 ? arr[top1--] : -1`.
 * - `pop2()`: `top2 < size ? arr[top2++] : -1`.
 * - Time: O(1), Space: O(N).
 */
