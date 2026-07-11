# Module 8: Trees & Heaps (Lectures 99–113)

## 📋 Syllabus
*   **Binary Trees:** Traversals (Pre, In, Post, Level Order, Morris Traversal), Height, Diameter, Left/Right/Top View, Construct from Pre/In/Post Order, Vertical/Diagonal/Boundary Traversal.
*   **Binary Search Tree (BST):** Search, Insertion, Deletion, LCA, Check BST, Merge Two BSTs, Largest BST in Binary Tree.
*   **AVL Trees:** Rotations (LL, RR, LR, RL), Insertion/Deletion.
*   **Heaps:** Heapify, Heap Sort, Priority Queue, Kth Largest/Smallest, Median in Stream, Merge K Sorted Lists.

---

## 🟢 Section 1: Binary Trees

### 🎯 Solution 8.1: Morris Inorder Traversal
*   **Concept:** Perform inorder traversal with $O(1)$ auxiliary space by constructing temporary links (threads) from predecessor nodes back to the current node.
*   **C++ Code:**
```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

#include <vector>

std::vector<int> morrisInorder(TreeNode* root) {
    std::vector<int> inorder;
    TreeNode* curr = root;
    
    while (curr != nullptr) {
        if (curr->left == nullptr) {
            inorder.push_back(curr->val);
            curr = curr->right;
        } else {
            // Find inorder predecessor
            TreeNode* pred = curr->left;
            while (pred->right != nullptr && pred->right != curr) {
                pred = pred->right;
            }
            
            // Make thread
            if (pred->right == nullptr) {
                pred->right = curr;
                curr = curr->left;
            } 
            // Break thread
            else {
                pred->right = nullptr;
                inorder.push_back(curr->val);
                curr = curr->right;
            }
        }
    }
    return inorder;
}
```
*   **Complexity:** Time: $O(N)$, Space: $O(1)$ auxiliary.

### 🎯 Solution 8.2: Binary Tree Heights, Diameters, Views & Construct Tree
*   **C++ Code:**
```cpp
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

// 1. Height of Binary Tree
int height(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

// 2. Diameter of Binary Tree
int getDiameter(TreeNode* root, int& d) {
    if (root == nullptr) return 0;
    int lh = getDiameter(root->left, d);
    int rh = getDiameter(root->right, d);
    d = std::max(d, lh + rh);
    return 1 + std::max(lh, rh);
}

// 3. Right View of Binary Tree
void rightView(TreeNode* root, int level, std::vector<int>& ans) {
    if (root == nullptr) return;
    if (level == ans.size()) ans.push_back(root->val);
    rightView(root->right, level + 1, ans);
    rightView(root->left, level + 1, ans);
}

// 4. Construct Tree from Preorder & Inorder
TreeNode* buildHelper(const std::vector<int>& pre, int& preIdx, const std::vector<int>& in, int inStart, int inEnd, std::map<int, int>& m) {
    if (inStart > inEnd) return nullptr;
    int rootVal = pre[preIdx++];
    TreeNode* root = new TreeNode(rootVal);
    int inIdx = m[rootVal];
    root->left = buildHelper(pre, preIdx, in, inStart, inIdx - 1, m);
    root->right = buildHelper(pre, preIdx, in, inIdx + 1, inEnd, m);
    return root;
}
```
*   **Complexity:** Time: $O(N)$, Space: $O(N)$.

---

## 🟢 Section 2: Binary Search Tree (BST)

### 🎯 Solution 8.3: Validate BST & BST Operations
*   **C++ Code:**
```cpp
#include <climits>

// 1. Validate BST
bool isValidBST(TreeNode* root, long long minVal = LLONG_MIN, long long maxVal = LLONG_MAX) {
    if (root == nullptr) return true;
    if (root->val <= minVal || root->val >= maxVal) return false;
    return isValidBST(root->left, minVal, root->val) && 
           isValidBST(root->right, root->val, maxVal);
}

// 2. Insert into BST
TreeNode* insertBST(TreeNode* root, int val) {
    if (root == nullptr) return new TreeNode(val);
    if (val < root->val) root->left = insertBST(root->left, val);
    else root->right = insertBST(root->right, val);
    return root;
}

// 3. Delete from BST
TreeNode* getSuccessor(TreeNode* curr) {
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;
    if (key < root->val) root->left = deleteNode(root->left, key);
    else if (key > root->val) root->right = deleteNode(root->right, key);
    else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        TreeNode* succ = getSuccessor(root);
        root->val = succ->val;
        root->right = deleteNode(root->right, succ->val);
    }
    return root;
}
```
*   **Complexity:** Time: $O(H)$ where $H$ is tree height (averages $O(\log N)$), Space: $O(H)$ stack recursion.

---

## 🟢 Section 3: AVL Trees

### 🎯 Solution 8.4: AVL Tree Rotations & Insertion
*   **C++ Code:**
```cpp
struct AVLNode {
    int val;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int x) : val(x), left(nullptr), right(nullptr), height(1) {}
};

int getHeight(AVLNode* n) { return n ? n->height : 0; }
int getBalance(AVLNode* n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

AVLNode* insertAVL(AVLNode* node, int val) {
    if (!node) return new AVLNode(val);
    if (val < node->val) node->left = insertAVL(node->left, val);
    else if (val > node->val) node->right = insertAVL(node->right, val);
    else return node;
    
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);
    
    // LL Case
    if (balance > 1 && val < node->left->val) return rightRotate(node);
    // RR Case
    if (balance < -1 && val > node->right->val) return leftRotate(node);
    // LR Case
    if (balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // RL Case
    if (balance < -1 && val < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
```
*   **Complexity:** Time: $O(\log N)$ for insertion/rotations, Space: $O(\log N)$.

---

## 🟢 Section 4: Heaps

### 🎯 Solution 8.5: Heapify, Heap Sort & Priority Queues
*   **C++ Code:**
```cpp
#include <vector>
#include <queue>
#include <algorithm>

// 1. Max Heapify
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// 2. Heap Sort
void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 3. Find Median in a Stream
class MedianFinder {
    std::priority_queue<int> maxHeap; // Stores smaller half
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap; // Stores larger half
public:
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        if (maxHeap.size() < minHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) return maxHeap.top();
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};
```
*   **Complexity:**
    *   Heap Sort: Time $O(N \log N)$, Space $O(1)$.
    *   Median Finder: Time $O(\log N)$ for `addNum`, $O(1)$ for `findMedian`, Space $O(N)$.
