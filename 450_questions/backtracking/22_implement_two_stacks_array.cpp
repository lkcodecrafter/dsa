/*
 * QUESTION: Implement 2 stacks in an array
 * Link: https://practice.geeksforgeeks.org/problems/implement-two-stacks-in-an-array/1
 * 
 * Description: Implement two stacks in a single array of size N. 
 * Stack1 grows from left to right, and Stack2 grows from right to left.
 */

#include <iostream>
#include <vector>
#include <stdexcept>

class twoStacks {
private:
    std::vector<int> arr; // Shared array container
    int top1;             // Index of top element of Stack 1
    int top2;             // Index of top element of Stack 2
    int size;             // Total capacity of the array

public:
    // Constructor to initialize capacity
    twoStacks(int n = 100) {
        size = n;
        arr.resize(size);
        top1 = -1;        // Stack 1 starts from the left
        top2 = size;      // Stack 2 starts from the right
    }

    // Push element x to Stack 1
    void push1(int x) {
        // Space exists if top1 is at least 1 index away from top2
        if (top1 < top2 - 1) {
            top1++;
            arr[top1] = x;
        } else {
            throw std::overflow_error("Stack Overflow: No space available in shared array.");
        }
    }

    // Push element x to Stack 2
    void push2(int x) {
        // Space exists if top1 is at least 1 index away from top2
        if (top1 < top2 - 1) {
            top2--;
            arr[top2] = x;
        } else {
            throw std::overflow_error("Stack Overflow: No space available in shared array.");
        }
    }

    // Pop element from Stack 1 (returns -1 on underflow, matching GFG requirements)
    int pop1() {
        if (top1 >= 0) {
            int val = arr[top1];
            top1--;
            return val;
        } else {
            return -1; // Underflow indicator
        }
    }

    // Pop element from Stack 2 (returns -1 on underflow, matching GFG requirements)
    int pop2() {
        if (top2 < size) {
            int val = arr[top2];
            top2++;
            return val;
        } else {
            return -1; // Underflow indicator
        }
    }
};

/*
 * DRY RUN (Shared Array size = 4):
 * twoStacks ts(4);
 * Initial: top1 = -1, top2 = 4
 * 
 * | Operation | top1 | top2 | arr State       | Returned value | Note                                      |
 * | :-------- | :--- | :--- | :-------------- | :------------- | :---------------------------------------- |
 * | push1(5)  | 0    | 4    | {5, -, -, -}    | -              | top1 incremented to 0                     |
 * | push2(20) | 0    | 3    | {5, -, -, 20}   | -              | top2 decremented to 3                     |
 * | push1(10) | 1    | 3    | {5, 10, -, 20}  | -              | top1 incremented to 1                     |
 * | push2(30) | 1    | 2    | {5, 10, 30, 20} | -              | top2 decremented to 2. Array is now full! |
 * | push1(15) | 1    | 2    | {5, 10, 30, 20} | (Error)        | top1 < top2 - 1 (1 < 1) -> False. Overflow|
 * | pop2()    | 1    | 3    | {5, 10, 30, 20} | 30             | top2 incremented to 3                     |
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine two travelers sharing a single long bench. 
 * Traveler 1 sits at the far left edge (`top1 = -1`) and places luggage going right. 
 * Traveler 2 sits at the far right edge (`top2 = size`) and places luggage going left. 
 * They can keep adding bags as long as their luggage piles don't bump into each other (`top1 < top2 - 1`).
 * 
 * 1-MINUTE QUICK REVISION:
 * - Use a single array of size `N`.
 * - Initialize two pointers: `top1 = -1` (left end) and `top2 = N` (right end).
 * - Push check: both stacks can push as long as `top1 < top2 - 1` (at least one empty cell exists between them).
 *   - Stack 1 push: increment `top1`, insert.
 *   - Stack 2 push: decrement `top2`, insert.
 * - Pop check:
 *   - Stack 1 pop: if `top1 >= 0`, return `arr[top1--]`, else `-1`.
 *   - Stack 2 pop: if `top2 < N`, return `arr[top2++]`, else `-1`.
 * - Time Complexity: O(1) for all operations.
 * - Space Complexity: O(N) array storage, O(1) auxiliary space.
 */
