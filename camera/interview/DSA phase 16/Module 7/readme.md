# Module 7: Stacks & Queues (Lectures 89–98)

## 📋 Syllabus
*   **Stack:** Valid Parentheses, Next Greater/Smaller Element, Stock Span, Largest Rectangle in Histogram, Celebrity Problem, N-Stacks in Array.
*   **Queue & Deque:** Circular Queue, Queue using Stacks, Sliding Window Maximum, Min K-Consecutive Bit Flips.

---

## 🟢 Section 1: Stack

### 🎯 Solution 7.1: Next Greater Element & Next Smaller Element
*   **Problem:** Find the next greater element (or next smaller element) for each index in an array.
*   **C++ Code:**
```cpp
#include <vector>
#include <stack>

// 1. Next Greater Element
std::vector<int> nextGreaterElement(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> res(n, -1);
    std::stack<int> st; // Stores elements
    
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() <= nums[i]) {
            st.pop();
        }
        if (!st.empty()) {
            res[i] = st.top();
        }
        st.push(nums[i]);
    }
    return res;
}

// 2. Next Smaller Element
std::vector<int> nextSmallerElement(const std::vector<int>& nums) {
    int n = nums.size();
    std::vector<int> res(n, -1);
    std::stack<int> st;
    
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && st.top() >= nums[i]) {
            st.pop();
        }
        if (!st.empty()) {
            res[i] = st.top();
        }
        st.push(nums[i]);
    }
    return res;
}
```
*   **🔍 Dry Run (Next Greater Element on `{4, 5, 2, 25}`):**
    *   Initialize `res = {-1, -1, -1, -1}`, `st` is empty.
    *   `i = 3 (25)`: stack empty -> `res[3] = -1`. Push `25`.
    *   `i = 2 (2)`: stack top `25 > 2` -> `res[2] = 25`. Push `2`.
    *   `i = 1 (5)`: stack top `2 <= 5` -> pop 2. Stack top `25 > 5` -> `res[1] = 25`. Push `5`.
    *   `i = 0 (4)`: stack top `5 > 4` -> `res[0] = 5`. Push `4`.
    *   **Result:** `{5, 25, 25, -1}`.
*   **Complexity:** Time: $O(N)$, Space: $O(N)$ for stack.

### 🎯 Solution 7.2: Valid Parentheses, Stock Span & Celebrity Problem
*   **C++ Code:**
```cpp
#include <stack>
#include <string>
#include <vector>

// 1. Valid Parentheses
bool isValid(const std::string& s) {
    std::stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            if (c == ')' && st.top() != '(') return false;
            if (c == '}' && st.top() != '{') return false;
            if (c == ']' && st.top() != '[') return false;
            st.pop();
        }
    }
    return st.empty();
}

// 2. Stock Span Problem (Returns span values)
std::vector<int> calculateSpan(const std::vector<int>& price) {
    int n = price.size();
    std::vector<int> span(n);
    std::stack<int> st; // Stores indices
    
    for (int i = 0; i < n; i++) {
        while (!st.empty() && price[st.top()] <= price[i]) {
            st.pop();
        }
        span[i] = st.empty() ? (i + 1) : (i - st.top());
        st.push(i);
    }
    return span;
}

// 3. Celebrity Problem
int celebrity(const std::vector<std::vector<int>>& M, int n) {
    std::stack<int> st;
    for (int i = 0; i < n; i++) st.push(i);
    
    while (st.size() > 1) {
        int a = st.top(); st.pop();
        int b = st.top(); st.pop();
        if (M[a][b] == 1) st.push(b); // a knows b, so a cannot be celebrity
        else st.push(a); // a does not know b, so b cannot be celebrity
    }
    if (st.empty()) return -1;
    int candidate = st.top();
    for (int i = 0; i < n; i++) {
        if (i != candidate && (M[candidate][i] == 1 || M[i][candidate] == 0)) {
            return -1;
        }
    }
    return candidate;
}
```
*   **Complexity:** Time: $O(N)$ for all, Space: $O(N)$.

### 🎯 Solution 7.3: N-Stacks in an Array
*   **Problem:** Implement $N$ stacks in a single array of size $S$.
*   **C++ Code:**
```cpp
#include <vector>

class NStacks {
    std::vector<int> arr;
    std::vector<int> top;
    std::vector<int> next;
    int freeSpot;
public:
    NStacks(int N, int S) {
        arr.resize(S);
        top.assign(N, -1);
        next.resize(S);
        for (int i = 0; i < S - 1; i++) next[i] = i + 1;
        next[S - 1] = -1;
        freeSpot = 0;
    }
    
    bool push(int x, int m) {
        if (freeSpot == -1) return false; // Overflow
        int index = freeSpot;
        freeSpot = next[index];
        next[index] = top[m - 1];
        top[m - 1] = index;
        arr[index] = x;
        return true;
    }
    
    int pop(int m) {
        if (top[m - 1] == -1) return -1; // Underflow
        int index = top[m - 1];
        top[m - 1] = next[index];
        next[index] = freeSpot;
        freeSpot = index;
        return arr[index];
    }
};
```
*   **Complexity:** Time: $O(1)$ for push & pop, Space: $O(N + S)$.

### 🎯 Solution 7.4: Largest Rectangle in Histogram
*   **Problem:** Find the largest rectangular area possible in a given histogram.
*   **C++ Code:**
```cpp
#include <vector>
#include <stack>
#include <algorithm>

int largestRectangleArea(const std::vector<int>& heights) {
    int n = heights.size();
    std::stack<int> st;
    int maxArea = 0;
    
    for (int i = 0; i <= n; i++) {
        int currentHeight = (i == n) ? 0 : heights[i];
        while (!st.empty() && heights[st.top()] >= currentHeight) {
            int h = heights[st.top()];
            st.pop();
            int w = st.empty() ? i : i - st.top() - 1;
            maxArea = std::max(maxArea, h * w);
        }
        st.push(i);
    }
    return maxArea;
}
```
*   **Complexity:** Time: $O(N)$, Space: $O(N)$.

---

## 🟢 Section 2: Queue & Deque

### 🎯 Solution 7.5: Circular Queue & Queue using Stacks
*   **C++ Code:**
```cpp
// 1. Circular Queue
class CircularQueue {
    int* arr;
    int front, rear, size;
public:
    CircularQueue(int n) {
        size = n;
        arr = new int[size];
        front = rear = -1;
    }
    
    bool enqueue(int value) {
        if ((front == 0 && rear == size - 1) || (rear == (front - 1) % (size - 1))) {
            return false; // Full
        }
        if (front == -1) {
            front = rear = 0;
        } else if (rear == size - 1 && front != 0) {
            rear = 0;
        } else {
            rear++;
        }
        arr[rear] = value;
        return true;
    }
    
    int dequeue() {
        if (front == -1) return -1; // Empty
        int ans = arr[front];
        if (front == rear) {
            front = rear = -1;
        } else if (front == size - 1) {
            front = 0;
        } else {
            front++;
        }
        return ans;
    }
};

// 2. Queue using Stacks (Costly dequeue/pop)
#include <stack>

class QueueUsingStacks {
    std::stack<int> s1, s2;
public:
    void push(int x) { s1.push(x); }
    int pop() {
        if (s1.empty() && s2.empty()) return -1;
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        int val = s2.top();
        s2.pop();
        return val;
    }
};
```
*   **Complexity:** Time: $O(1)$ for enqueue (Circular Queue) and push (Queue using Stacks). Space: $O(N)$.

### 🎯 Solution 7.6: Sliding Window Maximum & Min K-Consecutive Bit Flips
*   **C++ Code:**
```cpp
#include <vector>
#include <deque>
#include <queue>

// 1. Sliding Window Maximum
std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
    std::vector<int> result;
    std::deque<int> dq; // Monotonic deque storing indices
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove indices out of current window
        if (!dq.empty() && dq.front() == i - k) {
            dq.pop_front();
        }
        // Remove elements smaller than current element from back
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

// 2. Min K-Consecutive Bit Flips
int minKBitFlips(std::vector<int>& nums, int k) {
    int n = nums.size();
    std::queue<int> q; // Stores indices of flips
    int flips = 0;
    
    for (int i = 0; i < n; i++) {
        if (!q.empty() && q.front() + k <= i) {
            q.pop();
        }
        // Check if current bit needs a flip based on cumulative flips in window
        if ((nums[i] == 0 && q.size() % 2 == 0) || (nums[i] == 1 && q.size() % 2 != 0)) {
            if (i + k > n) return -1;
            q.push(i);
            flips++;
        }
    }
    return flips;
}
```
*   **Complexity:**
    *   Window Maximum: Time $O(N)$, Space $O(K)$.
    *   Bit Flips: Time $O(N)$, Space $O(K)$.
