# Stack Pattern – 16 Lessons
(With Detailed Dry Runs & Visualizations)

---

# 📌 Introduction to Stack

A Stack is a Linear Data Structure that follows:

LIFO → Last In First Out

Basic Operations:
- push(x)
- pop()
- top()/peek()
- isEmpty()

Visualization:

Push Example:
Push 1 → Push 2 → Push 3

| 3 |
| 2 |
| 1 |
-----

Pop removes 3 first.

---

# 1️⃣ Implementing Stack Data Structure

## Using Array (C++)

```cpp
class Stack {
    int arr[1000];
    int top;
public:
    Stack() { top = -1; }

    bool push(int x) {
        if(top >= 999) return false;
        arr[++top] = x;
        return true;
    }

    int pop() {
        if(top < 0) return -1;
        return arr[top--];
    }
};
```

---

# 2️⃣ Using Built-in Stack

## C++
```cpp
#include <stack>
stack<int> st;
st.push(10);
st.pop();
```

## Java
```java
Stack<Integer> st = new Stack<>();
```

## Python
```python
stack = []
stack.append(10)
stack.pop()
```

---

# 3️⃣ Applications of Stack

✔ Balanced Parentheses  
✔ Expression Evaluation  
✔ Undo/Redo  
✔ DFS  
✔ Backtracking  
✔ Browser History  

---

# 4️⃣ Problem 1: Balanced Parentheses (Easy)

```cpp
bool isValid(string s) {
    stack<char> st;
    for(char c : s){
        if(c=='('||c=='{'||c=='[')
            st.push(c);
        else{
            if(st.empty()) return false;
            if((c==')'&&st.top()!='(') ||
               (c=='}'&&st.top()!='{') ||
               (c==']'&&st.top()!='['))
                return false;
            st.pop();
        }
    }
    return st.empty();
}
```

Dry Run:
Input: "{[()]}"

Push {  
Push [  
Push (  
Pop (  
Pop [  
Pop {  

Stack empty → Valid

---

# 5️⃣ Problem 2: Reverse a String (Easy)

```cpp
string reverseString(string s){
    stack<char> st;
    for(char c:s) st.push(c);
    string result="";
    while(!st.empty()){
        result += st.top();
        st.pop();
    }
    return result;
}
```

Dry Run:
Input: "abc"

Stack:
a b c

Pop order:
c b a

Output: "cba"

---

# 6️⃣ Problem 3: Decimal to Binary Conversion (Medium)

```cpp
string decimalToBinary(int n){
    stack<int> st;
    while(n>0){
        st.push(n%2);
        n/=2;
    }
    string result="";
    while(!st.empty()){
        result += to_string(st.top());
        st.pop();
    }
    return result;
}
```

Dry Run:
Input: 10

10 → remainder 0  
5 → remainder 1  
2 → remainder 0  
1 → remainder 1  

Stack (bottom→top):
0 1 0 1

Output: 1010

---

# 7️⃣ Problem 4: Next Greater Element (Easy)

```cpp
vector<int> nextGreater(vector<int>& nums){
    stack<int> st;
    vector<int> res(nums.size(), -1);

    for(int i=0;i<nums.size();i++){
        while(!st.empty() && nums[i] > nums[st.top()]){
            res[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return res;
}
```

Dry Run:
Input: [4,5,2,10]

4 → push  
5 > 4 → 5 is NGE of 4  
2 → push  
10 > 2 → 10 is NGE of 2  
10 > 5 → 10 is NGE of 5  

Result: [5,10,10,-1]

---

# 8️⃣ Problem 5: Sorting a Stack (Easy)

Idea:
Use recursion or temporary stack.

Example:

Original Stack:
| 3 |
| 1 |
| 4 |
| 2 |

Sorted Stack:
| 4 |
| 3 |
| 2 |
| 1 |

---

# 9️⃣ Problem 6: Simplify Path (Medium)

```cpp
string simplifyPath(string path){
    stack<string> st;
    string cur="";
    path += '/';

    for(char c:path){ // path = "/a/./b/../../c/"
        if(c=='/'){
            if(cur==".." && !st.empty())
                st.pop();
            else if(cur!="" && cur!="." && cur!="..")
                st.push(cur);
            cur="";
        } else {
            cur+=c; // cur = "a", then "b", then "..", then "..", then "c"
        }
    }

    string result="";
    while(!st.empty()){
        result = "/" + st.top() + result;
        st.pop();
    }

    return result==""?"/":result;
}
```

Dry Run:
Input: "/a/./b/../../c/"

Push a  
Push b  
Pop b  
Pop a  
Push c  

Output: "/c"

---

# ✅ Summary

✔ Stack follows LIFO  
✔ Used in parsing and matching problems  
✔ Powerful for monotonic stack problems  
✔ Common in coding interviews  

---

# 🧠 Interview Tip

If problem involves:
- Matching symbols
- Next greater/smaller
- Undo operations

Think → STACK
