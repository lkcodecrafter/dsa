# Fast & Slow Pointers – 15 Lessons (Selected)

## 📌 Introduction to Fast & Slow Pointers Pattern
The **Fast & Slow pointers** (also called tortoise & hare) is a technique where two pointers move through the data structure at different speeds.
It's particularly useful for linked lists and cycles detection, and often gives O(n) time with O(1) extra space.

**When to use:**
- Detect cycles in linked lists or arrays
- Find middle element in one pass
- Find start of cycle
- Check properties related to repeating sequences

---

## 1. LinkedList Cycle (Easy)
**Problem:** Given the head of a linked list, determine if the list has a cycle in it.  
**Idea:** Move `slow` by 1 and `fast` by 2. If they meet, cycle exists.

**C++ Code:**
```cpp
bool hasCycle(ListNode* head) {
    if(!head) return false;
    ListNode *slow = head, *fast = head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return true;
    }
    return false;
}
```

---

## 2. Middle of the LinkedList (Easy)
**Problem:** Return the middle node of a singly linked list. If there are two middle nodes, return the second one.  
**Idea:** Move `fast` by 2, `slow` by 1; when `fast` reaches end, `slow` is middle.

**C++ Code:**
```cpp
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```

---

## 3. Start of LinkedList Cycle (Medium)
**Problem:** Given a linked list that contains a cycle, return the node where the cycle begins. If there is no cycle, return null.  
**Idea (Floyd's algorithm):** First detect meeting point. Then move one pointer to head and advance both by 1 — they meet at cycle start.

**C++ Code:**
```cpp
ListNode* detectCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) break;
    }
    if(!fast || !fast->next) return nullptr; // no cycle

    slow = head;
    while(slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}
```

---

## 4. Happy Number (Medium)
**Problem:** Determine if a number is happy. A number is happy if repeatedly summing the square of digits eventually equals 1.  
**Idea:** Use fast & slow on the sequence of transformed numbers to detect cycles (instead of a `set`).

**C++ Code:**
```cpp
int nextNum(int x){
    int s=0;
    while(x){
        int d = x%10;
        s += d*d;
        x/=10;
    }
    return s;
}

bool isHappy(int n) {
    int slow = n, fast = n;
    do {
        slow = nextNum(slow);
        fast = nextNum(nextNum(fast));
    } while(slow != fast);
    return slow == 1;
}
```

---

## 5. Problem Challenge 1: Palindrome LinkedList (Medium)
**Problem:** Determine if a singly linked list is a palindrome.  
**Idea:** Use fast/slow to find middle, reverse second half, compare halves, and (optionally) restore list.

**C++ Code:**
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while(head) {
        ListNode* nxt = head->next;
        head->next = prev;
        prev = head;
        head = nxt;
    }
    return prev;
}

bool isPalindrome(ListNode* head) {
    if(!head || !head->next) return true;

    // find middle
    ListNode *slow = head, *fast = head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // reverse second half
    ListNode* second = reverseList(slow);
    ListNode* first = head;

    // compare
    ListNode* p1 = first;
    ListNode* p2 = second;
    bool pal = true;
    while(p2) {
        if(p1->val != p2->val) { pal = false; break; }
        p1 = p1->next;
        p2 = p2->next;
    }

    // (optional) restore second half: reverseList(second);

    return pal;
}
```

---

## 6. Problem Challenge 2: Rearrange a LinkedList (Medium)
**Problem:** Rearrange a linked list such that nodes are re-ordered: L0→Ln→L1→Ln-1→L2→Ln-2→…  
**Idea:** Find middle with fast/slow, reverse second half, then merge two lists alternatingly.

**C++ Code:**
```cpp
void reorderList(ListNode* head) {
    if(!head || !head->next) return;
    // find middle
    ListNode *slow=head, *fast=head;
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    // reverse second half
    ListNode* second = reverseList(slow->next);
    slow->next = nullptr; // split

    // merge first and second
    ListNode* first = head;
    while(second) {
        ListNode* t1 = first->next;
        ListNode* t2 = second->next;
        first->next = second;
        second->next = t1;
        first = t1;
        second = t2;
    }
}
```

---

## 7. Problem Challenge 3: Cycle in a Circular Array (Hard)
**Problem:** Given a circular array of integers, determine if there is a cycle in the array. The cycle must be all-increasing or all-decreasing (no direction changes) and length > 1.  
**Idea:** Use fast/slow but take care to maintain direction and avoid single-element loops. Mark visited indices to avoid re-checking.

**C++ Code (outline):**
```cpp
int nextIndex(const vector<int>& nums, int cur, bool forward) {
    bool dir = nums[cur] >= 0;
    if(dir != forward) return -1; // direction change
    int n = nums.size();
    int next = (cur + nums[cur]) % n;
    if(next < 0) next += n;
    if(next == cur) return -1; // single-element loop not allowed
    return next;
}

bool circularArrayLoop(vector<int>& nums) {
    int n = nums.size();
    for(int i=0;i<n;i++) {
        int slow = i, fast = i;
        bool forward = nums[i] >= 0;
        while(true) {
            slow = nextIndex(nums, slow, forward);
            if(slow == -1) break;
            fast = nextIndex(nums, fast, forward);
            if(fast == -1) break;
            fast = nextIndex(nums, fast, forward);
            if(fast == -1) break;
            if(slow == fast) return true;
        }
        // optionally mark all nodes in this traversal as 0 to skip later
    }
    return false;
}
```

---

## ✅ Notes & Tips
- Fast & Slow is memory-efficient and often O(n) time.  
- Be careful with edge cases: direction flips, single-node loops, and null pointers.  
- Practice dry runs on small examples to internalize pointer movements.

---

## 📚 Want more?
I can:
- Add complete 15 lessons and more hard problems
- Provide diagrams and dry runs
- Convert to PDF or combine with previous READMEs
