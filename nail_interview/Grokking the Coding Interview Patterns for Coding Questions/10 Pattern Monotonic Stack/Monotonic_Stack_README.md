
# 📘 Pattern 10: Monotonic Stack (Complete Guide with Dry Runs & Visualization)

---

# 1️⃣ Introduction to Monotonic Stack

A **Monotonic Stack** is a stack that maintains elements in either:

- Increasing order (Monotonic Increasing Stack)
- Decreasing order (Monotonic Decreasing Stack)

It is mainly used for:
- Next Greater Element
- Next Smaller Element
- Stock Span
- Histogram problems
- Subarray minimum/maximum problems

---

# 🧠 Core Idea

While pushing elements:
- Pop elements that break monotonic property.
- Then push current element.

Time Complexity: O(n) (each element pushed & popped once)

---
# 2️⃣ Remove Nodes From Linked List

## Idea:
Traverse and remove nodes which have a greater value on right.

### Example:
Input: 5 → 2 → 13 → 3 → 8

### Visualization:

Stack process (simulate from right to left):

Step1: 8 → stack = [8]
Step2: 3 < 8 → remove 3
Step3: 13 > 8 → stack = [13]
Step4: 2 < 13 → remove 2
Step5: 5 < 13 → remove 5

Result: 13 → 8

code 

```c++

class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        stack<ListNode*> st;
        ListNode* curr = head;
        while (curr) {
            while (!st.empty() && st.top()->val < curr->val) {
                st.pop();
            }
            st.push(curr);
            curr = curr->next;
        }
        ListNode* newHead = nullptr;
        while (!st.empty()) {
            ListNode* node = st.top();
            st.pop();
            node->next = newHead;
            newHead = node;
        }
        return newHead;
    }
};

```

---
# 3️⃣ Remove All Adjacent Duplicates In String

Input: "abbaca"

Dry Run:

a → push → [a]  
b → push → [a,b]  
b → duplicate → pop → [a]  
a → duplicate → pop → []  
c → push → [c]  
a → push → [c,a]

Output: "ca"

code 

```c++

class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> st;
        for (char c : s) {
            if (!st.empty() && st.top() == c) {
                st.pop();
            } else {
                st.push(c);
            }
        }
        string res = "";
        while (!st.empty()) {
            res += st.top();
            st.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

```
---
# 4️⃣ Next Greater Element

Input: [2,1,2,4,3]

We use Monotonic Decreasing Stack.

Dry Run:

i=0 → push 2  
i=1 → push 1  
i=2 → pop 1 → NGE=2  
i=3 → pop 2 → NGE=4  
i=4 → push 3  

Result: [4,2,4,-1,-1]

code 

```c++

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] < nums[i]) {
                res[st.top()] = nums[i];
                st.pop();
            }
            st.push(i);
        }
        return res;
    }
};

```
---
# 5️⃣ Daily Temperatures

Input: [73,74,75,71,69,72,76,73]

Dry Run (key steps):

73 → push  
74 → pop 73 → ans=1  
75 → pop 74 → ans=1  
71 → push  
69 → push  
72 → pop 69 → ans=1  
76 → pop 72,75 → ans updated  

Final Output:
[1,1,4,2,1,1,0,0]

```c++

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
                res[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }
        return res;
    }
};

```

---
# 6️⃣ Remove All Adjacent Duplicates II (k times)

Input: "deeedbbcccbdaa", k=3

Remove:
eee  
ccc  
ddd  

Final: "aa"

```c++

class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char, int>> st;
        for (char c : s) {
            if (st.empty() || st.top().first != c) {
                st.push({c, 1});
            } else {
                st.top().second++;
                if (st.top().second == k) {
                    st.pop();
                }
            }
        }
        string res = "";
        while (!st.empty()) {
            char c = st.top().first;
            int count = st.top().second;
            st.pop();
            while (count--) {
                res += c;
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```

---
# 7️⃣ Sum of Subarray Minimums

Input: [3,1,2,4]

Each element contribution:

3 → 3  
1 → 6  
2 → 4  
4 → 4  

Total = 17

Key Idea:
Find:
- Previous Smaller
- Next Smaller

Contribution:
arr[i] * left_count * right_count

```c++

    int sumSubarrayMins(vector<int>& arr) {
        int n = arr.size();
        int mod = 1e9 + 7;
        int res = 0;
        stack<int> st;
        for (int i = 0; i <= n; i++) {
            while (!st.empty() &&
                    (i == n || arr[st.top()] >= (i == n ? INT_MIN : arr[i]))) {
                int top = st.top();
                st.pop();
                int left = st.empty() ? -1 : st.top();
                int right = i;
                int count = (top - left) * (right - top);
                res = (res + (long)arr[top] * count) % mod;
            }
            st.push(i);
        }
        return res;
    }


```

---
# 8️⃣ Remove K Digits

Input: "1432219", k=3

Dry Run:

1 → push  
4 → push  
3 → pop 4 (k=2)  
2 → pop 3 (k=1)  
2 → push  
1 → pop 2 (k=0)  

Result: 1219

```c++

class Solution {
public:
    string removeKdigits(string num, int k) {
        int n = num.size();
        stack<char> st;
        for (char c : num) {
            while (k > 0 && !st.empty() && st.top() > c) {
                st.pop();
                k--;
            }
            st.push(c);
        }
        while (k > 0) {
            st.pop();
            k--;
        }
        string res = "";
        while (!st.empty()) {
            res += st.top();
            st.pop();
        }
        reverse(res.begin(), res.end());
        
        // Strip leading zeros (e.g., "0200" -> "200")
        // res.size() > 1 prevents erasing the final '0' if the number itself is "0"
        while (res.size() > 1 && res[0] == '0') {
            res.erase(0, 1);
        }
        return res.empty() ? "0" : res;
    }
};

```


---
# 🔥 When to Use Monotonic Stack?

If question says:
- Next Greater
- Next Smaller
- First smaller on left/right
- Remove digits for smallest/largest
- Subarray minimum/maximum

Think: Monotonic Stack

---
# 🏁 Time & Space Complexity

Time: O(n)  
Space: O(n)

---
# 💪 Master Tip

Each element:
- Pushed once
- Popped once

That’s why complexity is linear.

---
# 🚀 End of Monotonic Stack Pattern
