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

This is the standard Happy Number algorithm using
👉 Floyd’s Cycle Detection (slow/fast pointers)
— same idea as detecting a loop in a linked list.

⭐ First: What is a Happy Number?

A number is happy if:

You repeatedly replace it with the sum of the squares of its digits, and eventually reach 1.

Example:

19 → 82 → 68 → 100 → 1


So 19 is happy.

Unhappy numbers fall into a loop:

2 → 4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4 (loop)


The cycle NEVER reaches 1.

⭐ Why Slow & Fast Pointers?

Because:

Happy number sequence eventually ends at 1

Unhappy number sequences enter a cycle

We detect that cycle using:

slow moves 1 step
fast moves 2 steps


If they ever meet (slow == fast), a cycle exists.

If that meeting point is 1, then it’s a happy number.

⭐ Understanding the Code
Function:
bool isHappy(int n) {
    int slow = n, fast = n;
    do {
        slow = nextNum(slow);
        fast = nextNum(nextNum(fast));
    } while(slow != fast);
    return slow == 1;
}

Meaning:

slow moves 1 step each loop:

slow = nextNum(slow);


fast moves 2 steps each loop:

fast = nextNum(nextNum(fast));


The loop ends when slow == fast
(i.e., both pointers meet inside the cycle).

Finally:

if they meet at 1 → happy number
else → unhappy

⭐ Let’s Dry Run With an Example

Let’s pick n = 19 (a happy number).

Step 0:
slow = 19
fast = 19

Loop:
🔁 Iteration 1
slow = nextNum(19)  = 82
fast = nextNum(nextNum(19))
     = nextNum(82)
     = nextNum(68) = 68

Values now:
slow = 82
fast = 68

🔁 Iteration 2
slow = nextNum(82) = 68
fast = nextNum(nextNum(68))
     = nextNum(100)
     = 1

slow = 68
fast = 1

🔁 Iteration 3
slow = nextNum(68) = 100
fast = nextNum(nextNum(1))
     = nextNum(1)
     = 1

slow = 100
fast = 1

🔁 Iteration 4
slow = nextNum(100) = 1
fast = nextNum(nextNum(1)) = 1


🎉 Now:

slow == fast == 1


Loop stops.

Return:

slow == 1 → true

⭐ Dry Run With an Unhappy Number (n = 2)

Eventually both pointers enter the loop:

4 → 16 → 37 → 58 → 89 → 145 → 42 → 20 → 4


slow and fast eventually meet at 4, not 1.

So the function returns:

false

⭐ Summary (Super Simple Version)
✔ slow moves 1 step through the sum-of-squares chain
✔ fast moves 2 steps
✔ if they ever meet at 1 → HAPPY
✔ if they meet at any other number → UNHAPPY (cycle detected)


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

🟦 Let's assume this is our starting situation:
Before reversing:
prev   head
 |      |
 v      v
NULL -> 1 -> 2 -> 3 -> 4 -> NULL


We will follow each line step-by-step.

⭐ Step 1
ListNode* nxt = head->next;

We store the next node so we don’t lose the chain.

 prev     head    nxt
  |        |       |
  v        v       v
NULL ->   1 ->    2 -> 3 -> 4 -> NULL


Nothing changed yet — just saved 2 as nxt.

⭐ Step 2
head->next = prev;

We reverse the arrow of the current node!

Visual:
prev     head     nxt
 |        |        |
 v        v        v
NULL <-  1        2 -> 3 -> 4


The pointer from node 1 now points backward to prev (NULL).

⭐ Step 3
prev = head;

Move prev forward to the current node.

       prev   head    nxt
        |      |       |
        v      v       v
NULL <- 1      2 -> 3 -> 4


prev now sits on node 1.

⭐ Step 4
head = nxt;

Move head forward to keep processing the list.

       prev    head     nxt
        |       |        |
        v       v        v
NULL <- 1      2 -> 3 -> 4


Now we're ready for the next iteration, which will reverse:

2 -> 3  into  2 <- 1


—

⭐ FULL VISUAL of iteration effect

Each loop transforms:

Before:
prev <- 1 <-  ... (already reversed part)
head -> 2 -> 3 -> 4 (not yet reversed)

After:
prev <- 1
        ^
        |
       prev now here

head -> 2 -> 3 -> 4


And it continues like this until the whole list is reversed.

🎉 Final reversed list

After all iterations:

NULL <- 1 <- 2 <- 3 <- 4


Then normally we return prev (which will end at 4).


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

I’ll use the typical example:

📘 Example Input:
1 → 2 → 3 → 4 → 5


The reorder output should be:

1 → 5 → 2 → 4 → 3


Now let’s walk through the code.

⭐ Step 1: Find Middle Using Slow/Fast Pointers
ListNode *slow = head
ListNode *fast = head


Initial:

slow = 1
fast = 1

Loop:
slow = slow->next
fast = fast->next->next

Iteration 1
slow → 2
fast → 3

Iteration 2
slow → 3
fast → 5

Iteration 3

fast->next = NULL → stop

Middle found:
slow = 3

⭐ Step 2: Reverse Second Half

Second half starts at:

slow->next = 4
so second = reverseList(4 → 5)


Reverse:

Before:

4 → 5 → NULL


After reverse:

second = 5 → 4 → NULL


Now split the list:

slow->next = NULL;


So first half becomes:

1 → 2 → 3 → NULL


And second half is:

5 → 4 → NULL

⭐ Step 3: Merge First and Second Alternating

Pointers:

first  = 1 → 2 → 3
second = 5 → 4

🔁 Merge Iteration 1
t1 = first->next  = 2
t2 = second->next = 4

Connect:
first->next  = second   → 1 → 5
second->next = t1       → 5 → 2


New list:

1 → 5 → 2 → 3


Move pointers:

first  = t1 = 2
second = t2 = 4

🔁 Merge Iteration 2
t1 = first->next  = 3
t2 = second->next = NULL

Connect:
first->next = second → 2 → 4
second->next = t1    → 4 → 3


New list:

1 → 5 → 2 → 4 → 3


Move pointers:

first = 3
second = NULL


Loop ends.

🎉 FINAL RESULT

The reordered list is:

1 → 5 → 2 → 4 → 3

⭐ QUICK SUMMARY OF HOW CODE WORKS

Find middle → split into two halves

1 → 2 → 3      and      4 → 5


Reverse second half

5 → 4


Merge alternating

1 → 5 → 2 → 4 → 3



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

This is Circular Array Loop (LeetCode 457) using slow/fast pointers.

🔍 What the problem is asking (simple words)

Given an array where:

Each number tells how many steps to move (forward if +, backward if −)

The array is circular

A valid loop must:

Have more than 1 element

Move in one direction only (all + or all −)

Return true if such a loop exists.

🧠 Helper Function: nextIndex
int nextIndex(const vector<int>& nums, int cur, bool forward)

What it does:

From index cur, it computes the next index while enforcing rules:

❌ Direction must not change

❌ No self-loop (same index)

✅ Circular wrapping allowed

🔹 Example Input (important)

Let’s dry run with:

nums = [2, -1, 1, 2, 2]


This array HAS a valid loop, so the answer should be true.

Indices:

index: 0  1  2  3  4
nums:  2 -1  1  2  2

🚶 Main Loop: i = 0
slow = 0
fast = 0
forward = true (nums[0] = 2)

🔁 While loop starts
🔹 Step 1 — move slow (1 step)
slow = nextIndex(nums, 0, true)


Inside nextIndex:

nums[0] = 2 → direction = forward ✔
next = (0 + 2) % 5 = 2


✅ slow = 2

🔹 Step 2 — move fast (1st step)
fast = nextIndex(nums, 0, true)


Same as slow:

fast = 2

🔹 Step 3 — move fast (2nd step)
fast = nextIndex(nums, 2, true)


Inside:

nums[2] = 1 → direction forward ✔
next = (2 + 1) % 5 = 3


✅ fast = 3

🔹 Compare
slow = 2
fast = 3
→ not equal → continue

🔁 Second iteration
🔹 Move slow
slow = nextIndex(nums, 2, true)

next = (2 + 1) % 5 = 3


✅ slow = 3

🔹 Move fast (1st step)
fast = nextIndex(nums, 3, true)

next = (3 + 2) % 5 = 0


✅ fast = 0

🔹 Move fast (2nd step)
fast = nextIndex(nums, 0, true)

next = (0 + 2) % 5 = 2


✅ fast = 2

🔹 Compare
slow = 3
fast = 2
→ not equal

🔁 Third iteration
🔹 Move slow
slow = nextIndex(nums, 3, true)

next = (3 + 2) % 5 = 0


✅ slow = 0

🔹 Move fast (1st step)
fast = nextIndex(nums, 2, true)

next = 3

🔹 Move fast (2nd step)
fast = nextIndex(nums, 3, true)

next = 0

🎉 Compare
slow = 0
fast = 0


✅ They meet → loop found

Function returns:

true

🔁 Why this is a VALID loop

Cycle:

0 → 2 → 3 → 0


✔ Length > 1
✔ All moves are forward
✔ Circular

🚫 Why -1 matters in nextIndex
Case	Reason
Direction changes	Invalid loop
next == cur	Single-element loop
Hit -1	Stop this start index
🧠 Big Picture Summary

Try each index as a starting point

Use slow & fast pointers

Enforce:

Same direction

Loop length > 1

If slow == fast → valid loop


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
