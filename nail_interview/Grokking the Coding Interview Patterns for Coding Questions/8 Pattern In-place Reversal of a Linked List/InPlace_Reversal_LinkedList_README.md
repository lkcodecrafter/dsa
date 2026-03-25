# In-Place Reversal of a Linked List Pattern – 11 Lessons
(With Detailed Dry Runs & Visualizations)

---

## 📌 Introduction to In-Place Reversal Pattern

This pattern is used when:
- We need to reverse a linked list (fully or partially)
- We must do it using O(1) extra space
- We manipulate pointers carefully

Core Idea:
Use three pointers:
- prev
- current
- next

Reverse direction of `current->next` step by step.

Time Complexity: O(N)  
Space Complexity: O(1)

---

# 1️⃣ Reverse a LinkedList (Easy)

## C++ Code
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while(curr != nullptr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
```

## 🧪 Dry Run

Input:
1 → 2 → 3 → 4 → 5 → NULL

Step-by-step:

Iteration 1:
prev = NULL
curr = 1
1 → NULL

Iteration 2:
2 → 1 → NULL

Iteration 3:
3 → 2 → 1 → NULL

Final:
5 → 4 → 3 → 2 → 1 → NULL

## 📊 Visualization

Before:
1 → 2 → 3 → 4 → 5

After:
5 → 4 → 3 → 2 → 1

---

# 2️⃣ Reverse a Sub-list (Medium)

Reverse from position p to q.

## C++ Code
```cpp
ListNode* reverseBetween(ListNode* head, int p, int q) {
    if(p == q) return head;

    ListNode* curr = head;
    ListNode* prev = nullptr;

    for(int i=0; curr!=nullptr && i<p-1; i++) {
        prev = curr;
        curr = curr->next;
    }

    ListNode* lastNodeFirstPart = prev;
    ListNode* lastNodeSubList = curr;
    ListNode* next = nullptr;

    for(int i=0; curr!=nullptr && i<q-p+1; i++) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    if(lastNodeFirstPart != nullptr)
        lastNodeFirstPart->next = prev;
    else
        head = prev;

    lastNodeSubList->next = curr;

    return head;
}
```

## 🧪 Dry Run

Input:
1 → 2 → 3 → 4 → 5
p = 2, q = 4

Sublist reversed:
1 → 4 → 3 → 2 → 5

---

# 3️⃣ Reverse every K-element Sub-list (Medium)

## C++ Code
```cpp
ListNode* reverseKGroup(ListNode* head, int k) {
    if(k <= 1 || head == nullptr) return head;

    ListNode* curr = head;
    ListNode* prev = nullptr;

    while(true) {
        ListNode* lastNodePrevPart = prev;
        ListNode* lastNodeSubList = curr;
        ListNode* next = nullptr;

        for(int i=0; curr!=nullptr && i<k; i++) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        if(lastNodePrevPart != nullptr)
            lastNodePrevPart->next = prev;
        else
            head = prev;

        lastNodeSubList->next = curr;

        if(curr == nullptr) break;
        prev = lastNodeSubList;
    }
    return head;
}
```

## 🧪 Dry Run

Input:
1 → 2 → 3 → 4 → 5 → 6
k = 3

Output:
3 → 2 → 1 → 6 → 5 → 4

---

# 4️⃣ Reverse Alternating K-element Sub-list (Medium)

Reverse first K nodes, skip next K nodes.

## 🧪 Dry Run

Input:
1 → 2 → 3 → 4 → 5 → 6 → 7 → 8
k = 2

Reverse 1,2 → 2,1  
Skip 3,4  
Reverse 5,6 → 6,5  
Skip 7,8  

Output:
2 → 1 → 3 → 4 → 6 → 5 → 7 → 8

---

# 5️⃣ Rotate a LinkedList (Medium)

Rotate right by k nodes.

## C++ Code
```cpp
ListNode* rotateRight(ListNode* head, int k) {
    if(!head || !head->next || k<=0) return head;

    ListNode* last = head;
    int length = 1;

    while(last->next) {
        last = last->next;
        length++;
    }

    last->next = head;

    k = k % length;
    int skip = length - k;

    ListNode* newLast = head;
    for(int i=0;i<skip-1;i++)
        newLast = newLast->next;

    head = newLast->next;
    newLast->next = nullptr;

    return head;
}
```

## 🧪 Dry Run

Input:
1 → 2 → 3 → 4 → 5
k = 2

Output:
4 → 5 → 1 → 2 → 3

---

# ✅ Summary

✔ Uses pointer manipulation  
✔ No extra space  
✔ Key pointers: prev, curr, next  
✔ Used in top interview problems  

---

# 🧠 Pointer Trick Reminder

Always store `next = curr->next`
Before changing `curr->next`

Otherwise you lose the list.
