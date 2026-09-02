#include<iostream>
#include<vector>
using namespace std;

/*
 * Problem: Min Stack (LeetCode 155)
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time O(1).
 *
 * Pattern: Stack Design / Pair Tracking
 *
 * Complexity:
 * - Time Complexity: O(1) for all operations (push, pop, top, getMin).
 *   We avoid any linear scan by tracking the minimum value at each state.
 * - Space Complexity: O(N) where N is the number of elements in the stack.
 *   Each element in the stack is stored as a pair of integers.
 *
 * Visualizations:
 * Stack state progression during push operations:
 *
 * 1. Push 5:
 *    [ {val: 5, min: 5} ] <-- Top (min_so_far is 5)
 *
 * 2. Push 3:
 *    [ {val: 5, min: 5}, {val: 3, min: 3} ] <-- Top (min_so_far is min(3, 5) = 3)
 *
 * 3. Push 7:
 *    [ {val: 5, min: 5}, {val: 3, min: 3}, {val: 7, min: 3} ] <-- Top (min_so_far is min(7, 3) = 3)
 *
 * Memorization Hook:
 * "Store each stack node as a pair: {value, min_so_far}. 
 * The current minimum is always cached at the top of the stack, eliminating searching."
 *
 * 1-Minute Quick Revision:
 * 1. Maintain a single `vector<pair<int, int>> st` where each element is `{val, min_so_far}`.
 * 2. `push(val)`: If stack is empty, push `{val, val}`. Otherwise, push `{val, min(val, st.back().second)}`.
 * 3. `pop()`: Remove the top element using `st.pop_back()`.
 * 4. `top()`: Return the value component of the top element: `st.back().first`.
 * 5. `getMin()`: Return the minimum component of the top element: `st.back().second`.
 *
 * Dry Run:
 * Operations: push(5), push(3), getMin(), push(7), getMin(), pop(), getMin()
 *
 * | Step / Operation | Argument | Stack State (Bottom -> Top)        | top() result | getMin() result | Action / Explanation                               |
 * |------------------|----------|------------------------------------|--------------|-----------------|----------------------------------------------------|
 * | push(5)          | 5        | [{5, 5}]                           | -            | -               | Stack empty, new min is 5                          |
 * | push(3)          | 3        | [{5, 5}, {3, 3}]                   | -            | -               | 3 < 5, new min is 3                                |
 * | getMin()         | -        | [{5, 5}, {3, 3}]                   | -            | 3               | Returns top pair's min (3)                         |
 * | push(7)          | 7        | [{5, 5}, {3, 3}, {7, 3}]           | -            | -               | 7 > 3, new min remains 3                           |
 * | getMin()         | -        | [{5, 5}, {3, 3}, {7, 3}]           | -            | 3               | Returns top pair's min (3)                         |
 * | pop()            | -        | [{5, 5}, {3, 3}]                   | -            | -               | Removes {7, 3}                                     |
 * | getMin()         | -        | [{5, 5}, {3, 3}]                   | -            | 3               | Returns top pair's min (3)                         |
 */
class MinStack {
private:
    // Pair stores {value, min_so_far_at_this_level}
    vector<pair<int, int>> st;

public:
    MinStack() {
        // Constructor
    }
    
    void push(int val) {
        if (st.empty()) {
            st.push_back({val, val});
        } else {
            // New min is the minimum of the new value and the current min of the stack
            int currentMin = min(val, st.back().second);
            st.push_back({val, currentMin});
        }
    }
    
    void pop() {
        st.pop_back();
    }
    
    int top() {
        return st.back().first;
    }
    
    int getMin() {
        return st.back().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */