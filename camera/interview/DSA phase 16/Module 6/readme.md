# Module 6: Linked Lists (Lectures 78–88)

## 📋 Syllabus
*   **Singly Linked List:** Insertion, Deletion, Reverse, Middle of List, Rotate List, Remove Kth Node, Palindrome List.
*   **Doubly Linked List:** Insertion and Deletion.
*   **Advanced Problems:** Merge Sorted Lists, Detect & Remove Cycle, Add Two Numbers, Flattening a Linked List, Clone List with Random Pointer.

---

## 🟢 Section 1: Singly Linked List Basics

### 🎯 Solution 6.1: Reverse, Middle, Rotate & Palindrome List
*   **C++ Code:**
```cpp
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// 1. Reverse a Singly Linked List in-place
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        Node* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}

// 2. Middle of a Linked List (Tortoise and Hare)
Node* middleNode(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 3. Rotate List by K Places
Node* rotateRight(Node* head, int k) {
    if (head == nullptr || head->next == nullptr || k == 0) return head;
    int len = 1;
    Node* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
        len++;
    }
    tail->next = head; // Connect tail to head to form loop
    k = k % len;
    int steps = len - k;
    Node* newTail = head;
    for (int i = 1; i < steps; i++) {
        newTail = newTail->next;
    }
    Node* newHead = newTail->next;
    newTail->next = nullptr; // Break the cycle
    return newHead;
}

// 4. Check if Palindrome
bool isPalindrome(Node* head) {
    if (head == nullptr || head->next == nullptr) return true;
    Node* mid = middleNode(head);
    Node* secondHalf = reverseList(mid);
    Node* firstHalf = head;
    Node* temp = secondHalf;
    while (temp != nullptr) {
        if (firstHalf->data != temp->data) return false;
        firstHalf = firstHalf->next;
        temp = temp->next;
    }
    return true;
}
```
*   **🔍 Dry Run (Reverse List `[1 -> 2 -> 3]`):**
    *   Initial: `prev = null`, `curr = 1`
    *   **Iter 1:** `nextNode = 2`. Link `1 -> null`. `prev = 1`, `curr = 2`.
    *   **Iter 2:** `nextNode = 3`. Link `2 -> 1`. `prev = 2`, `curr = 3`.
    *   **Iter 3:** `nextNode = null`. Link `3 -> 2`. `prev = 3`, `curr = null`.
    *   Loop ends. Returns `prev (3)` -> `[3 -> 2 -> 1]`.
*   **Complexity:** Time: $O(N)$, Space: $O(1)$.

---

## 🟢 Section 2: Doubly Linked List

### 🎯 Solution 6.2: DLL Insertion & Deletion
*   **C++ Code:**
```cpp
struct DLLNode {
    int data;
    DLLNode* prev;
    DLLNode* next;
    DLLNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Insert at head
DLLNode* insertAtHead(DLLNode* head, int val) {
    DLLNode* temp = new DLLNode(val);
    if (head != nullptr) {
        head->prev = temp;
        temp->next = head;
    }
    return temp;
}

// Delete a Node
DLLNode* deleteNode(DLLNode* head, DLLNode* delNode) {
    if (head == nullptr || delNode == nullptr) return head;
    if (head == delNode) head = delNode->next;
    if (delNode->next != nullptr) delNode->next->prev = delNode->prev;
    if (delNode->prev != nullptr) delNode->prev->next = delNode->next;
    delete delNode;
    return head;
}
```
*   **Complexity:** Time: $O(1)$, Space: $O(1)$.

---

## 🟢 Section 3: Advanced Problems

### 🎯 Solution 6.3: Detect and Remove Loop (Cycle detection)
*   **Problem:** Detect a cycle in a linked list using Floyd's Cycle-Finding Algorithm and break it.
*   **C++ Code:**
```cpp
void detectAndRemoveLoop(Node* head) {
    if (head == nullptr || head->next == nullptr) return;
    Node* slow = head;
    Node* fast = head;
    
    // Step 1: Detect Loop
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }
    
    // Loop exists if pointers met
    if (slow == fast) {
        slow = head;
        // If they meet at the head, handle tail pointing to head
        if (slow == fast) {
            while (fast->next != slow) {
                fast = fast->next;
            }
        } else {
            while (slow->next != fast->next) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        fast->next = nullptr; // Remove loop
    }
}
```
*   **Complexity:** Time: $O(N)$, Space: $O(1)$.

### 🎯 Solution 6.4: Reverse Linked List in K-Groups
*   **C++ Code:**
```cpp
Node* reverseKGroup(Node* head, int k) {
    if (head == nullptr || k == 1) return head;
    
    // Check if there are at least k nodes left
    Node* temp = head;
    for (int i = 0; i < k; i++) {
        if (temp == nullptr) return head;
        temp = temp->next;
    }
    
    Node* prev = nullptr;
    Node* curr = head;
    Node* nextNode = nullptr;
    int count = 0;
    
    while (curr != nullptr && count < k) {
        nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
        count++;
    }
    
    if (nextNode != nullptr) {
        head->next = reverseKGroup(nextNode, k);
    }
    return prev;
}
```
*   **Complexity:** Time: $O(N)$, Space: $O(N / K)$ recursion stack.

### 🎯 Solution 6.5: Merge Sorted Lists, Add Two Numbers, Flattening & Clone List
*   **C++ Code:**
```cpp
// 1. Merge Two Sorted Lists
Node* mergeTwoLists(Node* l1, Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    if (l1->data <= l2->data) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}

// 2. Add Two Numbers represented by Linked Lists
Node* addTwoNumbers(Node* l1, Node* l2) {
    Node dummy(0);
    Node* curr = &dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) { sum += l1->data; l1 = l1->next; }
        if (l2) { sum += l2->data; l2 = l2->next; }
        carry = sum / 10;
        curr->next = new Node(sum % 10);
        curr = curr->next;
    }
    return dummy.next;
}

// 3. Flattening a Linked List
struct FlatNode {
    int data;
    FlatNode* next;
    FlatNode* bottom;
    FlatNode(int val) : data(val), next(nullptr), bottom(nullptr) {}
};

FlatNode* mergeFlat(FlatNode* a, FlatNode* b) {
    if (!a) return b;
    if (!b) return a;
    FlatNode* result;
    if (a->data <= b->data) {
        result = a;
        result->bottom = mergeFlat(a->bottom, b);
    } else {
        result = b;
        result->bottom = mergeFlat(a, b->bottom);
    }
    result->next = nullptr;
    return result;
}

FlatNode* flatten(FlatNode* root) {
    if (!root || !root->next) return root;
    root->next = flatten(root->next);
    root = mergeFlat(root, root->next);
    return root;
}

// 4. Clone List with Random Pointer
struct RandomNode {
    int val;
    RandomNode* next;
    RandomNode* random;
    RandomNode(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

RandomNode* copyRandomList(RandomNode* head) {
    if (!head) return nullptr;
    RandomNode* curr = head;
    // Step 1: Interleave duplicate nodes
    while (curr) {
        RandomNode* temp = new RandomNode(curr->val);
        temp->next = curr->next;
        curr->next = temp;
        curr = temp->next;
    }
    // Step 2: Copy random pointers
    curr = head;
    while (curr) {
        if (curr->random) {
            curr->next->random = curr->random->next;
        }
        curr = curr->next->next;
    }
    // Step 3: Unpack/Separate lists
    curr = head;
    RandomNode* newHead = head->next;
    RandomNode* copy = newHead;
    while (curr) {
        curr->next = curr->next->next;
        if (copy->next) {
            copy->next = copy->next->next;
        }
        curr = curr->next;
        copy = copy->next;
    }
    return newHead;
}
```
*   **Complexity:**
    *   Merge: Time $O(N + M)$, Space $O(N + M)$ stack.
    *   Add Two: Time $O(\max(N, M))$, Space $O(\max(N, M))$ new list.
    *   Flattening: Time $O(N \cdot M)$ where $N$ is vertical height and $M$ is horizontal breadth, Space $O(M)$ recursion.
    *   Clone: Time $O(N)$, Space $O(1)$ auxiliary.
