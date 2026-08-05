# Grind List - Week 1 (C++)

# 1. Two Sum
**Idea:** Store visited numbers in a hash map.

```cpp
/*
 * Problem: Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 * 
 * Pattern: Hash Map (Single Pass)
 *
 * Memorization Hook:
 * "For each number, check if its complement (target - num) is already in our map.
 * If yes, we found the pair. If no, store the current number's index for future matching."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize an unordered_map to store {number -> index}.
 * 2. Loop through nums: calculate need = target - nums[i].
 * 3. If need is found in the map, return {map[need], i}.
 * 4. Otherwise, insert nums[i] into the map and continue.
 * 
 * Dry Run:
 * nums = [2, 7, 11, 15], target = 9
 *
 * | i | nums[i] | need (9 - nums[i]) | map status (before) | Action / Result |
 * |---|---------|-------------------|---------------------|-----------------|
 * | 0 | 2       | 7                 | {}                  | Insert {2: 0}   |
 * | 1 | 7       | 2                 | {2: 0}              | Found! Return {0, 1} |
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp; // Map to store: key = number, value = index

        for (int i = 0; i < nums.size(); i++) {
            int need = target - nums[i]; // The complement we need to reach target

            // If the complement is already in our map, we have found the two numbers
            if (mp.count(need)) {
                return {mp[need], i};
            }

            // Otherwise, store current number and its index in the map
            mp[nums[i]] = i;
        }
        return {}; // Return empty if no solution is found
    }
};
```

---

# 2. Valid Parentheses
**Idea:** Use a stack to track open brackets and match them with closing brackets.

```cpp
/*
 * Problem: Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 *
 * Pattern: Stack Matching
 *
 * Memorization Hook:
 * "Push opening brackets onto the stack. When hitting a closing bracket,
 * it must match the opening bracket at the top of the stack. Pop it upon match."
 *
 * 1-Minute Quick Revision:
 * 1. Use std::stack to track open brackets.
 * 2. Loop through characters:
 *    - If open bracket: push onto stack.
 *    - If closing bracket: check if stack is empty (fail if empty), check top match (fail if mismatch), then pop.
 * 3. Return true if stack is empty at the end.
 *
 * Dry Run:
 * s = "()[]{}"
 *
 * | Step | Char | Stack (before) | Action | Stack (after) |
 * |------|------|----------------|--------|---------------|
 * | 1    | '('  | []             | Push   | ['(']         |
 * | 2    | ')'  | ['(']          | Pop    | []            |
 * | 3    | '['  | []             | Push   | ['[']         |
 * | 4    | ']'  | ['[']          | Pop    | []            |
 * | 5    | '{'  | []             | Push   | ['{']         |
 * | 6    | '}'  | ['{']          | Pop    | []            |
 */
class Solution {
public:
    bool isValid(string s) {
        stack<char> st; // Stack to hold opening brackets

        for (char c : s) {
            // Push opening brackets onto the stack
            if (c == '(' || c == '{' || c == '[') {
                st.push(c);
            } else {
                // If stack is empty and we see a closing bracket, it's invalid
                if (st.empty()) return false;

                // Check if the closing bracket matches the top opening bracket
                if ((c == ')' && st.top() != '(') ||
                    (c == '}' && st.top() != '{') ||
                    (c == ']' && st.top() != '[')) {
                    return false;
                }
                st.pop(); // Pop matched opening bracket
            }
        }
        return st.empty(); // Returns true if all brackets matched and popped
    }
};
```

---

# 3. Merge Two Sorted Lists
**Idea:** Traverse both lists and link nodes in sorted order using a dummy head.

```cpp
/*
 * Problem: Merge two sorted linked lists and return it as a sorted list.
 *
 * Pattern: Two-Pointer Linked List Merge
 *
 * Visual representation:
 * l1: 1 -> 2 -> 4
 * l2: 1 -> 3 -> 4
 * dummy -> tail (moves along, linking smaller nodes)
 *
 * Memorization Hook:
 * "Use a dummy node as the start. Iteratively link the smaller node of the two lists
 * to the dummy's tail, and advance the list pointer. Append the remainder."
 *
 * 1-Minute Quick Revision:
 * 1. Create a dummy node and a tail pointer pointing to it.
 * 2. Loop while both l1 and l2 are non-null:
 *    - Link tail->next to the list with smaller head node.
 *    - Advance that list's head and the tail.
 * 3. Link tail->next to whichever list remains non-null.
 * 4. Return dummy.next.
 *
 * Dry Run:
 * l1 = [1, 2, 4], l2 = [1, 3, 4]
 * Dummy state starts as (0)
 *
 * | Step | l1 head | l2 head | tail->next link | Advanced Pointer |
 * |------|---------|---------|-----------------|------------------|
 * | 1    | 1       | 1       | l2 (value 1)    | l2 -> 3          |
 * | 2    | 1       | 3       | l1 (value 1)    | l1 -> 2          |
 * | 3    | 2       | 3       | l1 (value 2)    | l1 -> 4          |
 * | 4    | 4       | 3       | l2 (value 3)    | l2 -> 4          |
 * | 5    | 4       | 4       | l2 (value 4)    | l2 -> null       |
 * | 6    | 4       | null    | l1 (remainder)  | (loop ends)      |
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);      // Dummy node to simplify edge cases (start of merged list)
        ListNode* tail = &dummy; // Tail pointer to build the list

        // Merge nodes in sorted order
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1; // Link l1
                l1 = l1->next;   // Move l1 pointer
            } else {
                tail->next = l2; // Link l2
                l2 = l2->next;   // Move l2 pointer
            }
            tail = tail->next;   // Move tail pointer forward
        }

        // Attach the remaining nodes of the non-empty list
        tail->next = l1 ? l1 : l2;

        return dummy.next; // Return head of merged list
    }
};
```

---

# 4. Best Time to Buy and Sell Stock
**Idea:** Find the lowest price and calculate the maximum profit dynamically.

```cpp
/*
 * Problem: Find the maximum profit you can achieve by buying one stock and selling it in the future.
 *
 * Pattern: Sliding Minimum / Single Pass Greedy
 *
 * Memorization Hook:
 * "Track the lowest price seen so far. For each stock price, check the potential profit
 * if we sold today, and update the max profit."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize min_price = INT_MAX, max_profit = 0.
 * 2. For each price in prices:
 *    - Update min_price = min(min_price, price).
 *    - Update max_profit = max(max_profit, price - min_price).
 * 3. Return max_profit.
 *
 * Dry Run:
 * prices = [7, 1, 5, 3, 6, 4]
 *
 * | Step | Price | min_price | Profit (price - min_price) | max_profit |
 * |------|-------|-----------|----------------------------|------------|
 * | 1    | 7     | 7         | 0                          | 0          |
 * | 2    | 1     | 1         | 0                          | 0          |
 * | 3    | 5     | 1         | 4                          | 4          |
 * | 4    | 3     | 1         | 2                          | 4          |
 * | 5    | 6     | 1         | 5                          | 5          |
 * | 6    | 4     | 1         | 3                          | 5          |
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mn = INT_MAX; // Track the minimum price seen so far
        int profit = 0;   // Track the maximum profit achieved

        for (int p : prices) {
            mn = min(mn, p);          // Update minimum price
            profit = max(profit, p - mn); // Calculate and update max profit
        }
        return profit;
    }
};
```

---

# 5. Valid Palindrome
**Idea:** Filter out non-alphanumeric characters and compare pointers from both ends.

```cpp
/*
 * Problem: Determine if a string is a palindrome, considering only alphanumeric characters and ignoring cases.
 *
 * Pattern: Two-Pointer Verification
 *
 * Memorization Hook:
 * "Use two pointers, left and right. Clean characters (isalnum and tolower) 
 * first or check them dynamically. Compare outer characters moving inward."
 *
 * 1-Minute Quick Revision:
 * 1. Create a cleaned string of alphanumeric characters converted to lowercase.
 * 2. Use two pointers starting at left = 0 and right = size - 1.
 * 3. While left < right: if characters don't match, return false. Otherwise increment/decrement.
 * 4. Return true if loop finishes.
 *
 * Dry Run:
 * s = "A man, a plan, a canal: Panama"
 * Cleaned: "amanaplanacanalpanama"
 *
 * | left (index) | right (index) | t[left] | t[right] | Match? |
 * |--------------|---------------|---------|----------|--------|
 * | 0 ('a')      | 20 ('a')      | 'a'     | 'a'      | Yes    |
 * | 1 ('m')      | 19 ('m')      | 'm'     | 'm'      | Yes    |
 * | 2 ('a')      | 18 ('a')      | 'a'     | 'a'      | Yes    |
 * ...
 * | 10 ('a')     | 10 ('a')      | loop terminates (left >= right) |
 */
class Solution {
public:
    bool isPalindrome(string s) {
        string t = ""; // Temporary string to store cleaned characters

        // Filter and lowercase alphanumeric characters
        for (char c : s) {
            if (isalnum(c)) {
                t += tolower(c);
            }
        }

        int l = 0, r = (int)t.size() - 1; // Set pointers at boundaries

        // Compare characters from outside in
        while (l < r) {
            if (t[l++] != t[r--]) {
                return false; // Mismatch found
            }
        }
        return true; // All matched
    }
};
```

---

# 6. Invert Binary Tree
**Idea:** Swap left and right child pointers at each node recursively (DFS) or iteratively (BFS).

```cpp
/*
 * Problem: Invert a binary tree (swap left and right subtrees).
 *
 * Pattern: DFS Recursive & BFS Iterative
 *
 * Visual representation:
 *        4                  4
 *      /   \              /   \
 *     2     7     =>     7     2
 *    / \   / \          / \   / \
 *   1   3 6   9        9   6 3   1
 *
 * Memorization Hook:
 * "Swap the current node's left and right children. Recursively invert the left and right subtrees."
 *
 * 1-Minute Quick Revision:
 * 1. If root is null, return null.
 * 2. Swap root->left and root->right.
 * 3. Call invertTree on root->left and root->right.
 * 4. Return root.
 *
 * Dry Run (DFS):
 * Node = 4 (swaps 2 and 7)
 *   Node = 7 (swaps 6 and 9)
 *     Inverts children of 9 and 6 (base cases)
 *   Node = 2 (swaps 1 and 3)
 *     Inverts children of 3 and 1 (base cases)
 */
class Solution {
public:
    // DFS approach: Swap and recurse
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr; // Base case: empty node

        swap(root->left, root->right); // Swap left and right child pointers

        invertTree(root->left);  // Invert left subtree
        invertTree(root->right); // Invert right subtree

        return root;
    }
};

/*
 * BFS approach: Iterative traversal using queue
 * 
 * 1-Minute Quick Revision (BFS):
 * 1. Push root to queue.
 * 2. Loop while queue is not empty:
 *    - Pop front node.
 *    - Swap its left and right pointers.
 *    - Push non-null left and right children into the queue.
 * 3. Return root.
 *
 * Dry Run (BFS):
 * Queue: [4]
 * - Pop 4. Swap 2 and 7. Push 7, 2. Queue: [7, 2]
 * - Pop 7. Swap 6 and 9. Push 9, 6. Queue: [2, 9, 6]
 * - Pop 2. Swap 1 and 3. Push 3, 1. Queue: [9, 6, 3, 1]
 * - Subsequent pops have no children. Loop finishes.
 */
class SolutionBFS {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            swap(node->left, node->right); // Swap child pointers

            // Push children to queue for subsequent level swapping
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return root;
    }
};
```

---

# 7. Valid Anagram
**Idea:** Count character occurrences across both strings and verify balance.

```cpp
/*
 * Problem: Given two strings s and t, return true if t is an anagram of s.
 *
 * Pattern: Frequency Count (Alphabet Array Map)
 *
 * Memorization Hook:
 * "Increment counts for string s, decrement counts for string t.
 * If all counts are zero, they are anagrams."
 *
 * 1-Minute Quick Revision:
 * 1. If lengths of s and t differ, return false.
 * 2. Create a frequency array of size 26 initialized to 0.
 * 3. For each char c in s: increment count at c - 'a'.
 * 4. For each char c in t: decrement count at c - 'a'.
 * 5. Check if any element in the frequency array is not 0 (if so, return false).
 * 6. Return true.
 *
 * Dry Run:
 * s = "anagram", t = "nagaram"
 * Size check: 7 == 7 (continue)
 *
 * | Step | s[i] | Increment Index (s[i]-'a') | t[i] | Decrement Index (t[i]-'a') |
 * |------|------|---------------------------|------|---------------------------|
 * | 1    | 'a'  | cnt[0] -> 1               | 'n'  | cnt[13] -> -1             |
 * | 2    | 'n'  | cnt[13] -> 0              | 'a'  | cnt[0] -> 0               |
 * | 3    | 'a'  | cnt[0] -> 1               | 'g'  | cnt[6] -> -1              |
 * | 4    | 'g'  | cnt[6] -> 0               | 'a'  | cnt[0] -> 0               |
 * | 5    | 'r'  | cnt[17] -> 1              | 'r'  | cnt[17] -> 0              |
 * | 6    | 'a'  | cnt[0] -> 1               | 'a'  | cnt[0] -> 0               |
 * | 7    | 'm'  | cnt[12] -> 1              | 'm'  | cnt[12] -> 0              |
 * All values in cnt are 0 -> return true.
 */
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false; // Anagrams must be same length

        vector<int> cnt(26, 0); // Frequency counter for 26 alphabets

        // Count character occurrences
        for (char c : s) cnt[c - 'a']++;
        for (char c : t) cnt[c - 'a']--;

        // If any frequency is non-zero, it is not an anagram
        for (int x : cnt) {
            if (x != 0) return false;
        }

        return true;
    }
};
```

---

# 8. Binary Search
**Idea:** Divide the range in half iteratively based on comparison with middle value.

```cpp
/*
 * Problem: Given a sorted array nums and a target, search for target. If found, return its index. Otherwise, return -1.
 *
 * Pattern: Binary Search (Two-Pointer Divide and Conquer)
 *
 * Memorization Hook:
 * "Find mid = left + (right - left)/2. If nums[mid] equals target, return mid.
 * If target is smaller, search left half (right = mid - 1). Else, search right half (left = mid + 1)."
 *
 * 1-Minute Quick Revision:
 * 1. Set left = 0, right = nums.size() - 1.
 * 2. Loop while left <= right:
 *    - Calculate mid = left + (right - left) / 2 to prevent integer overflow.
 *    - Check target:
 *      - If nums[mid] == target: return mid.
 *      - If nums[mid] < target: left = mid + 1.
 *      - Else: right = mid - 1.
 * 3. Return -1.
 *
 * Dry Run:
 * nums = [-1, 0, 3, 5, 9, 12], target = 9
 *
 * | Iteration | left | right | mid | nums[mid] | Comparison |
 * |-----------|------|-------|-----|-----------|------------|
 * | 1         | 0    | 5     | 2   | 3         | 3 < 9 -> left = 3 |
 * | 2         | 3    | 5     | 4   | 9         | 9 == 9 -> Return 4 |
 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0, r = (int)nums.size() - 1; // Set boundaries

        while (l <= r) {
            int mid = l + (r - l) / 2; // Find middle element (overflow safe)

            if (nums[mid] == target) {
                return mid; // Target found
            }
            if (nums[mid] < target) {
                l = mid + 1; // Discard left half
            } else {
                r = mid - 1; // Discard right half
            }
        }
        return -1; // Target not found
    }
};
```

---

# 9. Flood Fill
**Idea:** Recursively recolor a connected component using Depth-First Search.

```cpp
/*
 * Problem: Perform a flood fill on the image starting from (sr, sc).
 *
 * Pattern: Depth-First Search (DFS) Grid Traversal
 *
 * Visual representation of Grid:
 * 1 1 1       2 2 2   (Changed starting pixel color and
 * 1 1 0   =>  2 2 0    connected neighbors of same color)
 * 1 0 1       2 0 1
 *
 * Memorization Hook:
 * "Check boundaries and color match. Update current cell to new color.
 * Recursively flood fill 4 neighbors (Up, Down, Left, Right)."
 *
 * 1-Minute Quick Revision:
 * 1. Get the target original color (old_color = image[sr][sc]).
 * 2. If old_color equals the new color, return image immediately.
 * 3. Call recursive DFS helper on (sr, sc).
 * 4. DFS Helper base checks: out of bounds, or image[r][c] != old_color.
 * 5. Update image[r][c] = new_color.
 * 6. Recurse for (r+1, c), (r-1, c), (r, c+1), (r, c-1).
 *
 * Dry Run:
 * image = [[1,1,1],[1,1,0],[1,0,1]], sr=1, sc=1, color=2
 * old_color = 1. sr, sc has value 1.
 * - DFS(1, 1): updates grid[1][1] = 2.
 *   - Recurse DFS(2, 1): grid[2][1] is 0 != 1 -> returns.
 *   - Recurse DFS(0, 1): grid[0][1] is 1 -> updates grid[0][1] = 2.
 *     - Recurse DFS(0, 2): updates grid[0][2] = 2.
 *     - Recurse DFS(0, 0): updates grid[0][0] = 2.
 *   - Recurse DFS(1, 2): grid[1][2] is 0 != 1 -> returns.
 *   - Recurse DFS(1, 0): grid[1][0] is 1 -> updates grid[1][0] = 2.
 */
class Solution {
public:
    void dfs(vector<vector<int>>& img, int r, int c, int old, int color) {
        // Base case: check grid boundary limits
        if (r < 0 || c < 0 || r >= img.size() || c >= img[0].size()) return;

        // Base case: stop if pixel is not of target old color
        if (img[r][c] != old) return;

        img[r][c] = color; // Perform color fill

        // Flood fill 4-directionally
        dfs(img, r + 1, c, old, color); // Down
        dfs(img, r - 1, c, old, color); // Up
        dfs(img, r, c + 1, old, color); // Right
        dfs(img, r, c - 1, old, color); // Left
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int old = image[sr][sc]; // Record original color of starting pixel

        // If target color is same as current color, no changes are needed
        if (old == color) return image;

        dfs(image, sr, sc, old, color);
        return image;
    }
};
```

---

# 10. Lowest Common Ancestor of BST
**Idea:** Walk down the BST to find the split point where p and q diverge.

```cpp
/*
 * Problem: Find the lowest common ancestor (LCA) node of two given nodes p and q in a BST.
 *
 * Pattern: Binary Search Tree Property Search
 *
 * Visual representation:
 *         6 (LCA for 2 and 8)
 *       /   \
 *      2     8
 *     / \
 *    0   4  (2 is LCA for 0 and 4)
 *
 * Memorization Hook:
 * "Use BST properties. If both nodes are smaller than root, go left.
 * If both nodes are larger, go right. Otherwise, the current node is the LCA."
 *
 * 1-Minute Quick Revision:
 * 1. Loop while root is not null:
 *    - If p->val and q->val are both smaller than root->val: root = root->left.
 *    - If p->val and q->val are both larger than root->val: root = root->right.
 *    - Else (split point or node found): return root.
 * 2. Return nullptr if loop ends.
 *
 * Dry Run:
 * Tree root = 6, p = 2, q = 8
 * - Root = 6:
 *   - p->val (2) < 6, but q->val (8) > 6.
 *   - Split point! Return 6.
 *
 * Tree root = 6, p = 2, q = 4
 * - Root = 6: Both 2 and 4 are < 6 -> root = root->left (2).
 * - Root = 2:
 *   - p->val (2) is equal to root->val. Split point! Return 2.
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root) {
            // If both nodes lie in the left subtree
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
            }
            // If both nodes lie in the right subtree
            else if (p->val > root->val && q->val > root->val) {
                root = root->right;
            }
            // Otherwise, we have found the split point (LCA node)
            else {
                return root;
            }
        }
        return nullptr;
    }
};
```

---

# 11. Balanced Binary Tree
**Idea:** Check height balance bottom-up using optimized single-pass DFS height computation.

```cpp
/*
 * Problem: Determine if a binary tree is height-balanced (left/right subtree height diff <= 1 for all nodes).
 *
 * Pattern: Optimized Postorder DFS Height check (Single-Pass O(N))
 *
 * Visual representation:
 *        1
 *       / \
 *      2   3
 *     / \
 *    4   5
 *   (Balanced: height diffs <= 1)
 *
 * Memorization Hook:
 * "Calculate height from bottom-up. If any subtree is unbalanced,
 * bubble up -1 immediately to cancel redundant calculations."
 *
 * 1-Minute Quick Revision:
 * 1. Write helper height(root) returning subtree height, or -1 if unbalanced.
 * 2. height() base: if null, return 0.
 * 3. Recurse left: if -1, return -1.
 * 4. Recurse right: if -1, return -1.
 * 5. Check balance: if abs(left_height - right_height) > 1, return -1.
 * 6. Return 1 + max(left_height, right_height).
 * 7. In main function, return isBalanced(root) if height(root) != -1.
 *
 * Dry Run:
 * Tree: 1 -> left=2, right=3. 2 -> left=4, right=5.
 * - height(4): returns 1.
 * - height(5): returns 1.
 * - height(2): left=1, right=1. diff = 0. returns 1 + max(1, 1) = 2.
 * - height(3): returns 1.
 * - height(1): left=2, right=1. diff = 1. returns 1 + max(2, 1) = 3.
 * Height not -1 -> Balanced (returns true).
 */
class Solution {
public:
    // Returns tree height if balanced, otherwise returns -1
    int height(TreeNode* root) {
        if (!root) return 0; // Empty tree height is 0

        int l = height(root->left); // Get left subtree height
        if (l == -1) return -1;     // Left subtree is unbalanced; propagate failure

        int r = height(root->right); // Get right subtree height
        if (r == -1) return -1;      // Right subtree is unbalanced; propagate failure

        // Check current node balance
        if (abs(l - r) > 1) return -1;

        return 1 + max(l, r); // Return actual height of subtree
    }

    bool isBalanced(TreeNode* root) {
        return height(root) != -1; // If height is -1, tree is unbalanced
    }
};
```

---

# 12. Linked List Cycle
**Idea:** Check if pointers meet using slow (1 step) and fast (2 steps) traversals.

```cpp
/*
 * Problem: Determine if a linked list contains a cycle.
 *
 * Pattern: Two-Pointer Fast & Slow (Floyd's Cycle Detection)
 *
 * Memorization Hook:
 * "Slow pointer moves 1 step, Fast pointer moves 2 steps.
 * If they meet, there is a cycle. If fast hits null, there is no cycle."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize slow = head, fast = head.
 * 2. Loop while fast is not null and fast->next is not null:
 *    - slow = slow->next
 *    - fast = fast->next->next
 *    - If slow == fast: return true (cycle detected).
 * 3. Return false.
 *
 * Dry Run:
 * List: 3 -> 2 -> 0 -> -4 (points back to 2)
 *
 * | Step | slow pointer node (value) | fast pointer node (value) | Equals? |
 * |------|---------------------------|---------------------------|---------|
 * | Start| 3                         | 3                         | (no check)|
 * | 1    | 2                         | 0                         | No      |
 * | 2    | 0                         | 2                         | No      |
 * | 3    | -4                        | -4                        | Yes! Return true |
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow = head, *fast = head; // Initialize slow and fast pointers

        while (fast && fast->next) {
            slow = slow->next;       // Moves 1 step
            fast = fast->next->next; // Moves 2 steps

            if (slow == fast) {
                return true; // Cycle detected when pointers meet
            }
        }
        return false; // Fast reached end -> no cycle
    }
};
```

---

# 13. Implement Queue using Stacks
**Idea:** Implement a queue with push to 'in' stack, and pop/peek from 'out' stack (transferring elements from 'in' to 'out' as needed).

```cpp
/*
 * Problem: Implement a first in first out (FIFO) queue using only two stacks.
 *
 * Pattern: Two-Stack Queue Design (Amortized O(1))
 *
 * Memorization Hook:
 * "Push goes to the 'in' stack. Pop/Peek from the 'out' stack.
 * If 'out' stack is empty, transfer all elements from 'in' stack to 'out' stack (reversing order)."
 *
 * 1-Minute Quick Revision:
 * 1. Maintain two stacks: std::stack 'in' and std::stack 'out'.
 * 2. push(x): push x onto 'in' stack.
 * 3. pop(): call peek() first to ensure 'out' has elements, store out.top(), pop from 'out', return stored value.
 * 4. peek(): if 'out' is empty, transfer all elements from 'in' to 'out'. Return out.top().
 * 5. empty(): return true if both 'in' and 'out' are empty.
 *
 * Dry Run:
 * push(1), push(2), peek(), pop(), empty()
 *
 * | Operation | Stack 'in' | Stack 'out' | Return Value | Notes |
 * |-----------|------------|-------------|--------------|-------|
 * | Push(1)   | [1]        | []          | -            | -     |
 * | Push(2)   | [1, 2]     | []          | -            | -     |
 * | Peek()    | []         | [2, 1]      | 1            | Transfer all in -> out |
 * | Pop()     | []         | [2]         | 1            | out.pop() is called |
 * | Empty()   | []         | [2] (false) | false        | Stacks not empty |
 */
class MyQueue {
    stack<int> in, out; // 'in' stack receives pushes; 'out' stack delivers pops/peeks

public:
    void push(int x) {
        in.push(x); // Push directly into input stack
    }

    int pop() {
        peek(); // Ensure the output stack has the current elements
        int x = out.top();
        out.pop();
        return x;
    }

    int peek() {
        // If output stack is empty, transfer all elements from input stack to output stack
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        return out.top();
    }

    bool empty() {
        return in.empty() && out.empty(); // Empty only if both stacks have no elements
    }
};
```

---

# Interview Revision

| Problem | Pattern |
|----------|----------|
| Two Sum | Hash Map |
| Valid Parentheses | Stack |
| Merge Lists | Linked List |
| Stock | Sliding Minimum |
| Palindrome | Two Pointer |
| Invert Tree | DFS |
| Anagram | Frequency Count |
| Binary Search | Binary Search |
| Flood Fill | DFS |
| LCA BST | BST Property |
| Balanced Tree | DFS Height |
| Linked List Cycle | Fast & Slow |
| Queue Using Stacks | Stack Design |

Good luck!
