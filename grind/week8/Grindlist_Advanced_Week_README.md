# Grind 75 - Advanced Week (Hard Problems)

This README contains:
- Easy-to-understand explanations
- Optimal C++ solutions
- Interview notes
- Dry runs
- Pattern recognition

---

# 1. Kth Smallest Element in a BST

## Pattern
Inorder Traversal

BST inorder = sorted order

```cpp
/*
 * Problem: Given the root of a binary search tree and an integer k,
 * return the kth smallest value (1-indexed) of all the values of the nodes in the tree.
 *
 * BST Inorder Traversal Visualization:
 *          5 (root)
 *         / \
 *        3   6
 *       / \
 *      2   4
 *     /
 *    1
 * Inorder sequence: 1 -> 2 -> 3 -> 4 -> 5 -> 6 (Always sorted)
 * If K = 3, we traverse until we visit the 3rd node, which is 3.
 *
 * Memorization Hook:
 * "Inorder traversal of a BST visits nodes in sorted order. Just decrement K at each node
 * visit, and capture the answer when K becomes 0."
 *
 * 1-Minute Quick Revision:
 * 1. Do a standard inorder DFS (Left -> Node -> Right).
 * 2. Keep track of K and decrement on visit.
 * 3. Save result and prune recursion when K reaches 0.
 * 4. Inorder traversal visits BST nodes in sorted (ascending) order.
 */
class Solution {
public:
    int ans;
    int k;

    void inorder(TreeNode* root){
        if(!root || k <= 0) return; // Base case and early pruning

        inorder(root->left); // Traverse left subtree

        // Process current node
        k--;
        if(k==0){
            ans=root->val;
            return;
        }

        inorder(root->right); // Traverse right subtree
    }

    int kthSmallest(TreeNode* root, int K) {
        k=K;
        inorder(root);
        return ans;
    }
};
/*
 * Dry Run:
 * Tree: Same as visualization. K = 3.
 *
 * | Step | Node | Action / Traversal | K value | ans |
 * |------|------|--------------------|---------|-----|
 * | 1    | 5    | Recurse left       | 3       | -   |
 * | 2    | 3    | Recurse left       | 3       | -   |
 * | 3    | 2    | Recurse left       | 3       | -   |
 * | 4    | 1    | Recurse left(Null) | 3       | -   |
 * | 5    | 1    | Visit node: K=2    | 2       | -   |
 * | 6    | 1    | Recurse right(Null)| 2       | -   |
 * | 7    | 2    | Visit node: K=1    | 1       | -   |
 * | 8    | 2    | Recurse right(Null)| 1       | -   |
 * | 9    | 3    | Visit node: K=0    | 0       | 3   |
 * | 10   | 3    | Match: Return ans  | 0       | 3   |
 */

```
### How Recursion Handles Leaf Nodes (null children)
To understand this, let's look at the implementation of inorder:

```cpp
void inorder(TreeNode* root) {
    if (!root || k <= 0) return; // Base case
    inorder(root->left); // Step A
    k--; // Step B
    if (k == 0) {
        ans = root->val;
        return;
    }
    inorder(root->right); // Step C
}
```

### When the recursion reaches Node 1 (a leaf node whose left and right children are nullptr), here is the step-by-step trace of execution:

```cpp
Call inorder(Node 1):
It checks if (!root) -> Node 1 is not null, so it continues.
Execute Step A: inorder(root->left) -> inorder(nullptr):
A new recursive stack frame is created for nullptr.
In this new frame, the base case if (!root) is true, so it executes return; immediately.
Crucial: Because it returned in the base case, k-- was never reached inside the nullptr frame. k remains 3.
Resume inorder(Node 1):
Having completed inorder(root->left) (which returned doing nothing), we proceed to Step B inside the frame for Node 1.
We run k-- -> k decrements from 3 to 2.
We check if (k == 0). Since k == 2, this block is skipped.
Execute Step C: inorder(root->right) -> inorder(nullptr):
Another recursive frame is created for nullptr.
The base case if (!root) is true, so it returns immediately.
Node 1 Finishes:
inorder(Node 1) has now completed all its code and returns control back to its parent caller, which is inorder(Node 2).
Step-by-Step Recursion Visual Stack
inorder(Node 5) [k=3]
  └── inorder(Node 3) [k=3]
        └── inorder(Node 2) [k=3]
              └── inorder(Node 1) [k=3]
                    ├── inorder(nullptr)  <── Returns immediately (Base case, no k change)
                    ├── k--               <── Decrements to 2 (k is now 2)
                    └── inorder(nullptr)  <── Returns immediately (Base case, no k change)
                    [Node 1 returns back to Node 2]
Once Node 1 returns, Node 2 resumes, decrements k to 1, and then returns back to Node 3. Node 3 resumes, decrements k to 0, matches the k == 0 check, sets ans = 3, and returns.

```
### Dry Run

BST:
      5
     / \
    3   6
   / \
  2   4

Inorder:
2 3 4 5 6

k=3

Answer = 4

Time: O(n)

---

# 2. Minimum Window Substring

## Pattern
Sliding Window

```cpp
/*
 * Problem: Given two strings s and t of lengths m and n respectively, return the
 * minimum window substring of s such that every character in t (including duplicates)
 * is included in the window.
 *
 * Sliding Window Visualization:
 * s = "ADOBECODEBANC", t = "ABC"
 * Required characters frequency: {A:1, B:1, C:1}, count = 3
 *
 *   [A D O B E C] O D E B A N C  -> Valid window found ("ADOBEC", len=6)
 *    L         R
 *
 *   A [D O B E C O D E B A] N C  -> Expand right to find another valid window,
 *      L                 R          then shrink left to find: "BANC" (len=4)
 *
 * Memorization Hook:
 * "Expand Right pointer to satisfy the window criteria (count of required chars = 0),
 * then contract Left pointer to optimize and find the minimum length."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize frequency map `cnt` with target string `t`.
 * 2. Keep a count of `required = t.size()`.
 * 3. Loop `right` from 0 to s.size() - 1. Decrement frequency in map. If count was > 0, decrement `required`.
 * 4. When `required == 0`, compare window size, update `minLen` & `start`, restore left character to map,
 *    and if its count becomes > 0, increment `required`. Advance `left`.
 *
 * Detailed Mechanics of the Frequency Map (`cnt`) and `required` Counter:
 *
 * 1. Expanding Phase (Right Pointer):
 *    - Characters from string `t` have initial frequency counts > 0 in `cnt`. All other characters are 0.
 *    - As `right` moves forward, we check `if (cnt[s[right]] > 0)`. If true, it means we found a needed character,
 *      so we decrement `required` by 1.
 *    - We then decrement the frequency `cnt[s[right]]--`. Note that characters NOT in `t` will have counts
 *      less than 0 (e.g., -1, -2), which signifies they are extra/redundant characters in our current window.
 *
 * 2. Shrinking Phase (Left Pointer):
 *    - When `required == 0`, the window has all target characters. We record/update the minimum window.
 *    - To shrink the window, we slide `left` forward. This ejects `s[left]` from the window, so we restore
 *      its frequency in the map using `cnt[s[left]]++`.
 *    - If `cnt[s[left]] > 0` after incrementing, it means we just ejected a required character that was critical,
 *      and its count is no longer satisfied by our window. Therefore, we increment `required++` to break the
 *      `while (required == 0)` loop and force the `right` pointer to expand again.
 */
class Solution {
public:
    string minWindow(string s, string t) {
        vector<int> cnt(128, 0); // Stores required frequencies of characters
        for (char c : t) {
            cnt[c]++;
        }

        int required = t.size(); // Total remaining characters to match
        int left = 0;
        int start = 0;
        int minLen = INT_MAX;

        for (int right = 0; right < s.size(); right++) {
            // If the character is needed, decrement the required count
            if (cnt[s[right]] > 0) {
                required--;
            }
            cnt[s[right]]--; // Decrement availability in map

            // Shrink window from the left as long as it contains all required chars
            while (required == 0) {
                // If current window s[left..right] is smaller than the minimum length found so far
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1; // Update minimum length (e.g. minLen becomes 6 for "ADOBEC")
                    start = left;              // Record the start index of this minimum window (e.g. start = 0)
                }

                // Since we are shifting left to shrink the window, s[left] is leaving the window.
                // We restore s[left] to our required count in the map.
                // Example:
                // - If t = "ABC" and window = "ADOBEC" (left=0, s[0]='A')
                // - cnt['A'] was 0 (indicating 'A' is satisfied in the window)
                // - Removing 'A' makes cnt['A'] = 1 (we need 1 'A' again)
                cnt[s[left]]++; 

                // If cnt[s[left]] becomes positive (> 0), it means we now lack this character.
                // The window is no longer valid.
                // Example:
                // - cnt['A'] is now 1 (> 0). We must increment `required` from 0 to 1.
                // - This breaks the `while (required == 0)` loop, forcing the `right` pointer to expand again.
                // Redundant case:
                // - If window had extra 'A' (e.g., "AADOBEC"), cnt['A'] was -1.
                // - Ejecting first 'A' makes cnt['A'] = 0. Since 0 is not > 0, we don't increment `required`.
                // - The window "ADOBEC" remains valid!
                if (cnt[s[left]] > 0) {
                    required++;
                }
                left++; // Slide left boundary inward
            }
        }

        // Return the substring starting at `start` with length `minLen` (e.g., s.substr(9, 4) for "BANC")
        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};
/*
 * Dry Run:
 * s = "ADOBECODEBANC", t = "ABC" (required starts at 3)
 *
 * | right | s[right] | cnt[s[right]] (after dec) | required | left | Window s[left..right] | Actions / Updates |
 * |-------|----------|---------------------------|----------|------|----------------------|-------------------|
 * | 0     | A        | cnt['A'] = 0              | 2        | 0    | "A"                  |                   |
 * | 1     | D        | cnt['D'] = -1             | 2        | 0    | "AD"                 |                   |
 * | 2     | O        | cnt['O'] = -1             | 2        | 0    | "ADO"                |                   |
 * | 3     | B        | cnt['B'] = 0              | 1        | 0    | "ADOB"               |                   |
 * | 4     | E        | cnt['E'] = -1             | 1        | 0    | "ADOBE"              |                   |
 * | 5     | C        | cnt['C'] = 0              | 0        | 0    | "ADOBEC"             | Valid! minLen=6, start=0. |
 * | -     | -        | (left shrinks to 1)       | 1        | 1    | "DOBEC"              | required becomes 1. |
 * | ...   | ...      | ...                       | ...      | ...  | ...                  |                   |
 * | 12    | C        | cnt['C'] = 0              | 0        | 9    | "BANC"               | Valid! minLen=4, start=9. |
 */
```

### Dry Run

s = ADOBECODEBANC
t = ABC

Answer = BANC

html visualizatoin - ///C:/Users/lalit.k/.gemini/antigravity-ide/brain/d227baf2-8baa-4398-a93c-166afc639554/visualizer.html'

---

# 3. Serialize and Deserialize Binary Tree

## Pattern
Preorder DFS

```cpp
/*
 * Problem: Design an algorithm to serialize and deserialize a binary tree.
 * Serialization converts a tree to a string; deserialization reconstructs it.
 *
 * Preorder DFS Visualization:
 *          1
 *        /   \
 *       2     3
 *            / \
 *           4   5
 *
 * Traversal Order: 1 -> 2 -> null -> null -> 3 -> 4 -> null -> null -> 5 -> null -> null
 * Serialized representation: "1,2,#,#,3,4,#,#,5,#,#,"
 *
 * Memorization Hook:
 * "Preorder traversal (Root, Left, Right) preserves tree topology if null pointers are
 * explicitly recorded (e.g. as '#'). Use stringstream + getline to parse it back."
 *
 * 1-Minute Quick Revision:
 * 1. DFS Preorder helper for serialization: Append `val + ","` or `"#,"`.
 * 2. Deserialization reads tokens split by `,` using `stringstream`.
 * 3. Build tree recursively: Read token. If `#`, return nullptr. Otherwise create node,
 *    assign left = build(), right = build(), and return node.
 */
class Codec {
public:
    // Helper to perform preorder DFS serialization
    void serializeDFS(TreeNode* root, string& s) {
        if (!root) {
            s += "#,";
            return;
        }
        s += to_string(root->val) + ",";
        serializeDFS(root->left, s);
        serializeDFS(root->right, s);
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s;
        serializeDFS(root, s);
        return s;
    }

    // Helper to recursively build the tree during deserialization
    TreeNode* build(stringstream& ss) {
        string token;
        if (!getline(ss, token, ',')) return nullptr; // getline means read till ',' // getline means to take input 

        if (token == "#") {
            return nullptr;
        }

        TreeNode* node = new TreeNode(stoi(token));
        node->left = build(ss);
        node->right = build(ss);
        return node;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        stringstream ss(data);
        return build(ss);
    }
};
/*
 * Dry Run - Deserialization:
 * data = "1,2,#,#,3,#,#,"
 *
 * Token Read | Action
 * -----------|-----------------------------
 * "1"        | Create Node(1)
 * "2"        | Create Node(2) -> Node(1)->left = Node(2)
 * "#"        | Return nullptr -> Node(2)->left = nullptr
 * "#"        | Return nullptr -> Node(2)->right = nullptr
 * "3"        | Create Node(3) -> Node(1)->right = Node(3)
 * "#"        | Return nullptr -> Node(3)->left = nullptr
 * "#"        | Return nullptr -> Node(3)->right = nullptr
 */
```

Time: O(n)

---

# 4. Trapping Rain Water

## Pattern
Two Pointer

```cpp
/*
 * Problem: Given n non-negative integers representing an elevation map where the
 * width of each bar is 1, compute how much water it can trap after raining.
 *
 * ASCII Visualization:
 * Heights: [0, 1, 0, 2, 1, 0, 1, 3]
 *
 *             (3)                             #
 *             (2)             # ~ ~ ~ ~ ~ ~ ~ #
 *             (1)     # ~ ~ ~ # # ~ # ~ ~ ~ ~ #
 *             (0)   _ # _ # _ # # # # # # # # #
 *
 *             Water:    1   2   1   1
 *             Total Water = 1 + 2 + 1 + 1 = 5 units
 *
 * Memorization Hook:
 * "The water above any bar is bounded by the shorter of the maximum heights on its left
 * and right sides. Two pointers move inward, always advancing the smaller height side."
 *
 * 1-Minute Quick Revision:
 * 1. Two pointers: `left = 0`, `right = n - 1`.
 * 2. Keep track of `leftMax = 0` and `rightMax = 0`.
 * 3. If `h[left] < h[right]`: update `leftMax`, add `leftMax - h[left]` to water, left++.
 * 4. Otherwise: update `rightMax`, add `rightMax - h[right]` to water, right--.
 */
class Solution {
public:
    int trap(vector<int>& h) {
        if (h.empty()) return 0;

        int left = 0;
        int right = h.size() - 1;
        int leftMax = 0;
        int rightMax = 0;
        int water = 0;

        while (left < right) {
            // Process the side with the lower height to ensure we don't overestimate water capacity
            if (h[left] < h[right]) {
                leftMax = max(leftMax, h[left]);
                water += leftMax - h[left]; // Water is difference from maximum wall on left
                left++;
            } else {
                rightMax = max(rightMax, h[right]);
                water += rightMax - h[right]; // Water is difference from maximum wall on right
                right--;
            }
        }

        return water;
    }
};
/*
 * Dry Run:
 * Heights: [0, 2, 0, 1, 3]
 *
 * | left | right | h[left] | h[right] | leftMax | rightMax | Water added | Next Pointers |
 * |------|-------|---------|----------|---------|----------|-------------|---------------|
 * | 0    | 4     | 0       | 3        | 0       | 0        | 0           | left -> 1     |
 * | 1    | 4     | 2       | 3        | 2       | 0        | 2-2 = 0     | left -> 2     |
 * | 2    | 4     | 0       | 3        | 2       | 0        | 2-0 = 2     | left -> 3     |
 * | 3    | 4     | 1       | 3        | 2       | 0        | 2-1 = 1     | left -> 4     |
 * Loops ends as left == right (4 == 4). Total Water = 3.
 */
```

### Dry Run

0 1 0 2 1 0 1 3

Collected Water = 6

---

# 5. Find Median from Data Stream

## Pattern
Two Heaps

```cpp
/*
 * Problem: Design a data structure that supports adding numbers from a data stream and
 * finding the median of the current list of numbers.
 *
 * Two Heaps Visualization:
 * Stream: [3, 1, 5, 4]
 *
 *       [ Lower Half (Max Heap) ]         [ Upper Half (Min Heap) ]
 *            Stores: [3, 1]                    Stores: [5, 4]
 *           (Top is Max = 3)                  (Top is Min = 4)
 *
 * Since size of both is equal, Median = (left.top() + right.top()) / 2.0 = (3 + 4) / 2 = 3.5
 *
 * Memorization Hook:
 * "Left see-saw is Max Heap (highest of lower half). Right see-saw is Min Heap (lowest
 * of upper half). Keep their sizes balanced so the median is always at the center tops."
 *
 * 1-Minute Quick Revision:
 * 1. `left` (max heap) stores smaller half; `right` (min heap) stores larger half.
 * 2. `addNum`: Push to `left`, transfer `left.top()` to `right`, then if `right.size() > left.size()`, transfer `right.top()` back to `left`.
 * 3. `findMedian`: If `left` is larger, median is `left.top()`, else average of `left.top()` and `right.top()`.


1-Minute Quick Review
Max Heap (left): Keeps the maximum element of the smaller half of numbers at the top.
Min Heap (right): Keeps the minimum element of the larger half of numbers at the top.
right.push(left.top()):
First, we push the new number onto the left heap to let it sort.
We then take the largest element of this smaller half (left.top()) and push it to the right heap (larger half).
This ensures the new number finds its correct sorted division.
Balancing Step (right.size() > left.size()): If the larger half grows larger than the smaller half, we shift the smallest element of the larger half (right.top()) back to left.


 */
class MedianFinder {
    /*
     * Visualizing Heaps:
     * 
     *      Max Heap (left)                     Min Heap (right)
     *   [ Root / Top (Largest) ]            [ Root / Top (Smallest) ]
     *         /         \                         /         \
     *    [Smaller]     [Smaller]             [Larger]      [Larger]
     * 
     * - `left` stores the smaller half of the numbers so far.
     *   Its root (left.top()) is the MAXIMUM of these smaller numbers.
     * 
     * - `right` stores the larger half of the numbers so far.
     *   Its root (right.top()) is the MINIMUM of these larger numbers.
     */
    priority_queue<int> left; // Max Heap containing elements <= median
    priority_queue<int, vector<int>, greater<int>> right; // Min Heap containing elements >= median

public:
    void addNum(int num) {
        /*
         * Let's trace adding values: 5, then 2, then 10.
         * 
         * ==========================================
         * STEP 1: addNum(5)
         * ==========================================
         * 1. left.push(5)
         *    - left (Max Heap): [5] (top is 5)
         * 
         * 2. right.push(left.top()) -> right.push(5)
         *    - We take the largest from the smaller half (5) and move it to the larger half.
         *    - left.pop() -> left becomes empty []
         *    - right (Min Heap): [5] (top is 5)
         * 
         * 3. if (right.size() > left.size()) -> (1 > 0) is TRUE
         *    - Since the larger half has more elements, move the minimum of the larger half (5) to the smaller half.
         *    - left.push(right.top()) -> left.push(5)
         *    - right.pop() -> right becomes empty []
         *    - State: left = [5], right = [] (Median = 5)
         * 
         * ==========================================
         * STEP 2: addNum(2)
         * ==========================================
         * 1. left.push(2)
         *    - left (Max Heap): [5, 2] (top is 5, because Max Heap keeps largest at top)
         * 
         * 2. right.push(left.top()) -> right.push(5)
         *    - We take the largest of the left heap (5) and move it to the right heap.
         *    - left.pop() -> left becomes [2] (top is 2)
         *    - right (Min Heap): [5] (top is 5)
         * 
         * 3. if (right.size() > left.size()) -> (1 > 1) is FALSE
         *    - No balancing needed.
         *    - State: left = [2] (top: 2), right = [5] (top: 5) (Median = (2 + 5) / 2.0 = 3.5)
         * 
         * ==========================================
         * STEP 3: addNum(10)
         * ==========================================
         * 1. left.push(10)
         *    - left (Max Heap): [10, 2] (top is 10)
         * 
         * 2. right.push(left.top()) -> right.push(10)
         *    - We take the largest of the left heap (10) and move it to the right heap.
         *    - left.pop() -> left becomes [2] (top is 2)
         *    - right (Min Heap): [5, 10] (top is 5, because Min Heap keeps smallest at top)
         * 
         * 3. if (right.size() > left.size()) -> (2 > 1) is TRUE
         *    - Move the minimum of the larger half (right.top() which is 5) to the smaller half.
         *    - left.push(right.top()) -> left.push(5)
         *    - right.pop() -> right becomes [10] (top is 10)
         *    - State: left = [5, 2] (top: 5), right = [10] (top: 10)
         * 
         *    Calculating Median:
         *    - Since left.size() (2) > right.size() (1), we return left.top() which is 5.
         *    - This matches the sorted stream [2, 5, 10] where the median is 5.
         * 
         * Heap Properties Kept:
         * 1. Every element in left heap <= every element in right heap.
         * 2. (left.size() - right.size()) is either 0 or 1.
         * 3. Median calculation:
         *    - If left.size() > right.size(): left.top() is the median.
         *    - If left.size() == right.size(): (left.top() + right.top()) / 2.0 is the median.
         */
        left.push(num);

        // Balance step 1: Send the maximum of left heap to right heap
        // This ensures the new number finds its correct position among the two halves
        right.push(left.top());
        left.pop();

        // Balance step 2: Keep left size >= right size
        if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian() {
        if (left.size() > right.size()) {
            return left.top();
        }
        return (left.top() + right.top()) / 2.0;
    }
};
/*
 * Dry Run:
 * Add Sequence: 3, 1, 5
 *
 * | Action   | Left Heap (Max) | Right Heap (Min) | Balancing Steps Done | Median |
 * |----------|-----------------|------------------|----------------------|--------|
 * | Add(3)   | [3]             | []               | right.size() > left size -> push to left. | 3.0 |
 * | Add(1)   | [1]             | [3]              | left has 1, right has 3. | 2.0 |
 * | Add(5)   | [3, 1]          | [5]              | left size > right size. | 3.0 |
 */
```

Time:
Add = O(log n)
Median = O(1)

---

# 6. Word Ladder

## Pattern
BFS

```cpp
/*
 * Problem: Given two words, beginWord and endWord, and a dictionary wordList, return the
 * number of words in the shortest transformation sequence from beginWord to endWord.
 *
 * Graph BFS Visualization:
 * beginWord = "hit", endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log","cog"]
 *
 *          [hit] (Level 1)
 *            |
 *          [hot] (Level 2)
 *         /     \
 *      [dot]   [lot] (Level 3)
 *        |       |
 *      [dog]   [log] (Level 4)
 *        \       /
 *          [cog] (Level 5) - Target Found!
 *
 * Memorization Hook:
 * "BFS explores shortest paths level-by-level like ripples in water. Changing one character
 * at a time constructs the edges dynamically. Erase from dict to prevent going backward."
 *
 * 1-Minute Quick Revision:
 * 1. Place `wordList` into a hash set `dict` for O(1) query.
 * 2. Push `beginWord` to Queue; set level = 1.
 * 3. Process level-by-level: mutate each character of the popped word from 'a' to 'z'.
 * 4. If mutation matches a word in `dict`, push to Queue and remove it from `dict`.
 * 5. Return current level when mutated word matches `endWord`.
 */
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord)) return 0; // If endWord is not in dictionary, path is impossible

        queue<string> q;
        q.push(beginWord);
        int level = 1;

        while (!q.empty()) {
            int size = q.size(); // Number of words at current level

            while (size--) {
                string word = q.front();
                q.pop();

                if (word == endWord) return level;

                // Mutate each character position
                for (int i = 0; i < word.size(); i++) {
                    char original = word[i];

                    for (char c = 'a'; c <= 'z'; c++) {
                        word[i] = c;

                        if (dict.count(word)) {
                            q.push(word);
                            dict.erase(word); // Prevent infinite loops
                        }
                    }
                    word[i] = original; // Revert mutation
                }
            }
            level++; // Move to next level
        }

        return 0; // Target endWord could not be reached
    }
};
/*
 * Dry Run:
 * beginWord = "hit", endWord = "cog", wordList = ["hot", "cog"]
 *
 * | Level | Queue State | Popped Word | Mutation | In Dict? | Next Queue State | Dict State |
 * |-------|-------------|-------------|----------|----------|------------------|------------|
 * | 1     | ["hit"]     | "hit"       | "hot"    | Yes      | ["hot"]          | {"cog"}    |
 * | 2     | ["hot"]     | "hot"       | "cog"    | No       | []               | {"cog"} (no intermediate node) |
 * Loop exits, returns 0 because "cog" wasn't reachable from "hot" directly.
 */
```

---

# 7. Basic Calculator

## Pattern
Stack

```cpp
/*
 * Problem: Implement a basic calculator to evaluate a simple expression string.
 * The string contains parentheses, '+', '-', and non-negative integers.
 *
 * Stack Context Switch Visualization:
 * Expression: 5 - (3 + 2)
 *
 * 1. Read '5': result = 5
 * 2. Read '-': sign = -1
 * 3. Read '(': Push result (5) and sign (-1) to Stack. Reset result = 0, sign = 1.
 *              Stack: [5, -1]
 * 4. Read '3': result = 3
 * 5. Read '+': sign = 1
 * 6. Read '2': result = 3 + 1 * 2 = 5
 * 7. Read ')': Pop sign (-1) -> result = 5 * -1 = -5
 *              Pop result (5) -> result = -5 + 5 = 0
 *
 * Memorization Hook:
 * "Think of '(' as bookmarking your current story state (result, sign) on the stack,
 * starting a clean sub-expression, and then evaluating it until ')' pops the bookmarks
 * to resume the outer expression."
 *
 * 1-Minute Quick Revision:
 * 1. Track `result` and current operation `sign = 1` or `-1`.
 * 2. Build multi-digit numbers using a while loop when `isdigit` is true.
 * 3. `(` saves state: Push `result`, then push `sign`. Reset `result=0`, `sign=1`.
 * 4. `)` restores state: `result = (result * popped_sign) + popped_prev_result`.
 */
class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        long result = 0;
        int sign = 1; // 1 for '+', -1 for '-'

        for (int i = 0; i < s.size(); i++) {
            if (isdigit(s[i])) {
                long num = 0;
                /*
                 * Parsing Multi-digit Numbers (e.g. "456"):
                 *
                 * Why this loop?
                 * A number in the expression can have multiple digits (like 12 or 456).
                 * We must read all consecutive digit characters and build the actual integer.
                 *
                 * How the math works:
                 * - `s[i] - '0'`: Converts the character digit (e.g., '4') to its actual numeric value (4).
                 *   Example: The ASCII value of '4' is 52 and the ASCII value of '0' is 48.
                 *   Subtracting them gives: '4' - '0' = 52 - 48 = 4.
                 *   This converts characters to their corresponding integer values.
                 * - `num * 10`: Shifts the current parsed number one decimal place to the left
                 *   to make room for the new digit.
                 *
                 * Trace of parsing "456":
                 * - Start: num = 0
                 * - i = index of '4': num = 0 * 10 + ('4' - '0') = 4. i becomes index of '5'.
                 * - i = index of '5': num = 4 * 10 + ('5' - '0') = 45. i becomes index of '6'.
                 * - i = index of '6': num = 45 * 10 + ('6' - '0') = 456. i becomes index of next char (e.g. '+').
                 * - Loop terminates because the next char is not a digit.
                 *
                 * Why `i--` at the end?
                 * After parsing "456", `i` points to the index of the character immediately *after* the number.
                 * But the outer for loop also has `i++` in its iteration. If we don't decrement `i` here,
                 * we will skip the character after the number! So we do `i--` to step back.
                 */
                while (i < s.size() && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                result += sign * num;
                i--; // Adjust index back so the next iteration of the for-loop processes this non-digit char
            } else if (s[i] == '+') {
                sign = 1;
            } else if (s[i] == '-') {
                sign = -1;
            } else if (s[i] == '(') {
                // Save context before entering parenthesis
                st.push(result);
                st.push(sign);
                // Reset context for sub-expression
                result = 0;
                sign = 1;
            } else if (s[i] == ')') {
                // Parenthesis evaluation complete
                result *= st.top(); // Multiply by sign before parenthesis
                st.pop();
                result += st.top(); // Add result before parenthesis
                st.pop();
            }
        }

        return result;
    }
};
/*
 * Dry Run:
 * s = "(1+(4-5))"
 *
 * | i | s[i] | Current Num | Stack       | result | sign | Notes |
 * |---|------|-------------|-------------|--------|------|-------|
 * | 0 | (    | -           | [0, 1]      | 0      | 1    | Push result(0), sign(1). Reset. |
 * | 1 | 1    | 1           | [0, 1]      | 1      | 1    | Add 1*1 |
 * | 2 | +    | -           | [0, 1]      | 1      | 1    | |
 * | 3 | (    | -           | [0, 1, 1, 1]| 0      | 1    | Push result(1), sign(1). Reset. |
 * | 4 | 4    | 4           | [0, 1, 1, 1]| 4      | 1    | Add 4*1 |
 * | 5 | -    | -           | [0, 1, 1, 1]| 4      | -1   | |
 * | 6 | 5    | 5           | [0, 1, 1, 1]| -1     | -1   | Add 5*-1 |
 * | 7 | )    | -           | [0, 1]      | 0      | 1    | result = (-1 * 1) + 1 = 0 |
 * | 8 | )    | -           | []          | 0      | 1    | result = (0 * 1) + 0 = 0 |
 */
```

---

# 8. Maximum Profit in Job Scheduling

## Pattern
Recursion + Memoization + Binary Search

```cpp
/*
 * Problem: Given n jobs where every job has a start time, end time, and profit.
 * Find the maximum profit you can get such that no two jobs overlap.
 *
 * Video Explanation Link: https://www.youtube.com/watch?v=LL0tVxlAeV4
 *
 * Interval Timeline Visualization:
 * Sorted by start times:
 * Job 0: [1, 3] P:50
 * Job 1: [2, 4] P:10
 * Job 2: [3, 5] P:40
 *
 * Time 0------------------------------>
 * J0:  1========3 (Profit: 50)
 * J1:     2========4 (Profit: 10)
 * J2:           3========5 (Profit: 40)
 *
 * Choice Decisions at each job index `i`:
 * - Taken: Current Job Profit + solve(next compatible job index)
 *   We use Binary Search (getNextIndex) to find the first job whose start time >= current job's end time.
 * - Not Taken: solve(i + 1)
 *   Skip current job and move to the immediate next job.
 *
 * Memorization Hook:
 * "Sort jobs by start time. At each job, choose to either TAKE it (and binary search for the next
 * compatible job) or SKIP it (move to index i + 1). Use memoization to cache subproblem results."
 *
 * 1-Minute Quick Revision:
 * 1. Bundle startTime, endTime, and profit together into a list of jobs `array = {start, end, profit}`.
 * 2. Sort the array of jobs by their start time.
 * 3. Recursion function `solve(array, i)` with memoization.
 * 4. In `solve(array, i)`:
 *    - Base case: if `i >= n`, return 0.
 *    - If already computed, return `memo[i]`.
 *    - Find the next compatible job index using binary search `getNextIndex(array, i+1, currentJobEnd)`.
 *    - Calculate `taken` as `profit + solve(array, next)` and `notTaken` as `solve(array, i+1)`.
 *    - Store and return `memo[i] = max(taken, notTaken)`.
 */
class Solution {
public:
    int memo[50001];
    int n;

    // Binary Search to find the first job whose start time is >= currentJobEnd
    int getNextIndex(vector<vector<int>>& array, int l, int currentJobEnd) {
        int r = n - 1;
        int result = n; // If no compatible job is found, return `n` (out-of-bounds, base case handles this)
        
        while (l <= r) {
            int mid = l + (r - l) / 2;
            
            // If mid job's start time is >= current job's end time, we can schedule it.
            // Search left to see if there is an even earlier compatible job.
            if (array[mid][0] >= currentJobEnd) {
                result = mid;
                r = mid - 1;
            } else {
                // Otherwise, search right
                l = mid + 1;
            }
        }
        return result;
    }

    int solve(vector<vector<int>>& array, int i) {
        // Base case: if we have processed all jobs, profit is 0
        if (i >= n) {
            return 0;
        }

        // Return cached result if already computed
        if (memo[i] != -1) {
            return memo[i];
        }

        // Find the index of the next non-overlapping job using binary search
        int next = getNextIndex(array, i + 1, array[i][1]);

        // Choice 1: Take the current job (add its profit + solve for the next compatible job)
        int taken = array[i][2] + solve(array, next);

        // Choice 2: Skip the current job (solve for the next sequential job)
        int notTaken = solve(array, i + 1);

        // Store the maximum of both decisions in the memoization table
        return memo[i] = max(taken, notTaken);
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        n = startTime.size();
        
        // Initialize memoization array with -1
        memset(memo, -1, sizeof(memo));

        // Package start, end, and profit together
        vector<vector<int>> array(n, vector<int>(3, 0));
        for (int i = 0; i < n; i++) {
            array[i][0] = startTime[i];
            array[i][1] = endTime[i];
            array[i][2] = profit[i];
        }

        // Sort the jobs by their start times to enable binary search on start times
        sort(array.begin(), array.end());

        return solve(array, 0);
    }
};

/*
 * Dry Run:
 * startTime = [1, 2, 3], endTime = [3, 4, 5], profit = [50, 10, 40]
 * Sorted Jobs Array:
 * Index 0: [1, 3, 50]
 * Index 1: [2, 4, 10]
 * Index 2: [3, 5, 40]
 *
 * solve(0):
 *   - next compatible job for Job 0 (ends at 3):
 *     Binary search on start times starting from index 1.
 *     We look for first start time >= 3.
 *     - mid = 1 (start=2 < 3) -> search right
 *     - mid = 2 (start=3 >= 3) -> valid, result=2, search left (loop terminates)
 *     - next index = 2.
 *   - taken = 50 + solve(2)
 *   - notTaken = solve(1)
 *
 *   Now let's compute solve(2):
 *     - next compatible job for Job 2 (ends at 5):
 *       Binary search on start times starting from index 3.
 *       Since index 3 >= n, getNextIndex returns 3.
 *     - taken = 40 + solve(3) = 40 + 0 = 40
 *     - notTaken = solve(3) = 0
 *     - memo[2] = max(40, 0) = 40.
 *
 *   Now let's compute solve(1):
 *     - next compatible for Job 1 (ends at 4):
 *       Binary search starting from index 2.
 *       Look for start time >= 4.
 *       - mid = 2 (start=3 < 4) -> search right
 *       - next index = 3 (out of bounds).
 *     - taken = 10 + solve(3) = 10 + 0 = 10
 *     - notTaken = solve(2) = 40 (retrieved from memo[2])
 *     - memo[1] = max(10, 40) = 40.
 *
 *   Back to solve(0):
 *     - taken = 50 + solve(2) = 50 + 40 = 90
 *     - notTaken = solve(1) = 40
 *     - memo[0] = max(90, 40) = 90.
 *
 * Final Return Value is solve(0) = 90.
 */
```

---

# 9. Merge K Sorted Lists

## Pattern
Min Heap

```cpp
/*
 * Problem: Merge k sorted linked lists and return it as one sorted list.
 *
 * Min Heap Visualization:
 * Lists: L1 = [1, 4], L2 = [1, 3], L3 = [2]
 *
 *       [ Priority Queue (Min Heap) ]
 *              Nodes: 1(L1), 1(L2), 2(L3)
 *
 * 1. Pop 1(L1). tail->next = 1(L1). Push L1's next: 4. PQ: [1(L2), 2(L3), 4(L1)]
 * 2. Pop 1(L2). tail->next = 1(L2). Push L2's next: 3. PQ: [2(L3), 3(L2), 4(L1)]
 * 3. Pop 2(L3). tail->next = 2(L3). L3 has no next. PQ: [3(L2), 4(L1)]
 *
 * Memorization Hook:
 * "Use a min-heap to keep track of the head element of all lists. Pop the minimum node,
 * insert it into the merged list, and advance to its next node by pushing it to the heap."
 *
 * 1-Minute Quick Revision:
 * 1. Define custom comparator `cmp` for min-heap (returns `a->val > b->val`).
 * 2. Push all initial non-null heads of the `k` lists into the priority queue.
 * 3. While queue is not empty: Pop minimum, link it to `tail->next`, update `tail`.
 * 4. If popped node has a next element, push `node->next` to PQ. Return `dummy.next`.
 */
class Solution {
public:
    // --- UNDERSTANDING PRIORITY QUEUE & CUSTOM COMPARATORS ---
    // 1. What is a Priority Queue?
    //    A priority queue is a container adapter providing O(1) access to the element with the "highest priority".
    //    Elements are pushed/popped in O(log N) time. It maintains a binary heap structure internally.
    //
    // 2. What is operator() (the call operator) and how is it called?
    //    - Overloading operator() in a struct/class defines a "functor" (function object).
    //    - Inside `std::priority_queue`, an instance of `cmp` is instantiated (e.g., `cmp comp;`).
    //    - During operations like `pq.push(node)` or `pq.pop()`, elements are reordered (heapified).
    //      To compare two elements `a` and `b`, the queue internally calls `comp(a, b)`.
    //    - Since `operator()` is overloaded, `comp(a, b)` invokes `cmp::operator()(a, b)` returning `a->val > b->val`.
    //
    // 3. How does the comparison logic determine Min Heap vs Max Heap?
    //    - Default behavior: std::priority_queue uses std::less<T>, which creates a MAX-HEAP.
    //    - Heapification rule: If the comparator returns true, it indicates that the first argument 'a' (parent)
    //      has lower priority than the second argument 'b' (child), causing them to swap.
    //    - Min-Heap condition: By returning `a->val > b->val`, we return true when 'a' has a larger value than 'b'.
    //      This means larger elements have lower priority and bubble down, keeping the smallest element at the top.
    //
    // 4. Does only the minimum element get pushed when pq.push() is called?
    //    - No, any element can be pushed into the priority queue.
    //    - When `pq.push(node)` is called, the element is appended to the bottom of the binary heap.
    //    - The queue then automatically performs heapification ("bubble up" comparisons) using the comparator `cmp` to reorder elements.
    //    - As a result of this reordering, the smallest element is moved to the root/top (`pq.top()`), but all pushed elements remain stored.
    // ---------------------------------------------------------
    struct cmp {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, cmp> pq;

        // Push the heads of all non-empty lists into the min-heap
        for (auto node : lists) {
            if (node) {
                pq.push(node);
            }
        }

        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (!pq.empty()) {
            auto node = pq.top(); // Retrieve node with the smallest value
            pq.pop();

            tail->next = node; // Link node to merged list
            tail = node;       // Move tail pointer

            // If there's a next node in the list we just popped from, add it to heap
            if (node->next) {
                pq.push(node->next);
            }
        }

        return dummy.next;
    }
};
/*
 * Dry Run:
 * lists = [[1, 5], [2, 6]]
 *
 * | PQ State (values) | Popped Node | tail->next value | Pushed Node |
 * |-------------------|-------------|------------------|-------------|
 * | [1, 2]            | 1           | 1                | 5           |
 * | [2, 5]            | 2           | 2                | 6           |
 * | [5, 6]            | 5           | 5                | null        |
 * | [6]               | 6           | 6                | null        |

 * one more example : 
 * lists = [[1,5],[2,6],[0,10]]
 *
 * 1. Initially, we push the heads of all non-empty lists into the min-heap:
 *    Min Heap = [0, 1, 2] (containing heads of [0,10], [1,5], and [2,6]).
 *
 * 2. Step-by-step Dry Run:
 *    - Step 1: Pop 0 (from list [0,10]). Since 0 has a next element (10), push 10.
 *      Heap State: [1, 2, 10]
 *    - Step 2: Pop 1 (from list [1,5]). Since 1 has a next element (5), push 5.
 *      Heap State: [2, 5, 10]
 *    - Step 3: Pop 2 (from list [2,6]). Since 2 has a next element (6), push 6.
 *      Heap State: [5, 6, 10] (Note: 6 IS pushed here because it is the next element after 2!)
 *    - Step 4: Pop 5 (from list [1,5]). 5 has no next element.
 *      Heap State: [6, 10]
 *    - Step 5: Pop 6 (from list [2,6]). 6 has no next element.
 *      Heap State: [10]
 *    - Step 6: Pop 10 (from list [0,10]). 10 has no next element.
 *      Heap State: []
 *
 * 3. Final Merged Result: 0 -> 1 -> 2 -> 5 -> 6 -> 10.
 *
 * FAQ: "Where is 6 / Why did 6 seem missing?"
 * - In Step 3, when we pop the node with value 2, its next pointer points to the node with value 6.
 * - The code checks `if (node->next)` (which is true since 2->next is 6) and calls `pq.push(node->next)`.
 * - Thus, 6 is successfully added to the priority queue. It is then popped in Step 5 when it becomes the minimum remaining element in the heap.

*/

```

Time: O(N log K)

---

# 10. Largest Rectangle in Histogram

## Pattern
Monotonic Stack

```cpp
/*
 * Problem: Given an array of integers heights representing the histogram's bar
 * height where the width of each bar is 1, find the area of the largest rectangle
 * in the histogram.
 *
 * Monotonic Increasing Stack Visualization:
 * heights = [2, 1, 5, 6, 2, 3, 0] (Note the padded 0 at the end to flush out elements)
 *
 * Stack stores indices of bars in increasing height:
 * [2] (Stack: [0])
 * Next is 1 (heights[1] < heights[0]). Pop 0. h=2, w=1. Area=2. (Stack: [1])
 * [1, 5, 6] (Stack: [1, 2, 3])
 * Next is 2 (heights[4] < heights[3]).
 *   - Pop 3 (h=6). w = 4 - 2 - 1 = 1. Area = 6. (Stack: [1, 2])
 *   - Pop 2 (h=5). w = 4 - 1 - 1 = 2. Area = 10. (Stack: [1])
 *   - Stop popping since heights[1] (1) < heights[4] (2). Push 4. (Stack: [1, 4])
 *
 * Memorization Hook:
 * "Keep heights strictly increasing in the stack. When you hit a bar that is shorter, it
 * acts as a boundary. Pop taller bars and calculate the maximum rectangles they could form."
 *
 * 1-Minute Quick Revision:
 * 1. Push a `0` to the end of `heights` to guarantee all bars are popped and processed.
 * 2. Keep a stack of indices.
 * 3. While `heights[i] < heights[st.top()]`: Pop top index to get height `h`.
 *    Width `w` is `i - st.top() - 1` if stack is not empty, otherwise `i`.
 * 4. Update max area with `h * w`. Push `i` onto the stack.
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st; // Stores indices of bars in monotonic increasing height order
        int ans = 0;

        // 1. FORCE FLUSH: Append a 0 to the end of heights (e.g., [2, 1, 5, 6, 2, 3] becomes [2, 1, 5, 6, 2, 3, 0])
        //    This dummy 0 is smaller than all valid heights, guaranteeing that every index still on the stack
        //    will be popped and processed when the loop reaches this final element.
        heights.push_back(0);

        for (int i = 0; i < heights.size(); i++) {
            // 2. MONOTONIC PROPERTY ENFORCEMENT:
            //    If the current bar at index `i` is shorter than the bar at the stack's top index,
            //    we cannot extend the rectangle of the top bar to the right. The current index `i`
            //    acts as the right boundary. We must pop elements and calculate their maximum rectangle area.
            // Trace for i = 0 (heights[0] = 2):
            // - Since st is empty, `st.empty()` is true, so `!st.empty()` evaluates to false.
            // - The while-loop condition is false, so it is skipped.
            // - We push index 0 onto the stack (st now contains [0]).
            //
            // Trace for i = 1 (heights[1] = 1):
            // - st is not empty (`st.top()` is 0, which corresponds to height 2).
            // - We evaluate: `!st.empty() && heights[st.top()] > heights[i]`
            //                `true && heights[0] > heights[1]`
            //                `true && 2 > 1` (evaluates to true!)
            // - We enter the while loop:
            //   - h = heights[st.top()] = heights[0] = 2.
            //   - st.pop() is called, making the stack empty.
            //   - w = st.empty() ? i : ... => w = i = 1.
            //   - ans = max(ans, 2 * 1) = 2.
            // - Loop condition is checked again; since st is empty, we exit.
            // - We push index 1 onto the stack (st now contains [1]).
            while (!st.empty() && heights[st.top()] > heights[i]) {
                // 3. Popping the top element to calculate its rectangle area:
                int h = heights[st.top()]; // Height of the popped bar
                st.pop();

                // 4. Calculating the width 'w' of the rectangle with height 'h':
                //    - If the stack is empty after popping: the popped bar was the shortest bar seen so far.
                //      It can extend all the way back to index 0. So the width is the entire distance: `w = i`.
                //    - If the stack is not empty: the new top of the stack is the first bar to the left that
                //      is strictly shorter than `h`. This makes `st.top()` the exclusive left boundary,
                //      and `i` the exclusive right boundary. Thus, the width `w = i - st.top() - 1`.
                int w = st.empty() ? i : i - st.top() - 1;

                // 5. Update the maximum rectangle area
                ans = max(ans, h * w);
            }
            // 6. Push the current index `i` onto the stack
            st.push(i);
        }

        return ans;
    }
};
/*
 * Dry Run:
 * Step-by-Step Value Trace for heights = [2, 1, 5, 6, 2, 3]
 * After appending `0` to force flush, the array becomes `heights = [2, 1, 5, 6, 2, 3, 0]`.
 *
 * | Step | i | heights[i] | Stack (Indices) | Action / Loop Condition | Pop Index | h | w calculation | w | Area (h * w) | Max Area (ans) |
 * |------|---|------------|-----------------|-------------------------|-----------|---|---------------|---|--------------|----------------|
 * | 1    | 0 | 2          | `[0]`           | Push `0` (stack empty)  | -         | - | -             | - | -            | 0              |
 * | 2    | 1 | 1          | `[0]`           | `heights[0]` (2) > 1    | `0`       | 2 | `st.empty() ? 1 : ...` | 1 | `2 * 1 = 2`  | 2              |
 * | 3    | 1 | 1          | `[1]`           | Push `1`                | -         | - | -             | - | -            | 2              |
 * | 4    | 2 | 5          | `[1, 2]`        | `heights[1]` (1) < 5    | -         | - | -             | - | -            | 2              |
 * | 5    | 3 | 6          | `[1, 2, 3]`     | `heights[2]` (5) < 6    | -         | - | -             | - | -            | 2              |
 * | 6    | 4 | 2          | `[1, 2, 3]`     | `heights[3]` (6) > 2    | `3`       | 6 | `4 - 2 - 1`   | 1 | `6 * 1 = 6`  | 6              |
 * | 7    | 4 | 2          | `[1, 2]`        | `heights[2]` (5) > 2    | `2`       | 5 | `4 - 1 - 1`   | 2 | `5 * 2 = 10` | 10             |
 * | 8    | 4 | 2          | `[1, 4]`        | Push `4`                | -         | - | -             | - | -            | 10             |
 * | 9    | 5 | 3          | `[1, 4, 5]`     | `heights[4]` (2) < 3    | -         | - | -             | - | -            | 10             |
 * | 10   | 6 | 0 (flush)  | `[1, 4, 5]`     | `heights[5]` (3) > 0    | `5`       | 3 | `6 - 4 - 1`   | 1 | `3 * 1 = 3`  | 10             |
 * | 11   | 6 | 0 (flush)  | `[1, 4]`        | `heights[4]` (2) > 0    | `4`       | 2 | `6 - 1 - 1`   | 4 | `2 * 4 = 8`  | 10             |
 * | 12   | 6 | 0 (flush)  | `[1]`           | `heights[1]` (1) > 0    | `1`       | 1 | `st.empty() ? 6 : ...` | 6 | `1 * 6 = 6`  | 10             |
 * | 13   | 6 | 0 (flush)  | `[6]`           | Push `6`                | -         | - | -             | - | -            | 10             |
 *
 * Final Answer: 10
 */
```

---

# Revision Table

| Problem | Pattern |
|----------|----------|
| Kth Smallest BST | Inorder |
| Minimum Window | Sliding Window |
| Serialize Tree | DFS |
| Trapping Rain Water | Two Pointer |
| Median Stream | Heap |
| Word Ladder | BFS |
| Basic Calculator | Stack |
| Job Scheduling | DP + Binary Search |
| Merge K Lists | Heap |
| Largest Histogram | Monotonic Stack |

# Must Remember

1. Sliding Window
2. Monotonic Stack
3. BFS
4. DFS
5. Heap
6. DP
7. Binary Search
8. Two Pointer

These are among the most frequently asked Google/Meta/Amazon hard patterns.
