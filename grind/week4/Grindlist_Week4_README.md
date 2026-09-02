# Grind 75 - Week 4 (C++)

# 1. Course Schedule

## Idea
The problem asks whether all courses can be completed given their prerequisites. This is equivalent to finding if there is a cycle in a directed graph. We represent the courses as nodes and prerequisites as directed edges. Since Kahn's algorithm (Topological Sort) can determine if a directed graph contains a cycle, we use it here. Courses with 0 indegree are queued first, then processed in BFS fashion. If the number of processed nodes equals `numCourses`, no cycle exists, meaning courses can be completed.

```cpp
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
-
/*
 * Problem: Course Schedule (LeetCode 207)
 * Determine if you can finish all courses given the prerequisites.
 *
 * Pattern: Topological Sort (Kahn's Algorithm) / Directed Acyclic Graph (DAG) cycle detection
 *
 * Complexity:
 * - Time Complexity: O(V + E) where V is the number of courses (numCourses) and E is the number of prerequisites.
 *   Building the graph takes O(E). In Kahn's algorithm, each node and edge is processed at most once: O(V + E).
 * - Space Complexity: O(V + E) for the adjacency list representation of the graph, the indegree array O(V),
 *   and the queue O(V) for BFS traversal.
 *
 * Visualizations:
 * 1. Acyclic Graph (Valid case: no cycle)
 *    0 (indegree=0) ---> 1 (indegree=1) ---> 2 (indegree=1) ---> 3 (indegree=1)
 *
 * 2. Cyclic Graph (Invalid case: has cycle)
 *    0 (indegree=0) ---> 1 (indegree=2) ---> 2 (indegree=1)
 *                           ^                 |
 *                           |                 v
 *                           +---------------- 3 (indegree=1)
 *
 * Memorization Hook:
 * "Find indegrees. Queue up 0-indegree courses. Pop course, increment processed count, decrement indegrees 
 * of neighbors. If any neighbor hits 0 indegree, queue it. Success if processed count equals total courses."
 *
 * 1-Minute Quick Revision:
 * 1. Build an adjacency list `adj` mapping dependencies: prerequisites[i][1] (pre) -> prerequisites[i][0] (course).
 * 2. Maintain an `indegree` array where `indegree[course]` represents the number of prereqs it depends on.
 * 3. Add all courses with `indegree == 0` to a queue `q`.
 * 4. While `q` is not empty:
 *    - Pop the front course `u`, and increment the `count` of completed courses.
 *    - For each neighbor `v` of `u`, decrement its `indegree`. If it becomes 0, push `v` to `q`.
 * 5. Return `count == numCourses`.
 *
 * Dry Run:
 * numCourses = 4, prerequisites = [[1, 0], [2, 1], [3, 2]] (meaning 0 -> 1 -> 2 -> 3)
 * adj = {0: [1], 1: [2], 2: [3]}, indegree = [0, 1, 1, 1]
 *
 * | Step / Iteration | Popped Node u | Neighbors v | indegree[v] after decr | Queue State (Front -> Back) | count | Condition / Action                  |
 * |------------------|---------------|-------------|------------------------|-----------------------------|-------|-------------------------------------|
 * | Initialization   | -             | -           | -                      | [0]                         | 0     | Push node 0 (indegree is 0)         |
 * | Iteration 1      | 0             | 1           | indegree[1] = 0        | [1]                         | 1     | Pop 0; decr indegree[1] -> push 1   |
 * | Iteration 2      | 1             | 2           | indegree[2] = 0        | [2]                         | 2     | Pop 1; decr indegree[2] -> push 2   |
 * | Iteration 3      | 2             | 3           | indegree[3] = 0        | [3]                         | 3     | Pop 2; decr indegree[3] -> push 3   |
 * | Iteration 4      | 3             | -           | -                      | []                          | 4     | Pop 3; no neighbors                 |
 * | End              | -             | -           | -                      | []                          | 4     | count == numCourses (4 == 4) -> true|
 */
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Track the number of dependencies (incoming edges) for each course
        vector<int> indegree(numCourses, 0);
        // Adjacency list representation of the directed dependency graph
        vector<vector<int>> adj(numCourses);
        
        // Build the dependency graph: p[1] -> p[0] means p[1] must be completed before starting p[0]
        for (auto &p : prerequisites) {
            adj[p[1]].push_back(p[0]); 
            indegree[p[0]]++;          // Increment indegree for the dependent course
        }
        
        // Queue to store courses with no prerequisites (indegree == 0)
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int count = 0; // Tracks the number of courses that can be completed
        
        // Process courses in topological order
        while (!q.empty()) {
            int u = q.front(); 
            q.pop();
            count++;
            
            // For all courses that depend on the completed course 'u'
            for (auto v : adj[u]) {
                // Decrement neighbor's indegree. If all prerequisites are cleared (indegree becomes 0)
                if (--indegree[v] == 0) {
                    q.push(v); // Queue it for completion
                }
            }
        }
        
        // If we completed all courses, no cycle was detected
        return count == numCourses;
    }
};
```

---

# 2. Implement Trie (Prefix Tree)

## Idea
A Trie (Prefix Tree) is an efficient information retrieval data structure that stores strings as paths of characters in a tree. Each node contains pointers to its child nodes (up to 26 for lowercase English letters) and a boolean flag `eow` that marks the end of a complete word. Searches are extremely fast and depend on the length of the string rather than the size of the dataset.

```cpp
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
 * Problem: Implement Trie (Prefix Tree) (LeetCode 208)
 * Implement a trie with insert, search, and startsWith methods.
 *
 * Pattern: Trie / Prefix Tree / Tree Traversal
 *
 * Complexity:
 * - Time Complexity:
 *   - insert(word): O(L) where L is the length of the word. We traverse or create L nodes.
 *   - search(word): O(L) where L is the length of the word. We traverse at most L nodes.
 *   - startsWith(prefix): O(L) where L is the length of the prefix. We traverse at most L nodes.
 * - Space Complexity:
 *   - Worst case: O(N * L * 26) where N is the number of inserted words, L is the maximum length of a word.
 *   - Auxiliary space: O(1) for search and startsWith operations.
 *
 * Visualizations:
 * Trie containing "cat" and "car":
 *
 *          [root]
 *             | 'c'
 *           [node]
 *             | 'a'
 *           [node]
 *          /      \
 *     't' /        \ 'r'
 *      [node]     [node]
 *    (eow=true)  (eow=true)
 *
 * Memorization Hook:
 * "Trie node holds an array of 26 child pointers and a boolean 'eow' (End of Word).
 * Insertion allocates nodes along character path; search expects path existence + eow; 
 * startsWith just expects path existence."
 *
 * 1-Minute Quick Revision:
 * 1. Define children array `Trie* children[26]` (initialized to nullptr) and bool `eow` (initialized to false).
 * 2. `insert(word)`: Loop each character `c` of word. If `node->children[c-'a']` is nullptr, create a new Trie node. Move `node = node->children[c-'a']`. Set `node->eow = true` at the end.
 * 3. `search(word)`: Loop each character. If `node->children[c-'a']` is nullptr, return false. Otherwise move. Return `node->eow`.
 * 4. `startsWith(prefix)`: Loop each character. If `node->children[c-'a']` is nullptr, return false. Otherwise move. Return true.
 *
 * Dry Run:
 * Operations: insert("cat"), search("cat"), search("ca"), startsWith("ca")
 *
 * | Operation        | Argument | Characters Checked | Trie Path & Nodes Found / Created | Final Result / End of Word State |
 * |------------------|----------|--------------------|-----------------------------------|----------------------------------|
 * | insert("cat")    | "cat"    | 'c', 'a', 't'      | Creates new nodes for 'c', 'a', 't'| Marks node 't' -> eow = true     |
 * | search("cat")    | "cat"    | 'c', 'a', 't'      | Traverses node 'c' -> 'a' -> 't'  | Returns t->eow (true)            |
 * | search("ca")     | "ca"     | 'c', 'a'           | Traverses node 'c' -> 'a'         | Returns a->eow (false)           |
 * | startsWith("ca") | "ca"     | 'c', 'a'           | Traverses node 'c' -> 'a'         | Returns true (path exists)       |
 */
class Trie {
private:
    Trie* children[26];
    bool eow; // End of word marker

public:
    // Initialize the Trie node
    Trie() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        eow = false;   
    }
    
    // Inserts a word into the trie
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            int index = c - 'a';
            // Create a new trie node if it doesn't exist for the current character
            if (node->children[index] == nullptr) {
                node->children[index] = new Trie();
            }
            node = node->children[index]; // Move to the child node
        }
        node->eow = true; // Mark the end of the word
    }
    
    // Returns if the word is in the trie
    bool search(string word) {
        Trie* node = this;
        for (char c : word) {
            int index = c - 'a';
            // Character path doesn't exist
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index]; // Move to the child node
        }
        return node->eow; // Return if it's the exact end of a word
    }
    
    // Returns if there is any word in the trie that starts with the given prefix
    bool startsWith(string prefix) {
        Trie* node = this;
        for (char c : prefix) {
            int index = c - 'a';
            // Prefix character path doesn't exist
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index]; // Move to the child node
        }
        return true; // We successfully traversed the prefix path
    }
};
```

---

# 3. Coin Change

## Idea
This problem finds the minimum number of coins needed to make up a specific amount. We utilize bottom-up Dynamic Programming. By initializing a DP array of size `amount + 1` with a placeholder for infinity (`amount + 1`), we can compute the minimum coins needed for all sub-amounts from `1` to `amount`. For any amount `i` and coin denomination `coin`, the transition is `dp[i] = min(dp[i], dp[i - coin] + 1)`.

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
 * Problem: Coin Change (LeetCode 322)
 * Find the fewest number of coins that you need to make up a given amount.
 *
 * Pattern: Dynamic Programming / 1D DP / Bottom-Up
 *
 * Complexity:
 * - Time Complexity: O(amount * N) where N is the number of coin denominations (coins.size()).
 *   For each amount from 1 to amount, we iterate through all coins.
 * - Space Complexity: O(amount) to store the DP array of size amount + 1.
 *
 * Visualizations:
 * DP Array representing the minimum coins needed for each sub-amount up to amount 5:
 * coins = [1, 2, 5], amount = 5
 *
 * Index (Amount):   0   1   2   3   4   5
 * dp[Index]:       [0,  1,  1,  2,  2,  1]
 *                   |   |   |   |   |   |
 *                   |   |   |   |   |   +--> min(dp[4]+1, dp[3]+1, dp[0]+1) = 1 (uses 5)
 *                   |   |   |   |   +------> min(dp[3]+1, dp[2]+1) = 2 (uses 2+2)
 *                   |   |   |   +----------> min(dp[2]+1, dp[1]+1) = 2 (uses 2+1)
 *                   |   |   +--------------> min(dp[1]+1, dp[0]+1) = 1 (uses 2)
 *                   |   +------------------> min(dp[0]+1) = 1 (uses 1)
 *                   +----------------------> Base Case (0 coins for amount 0)
 *
 * Memorization Hook:
 * "Initialize DP array of size amount+1 with amount+1 (representing infinity). Base case dp[0] = 0.
 * For each amount from 1 to target, try every coin denomination. If the coin is smaller than or equal 
 * to the amount, update dp[amount] = min(dp[amount], dp[amount - coin] + 1)."
 *
 * 1-Minute Quick Revision:
 * 1. Create a `dp` array of size `amount + 1` initialized to `amount + 1`.
 * 2. Set the base case: `dp[0] = 0`.
 * 3. Loop amount `i` from 1 to `amount`.
 * 4. Nested loop over each `coin` in `coins`.
 * 5. If `i - coin >= 0`, set `dp[i] = min(dp[i], dp[i - coin] + 1)`.
 * 6. Return `dp[amount]` if it was reachable (less than `amount + 1`), else return `-1`.
 *
 * Dry Run:
 * coins = [1, 2, 5], amount = 5
 * dp array initially = [0, 6, 6, 6, 6, 6] (6 is amount+1, representing infinity)
 *
 * | Amount i | Coin Option | condition: i - coin >= 0 | dp[i - coin] | Transition: min(dp[i], dp[i - coin] + 1) | dp array after processing amount i |
 * |----------|-------------|--------------------------|--------------|------------------------------------------|-----------------------------------|
 * | 1        | 1           | 1 - 1 = 0 >= 0 (true)    | dp[0] = 0    | min(6, 0 + 1) = 1                        | [0, 1, 6, 6, 6, 6]                |
 * | 1        | 2           | 1 - 2 = -1 >= 0 (false)  | -            | -                                        | [0, 1, 6, 6, 6, 6]                |
 * | 1        | 5           | 1 - 5 = -4 >= 0 (false)  | -            | -                                        | [0, 1, 6, 6, 6, 6]                |
 * | 2        | 1           | 2 - 1 = 1 >= 0 (true)    | dp[1] = 1    | min(6, 1 + 1) = 2                        | [0, 1, 2, 6, 6, 6]                |
 * | 2        | 2           | 2 - 2 = 0 >= 0 (true)    | dp[0] = 0    | min(2, 0 + 1) = 1                        | [0, 1, 1, 6, 6, 6]                |
 * | 2        | 5           | 2 - 5 = -3 >= 0 (false)  | -            | -                                        | [0, 1, 1, 6, 6, 6]                |
 * | 3        | 1           | 3 - 1 = 2 >= 0 (true)    | dp[2] = 1    | min(6, 1 + 1) = 2                        | [0, 1, 1, 2, 6, 6]                |
 * | 3        | 2           | 3 - 2 = 1 >= 0 (true)    | dp[1] = 1    | min(2, 1 + 1) = 2                        | [0, 1, 1, 2, 6, 6]                |
 * | 3        | 5           | 3 - 5 = -2 >= 0 (false)  | -            | -                                        | [0, 1, 1, 2, 6, 6]                |
 * | 4        | 1           | 4 - 1 = 3 >= 0 (true)    | dp[3] = 2    | min(6, 2 + 1) = 3                        | [0, 1, 1, 2, 3, 6]                |
 * | 4        | 2           | 4 - 2 = 2 >= 0 (true)    | dp[2] = 1    | min(3, 1 + 1) = 2                        | [0, 1, 1, 2, 2, 6]                |
 * | 4        | 5           | 4 - 5 = -1 >= 0 (false)  | -            | -                                        | [0, 1, 1, 2, 2, 6]                |
 * | 5        | 1           | 5 - 1 = 4 >= 0 (true)    | dp[4] = 2    | min(6, 2 + 1) = 3                        | [0, 1, 1, 2, 2, 3]                |
 * | 5        | 2           | 5 - 2 = 3 >= 0 (true)    | dp[3] = 2    | min(3, 2 + 1) = 3                        | [0, 1, 1, 2, 2, 3]                |
 * | 5        | 5           | 5 - 5 = 0 >= 0 (true)    | dp[0] = 0    | min(3, 0 + 1) = 1                        | [0, 1, 1, 2, 2, 1]                |
 */
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // dp[i] will store the minimum number of coins needed to make amount i
        // Initialize with amount + 1 (representing positive infinity)
        vector<int> dp(amount + 1, amount + 1);
        
        // Base Case: 0 coins needed to make amount 0
        dp[0] = 0;
        
        // Outer loop: iterate through all amounts from 1 to target amount
        for (int i = 1; i <= amount; i++) {
            // Inner loop: try all coin options
            for (int coin : coins) {
                // If the current amount can fit this coin
                if (i - coin >= 0) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        // If target amount is still placeholder amount + 1, it's unreachable
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }
};
```

---

# 4. Product of Array Except Self

## Idea
The problem asks for an output array where each element `ans[i]` is the product of all elements in `nums` except `nums[i]`, in $O(N)$ time and without division. We can accomplish this by making two sweeps. In the forward sweep, we calculate and store the prefix product (the product of all elements to the left of the current index). In the backward sweep, we multiply this value by the suffix product (the product of all elements to the right of the current index), which we accumulate dynamically in a single variable.

```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/*
 * Problem: Product of Array Except Self (LeetCode 238)
 * Return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
 * Must run in O(n) time and without using the division operation.
 *
 * Pattern: Prefix & Suffix Products / Accumulators
 *
 * Complexity:
 * - Time Complexity: O(N) where N is the number of elements in nums. We make exactly two sequential linear passes.
 * - Space Complexity: O(1) auxiliary space (excluding the output container).
 *
 * Visualizations:
 * Input array: [1,  2,  3,  4]
 *
 * Left products (Prefix):
 *   ans[0] = 1
 *   ans[1] = 1 * nums[0] = 1
 *   ans[2] = 1 * nums[0] * nums[1] = 2
 *   ans[3] = 1 * nums[0] * nums[1] * nums[2] = 6
 *   Prefix vector: [1, 1, 2, 6]
 *
 * Right products (Suffix, accumulated via single right_prod variable):
 *   ans[3] *= 1              => 6
 *   ans[2] *= 4              => 8
 *   ans[1] *= 4 * 3 = 12     => 12
 *   ans[0] *= 4 * 3 * 2 = 24 => 24
 *   Final Result: [24, 12, 8, 6]
 *
 * Memorization Hook:
 * "Store prefix products in the output array in a forward pass. 
 * Then, maintain a running suffix product in a backward pass, multiplying it into the output array."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize result vector `ans` of size `n` with 1.
 * 2. Set prefix accumulator `left_prod = 1`.
 * 3. Traverse left-to-right: `ans[i] = left_prod`, then update `left_prod *= nums[i]`.
 * 4. Set suffix accumulator `right_prod = 1`.
 * 5. Traverse right-to-left: `ans[i] *= right_prod`, then update `right_prod *= nums[i]`.
 * 6. Return `ans`.
 *
 * Dry Run:
 * nums = [1, 2, 3, 4]
 * Output array `ans` initialized to [1, 1, 1, 1]
 *
 * Left-to-right pass:
 * | i | nums[i] | ans[i] assignment (left_prod) | left_prod update (left_prod * nums[i]) | ans state after step |
 * |---|---------|-------------------------------|----------------------------------------|----------------------|
 * | 0 | 1       | ans[0] = 1                    | left_prod = 1 * 1 = 1                  | [1, 1, 1, 1]         |
 * | 1 | 2       | ans[1] = 1                    | left_prod = 1 * 2 = 2                  | [1, 1, 1, 1]         |
 * | 2 | 3       | ans[2] = 2                    | left_prod = 2 * 3 = 6                  | [1, 1, 2, 1]         |
 * | 3 | 4       | ans[3] = 6                    | left_prod = 6 * 4 = 24                 | [1, 1, 2, 6]         |
 *
 * Right-to-left pass (starting right_prod = 1):
 * | i | nums[i] | ans[i] update (ans[i] * right_prod) | right_prod update (right_prod * nums[i]) | ans state after step |
 * |---|---------|-------------------------------------|------------------------------------------|----------------------|
 * | 3 | 4       | ans[3] = 6 * 1 = 6                  | right_prod = 1 * 4 = 4                   | [1, 1, 2, 6]         |
 * | 2 | 3       | ans[2] = 2 * 4 = 8                  | right_prod = 4 * 3 = 12                  | [1, 1, 8, 6]         |
 * | 1 | 2       | ans[1] = 1 * 12 = 12                | right_prod = 12 * 2 = 24                 | [1, 12, 8, 6]        |
 * | 0 | 1       | ans[0] = 1 * 24 = 24                | right_prod = 24 * 1 = 24                 | [24, 12, 8, 6]       |
 */
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        
        // Pass 1: Store prefix products in output array
        int left = 1;
        for (int i = 0; i < n; i++) {
            result[i] = left;
            left *= nums[i]; // Accumulate left product
        }
        
        // Pass 2: Multiply with suffix products from right to left
        int right = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= right; // Multiply by right product
            right *= nums[i]; // Accumulate right product
        }

        return result;
    }
};
```

---

# 5. Min Stack

## Idea
We need to design a stack that retrieves the minimum element in $O(1)$ constant time. We can achieve this by pairing each value pushed onto the stack with the minimum value observed in the stack at that level. We use a single vector of pairs `vector<pair<int, int>> st` where the first element is the actual value and the second is the minimum value up to that level.

```cpp
#include<iostream>
#include<vector>
using namespace std;

/*
 * Problem: Min Stack (LeetCode 155)
 * Design a stack that supports push, pop, top, and retrieving the minimum element in constant time O(1).
 *
 * Pattern: Stack Design / Pair Tracking
 *
 * Complexity:
 * - Time Complexity: O(1) for all operations (push, pop, top, getMin).
 *   We avoid any linear scan by tracking the minimum value at each state.
 * - Space Complexity: O(N) where N is the number of elements in the stack.
 *   Each element in the stack is stored as a pair of integers.
 *
 * Visualizations:
 * Stack state progression during push operations:
 *
 * 1. Push 5:
 *    [ {val: 5, min: 5} ] <-- Top (min_so_far is 5)
 *
 * 2. Push 3:
 *    [ {val: 5, min: 5}, {val: 3, min: 3} ] <-- Top (min_so_far is min(3, 5) = 3)
 *
 * 3. Push 7:
 *    [ {val: 5, min: 5}, {val: 3, min: 3}, {val: 7, min: 3} ] <-- Top (min_so_far is min(7, 3) = 3)
 *
 * Memorization Hook:
 * "Store each stack node as a pair: {value, min_so_far}. 
 * The current minimum is always cached at the top of the stack, eliminating searching."
 *
 * 1-Minute Quick Revision:
 * 1. Maintain a single `vector<pair<int, int>> st` where each element is `{val, min_so_far}`.
 * 2. `push(val)`: If stack is empty, push `{val, val}`. Otherwise, push `{val, min(val, st.back().second)}`.
 * 3. `pop()`: Remove the top element using `st.pop_back()`.
 * 4. `top()`: Return the value component of the top element: `st.back().first`.
 * 5. `getMin()`: Return the minimum component of the top element: `st.back().second`.
 *
 * Dry Run:
 * Operations: push(5), push(3), getMin(), push(7), getMin(), pop(), getMin()
 *
 * | Step / Operation | Argument | Stack State (Bottom -> Top)        | top() result | getMin() result | Action / Explanation                               |
 * |------------------|----------|------------------------------------|--------------|-----------------|----------------------------------------------------|
 * | push(5)          | 5        | [{5, 5}]                           | -            | -               | Stack empty, new min is 5                          |
 * | push(3)          | 3        | [{5, 5}, {3, 3}]                   | -            | -               | 3 < 5, new min is 3                                |
 * | getMin()         | -        | [{5, 5}, {3, 3}]                   | -            | 3               | Returns top pair's min (3)                         |
 * | push(7)          | 7        | [{5, 5}, {3, 3}, {7, 3}]           | -            | -               | 7 > 3, new min remains 3                           |
 * | getMin()         | -        | [{5, 5}, {3, 3}, {7, 3}]           | -            | 3               | Returns top pair's min (3)                         |
 * | pop()            | -        | [{5, 5}, {3, 3}]                   | -            | -               | Removes {7, 3}                                     |
 * | getMin()         | -        | [{5, 5}, {3, 3}]                   | -            | 3               | Returns top pair's min (3)                         |
 */
class MinStack {
private:
    // Pair stores {value, min_so_far_at_this_level}
    vector<pair<int, int>> st;

public:
    MinStack() {
        // Constructor
    }
    
    void push(int val) {
        if (st.empty()) {
            st.push_back({val, val});
        } else {
            // New min is the minimum of the new value and the current min of the stack
            // st.back() = {topmost element, current minimum}
            // st.back().first = topmost element
            // st.back().second = current minimum
            int currentMin = min(val, st.back().second);
            st.push_back({val, currentMin});
        }
    }
    
    void pop() {
        st.pop_back();
    }
    
    int top() {
        return st.back().first;
    }
    
    int getMin() {
        return st.back().second;
    }
};
```

---

# 6. Validate Binary Search Tree

## Idea
A Binary Search Tree (BST) must satisfy the property that for every node, all values in its left subtree are strictly less than the node's value, and all values in its right subtree are strictly greater. We validate this property recursively by passing the valid minimum and maximum boundaries downward. We use `long long` bounds `LLONG_MIN` and `LLONG_MAX` to avoid integer overflow issues when node values contain `INT_MIN` or `INT_MAX`.

```cpp
#include<iostream>
#include<vector>
using namespace std;

#ifndef TREE_NODE_DECLARED
#define TREE_NODE_DECLARED
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#endif

/*
 * Problem: Validate Binary Search Tree (LeetCode 98)
 * Given the root of a binary tree, determine if it is a valid binary search tree (BST).
 *
 * Pattern: Binary Tree / DFS Recursion / BST Properties
 *
 * Complexity:
 * - Time Complexity: O(N) where N is the number of nodes in the binary tree. We visit each node exactly once.
 * - Space Complexity: O(H) recursion stack space where H is the height of the tree. In the worst case (skewed tree), H = N.
 *
 * Visualizations:
 * Valid range constraints for BST nodes:
 *
 *                     10  [Range: -∞ to +∞]
 *                    /  \
 *                   /    \
 *                  5      15  [Range: 10 to +∞]
 *          [Range: -∞ to 10]
 *                /   \
 *               3     7
 *      [Range: -∞ to 5] [Range: 5 to 10]
 *
 * Memorization Hook:
 * "isValid(node, min_val, max_val). Empty tree is valid. 
 * Node's value must be strictly between min_val and max_val. 
 * Recurse left with max updated to current; recurse right with min updated to current."
 *
 * 1-Minute Quick Revision:
 * 1. Implement a helper function `isValid(node, min_val, max_val)` using `long long` (LLONG_MIN/LLONG_MAX) to prevent overflow.
 * 2. Base case: If `node` is nullptr, return `true`.
 * 3. Range check: If `node->val <= min_val` or `node->val >= max_val`, return `false`.
 * 4. Recursive case: Check left subtree with updated max constraint `isValid(node->left, min_val, node->val)`.
 * 5. Check right subtree with updated min constraint `isValid(node->right, node->val, max_val)`.
 * 6. Return `left_subtree_is_valid && right_subtree_is_valid`.
 *
 * Dry Run:
 * Tree: 10 / \ 5 15 / \ 3 7 (where 10 is root, 5 and 15 are left and right child, 3 and 7 are children of 5)
 *
 * | Step / DFS Call        | Node | Current Range [min, max]          | Condition: node->val <= min or >= max | Left DFS Recursive Call             | Right DFS Recursive Call            | Result |
 * |------------------------|------|-----------------------------------|---------------------------------------|-------------------------------------|-------------------------------------|--------|
 * | isValid(root, -∞, +∞)  | 10   | [LLONG_MIN, LLONG_MAX]            | 10 <= -∞ or >= +∞ (false)             | isValid(5, LLONG_MIN, 10)           | isValid(15, 10, LLONG_MAX)          | true   |
 * | isValid(left, -∞, 10)  | 5    | [LLONG_MIN, 10]                   | 5 <= -∞ or >= 10 (false)              | isValid(3, LLONG_MIN, 5)            | isValid(7, 5, 10)                   | true   |
 * | isValid(left, -∞, 5)   | 3    | [LLONG_MIN, 5]                    | 3 <= -∞ or >= 5 (false)               | isValid(nullptr, LLONG_MIN, 3)->true| isValid(nullptr, 3, 5)->true        | true   |
 * | isValid(right, 5, 10)  | 7    | [5, 10]                           | 7 <= 5 or >= 10 (false)               | isValid(nullptr, 5, 7)->true        | isValid(nullptr, 7, 10)->true       | true   |
 * | isValid(right, 10, +∞) | 15   | [10, LLONG_MAX]                   | 15 <= 10 or >= +∞ (false)             | isValid(nullptr, 10, 15)->true      | isValid(nullptr, 15, LLONG_MAX)->true| true   |
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValid(root, LLONG_MIN, LLONG_MAX);
    }

private:
    bool isValid(TreeNode* root, long long minVal, long long maxVal) {
        // Base case: An empty tree or node is a valid BST
        if (root == nullptr) {
            return true;
        }
        
        // The current node's value must sit strictly within the allowed range [minVal, maxVal]
        if (root->val <= minVal || root->val >= maxVal) {
            return false;
        }
        
        // Recurse left (updating maxVal) and right (updating minVal)
        return isValid(root->left, minVal, root->val) 
            && isValid(root->right, root->val, maxVal);
    }
};
```

---

# 7. Number of Islands

## Idea
We need to count the number of distinct islands in an $M \times N$ binary grid where `'1'` is land and `'0'` is water. We iterate through each cell. When we encounter land (`'1'`), it signifies the start of a new island. We increment our island count, then trigger a DFS traversal starting at that cell to "sink" (change `'1'` to `'0'`) all connected land cells. This prevents us from counting the same island multiple times.

```cpp
#include<iostream>
#include<vector>
using namespace std;

/*
 * Problem: Number of Islands (LeetCode 200)
 * Given an m x n 2D binary grid which represents a map of '1's (land) and '0's (water), return the number of islands.
 *
 * Pattern: Graph DFS / Grid Connected Components
 *
 * Complexity:
 * - Time Complexity: O(M * N) where M is the number of rows and N is the number of columns.
 *   Each cell is visited at most constant times during the grid traversal and subsequent DFS calls.
 * - Space Complexity: O(M * N) in the worst case (where the grid is filled with land) for the recursive call stack.
 *
 * Visualizations:
 * Grid flood-fill via DFS recursion (sinking land):
 *
 * Initial Grid:       BFS/DFS Discovery:     After DFS Sinks Island:
 *   [1, 1, 0]           [(1), (1), 0]          [0, 0, 0]
 *   [1, 0, 0]    --->   [(1),  0 , 0]   --->   [0, 0, 0]
 *   [0, 0, 1]           [ 0 ,  0 , 1]          [0, 0, 1] (island count incremented)
 *
 * Memorization Hook:
 * "Traverse the grid. When you hit land '1', increment the island count and start a DFS 
 * to sink all connected land cells by turning them into '0'. Repeat."
 *
 * 1-Minute Quick Revision:
 * 1. Loop through all cells in the grid.
 * 2. If `grid[i][j] == '1'`:
 *    - Increment `count`.
 *    - Trigger `dfs(grid, i, j, m, n)` to flood-fill and sink the island.
 * 3. Inside `dfs(i, j)`:
 *    - If `i` or `j` are out of bounds or `grid[i][j] == '0'`, return.
 *    - Sink current cell: `grid[i][j] = '0'`.
 *    - Recurse in all four cardinal directions (Up, Down, Left, Right).
 * 4. Return `count`.
 *
 * Dry Run:
 * grid = [
 *   ["1", "1", "0"],
 *   ["1", "0", "0"],
 *   ["0", "0", "1"]
 * ]
 *
 * | Row i | Col j | grid[i][j] | Action Taken / DFS Spawned                | Cells Sunk ('1' -> '0') in DFS Run | Island Count Updated |
 * |-------|-------|------------|-------------------------------------------|-------------------------------------|----------------------|
 * | 0     | 0     | '1'        | Increment count, spawn DFS from (0, 0)     | (0,0) -> (1,0) -> (0,1)             | count = 1           |
 * | 0     | 1     | '0' (sunk) | Skip                                      | -                                   | 1                    |
 * | 0     | 2     | '0'        | Skip                                      | -                                   | 1                    |
 * | 1     | 0     | '0' (sunk) | Skip                                      | -                                   | 1                    |
 * | 1     | 1     | '0'        | Skip                                      | -                                   | 1                    |
 * | 1     | 2     | '0'        | Skip                                      | -                                   | 1                    |
 * | 2     | 0     | '0'        | Skip                                      | -                                   | 1                    |
 * | 2     | 1     | '0'        | Skip                                      | -                                   | 1                    |
 * | 2     | 2     | '1'        | Increment count, spawn DFS from (2, 2)     | (2,2)                               | count = 2           |
 */
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j, m, n);
                }
            }
        }

        return count;
    }

private:
    void dfs(vector<vector<char>>& grid, int i, int j, int m, int n) {
        // Base case check for boundary limits and water cell
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == '0') {
            return;
        }
        
        // Mark the land cell as water (sink it)
        grid[i][j] = '0';
        
        // Traverse in all 4 direction paths
        dfs(grid, i + 1, j, m, n);
        dfs(grid, i - 1, j, m, n);
        dfs(grid, i, j + 1, m, n);
        dfs(grid, i, j - 1, m, n);
    }
};
```

---

# 8. Rotting Oranges

## Idea
We need to find the minimum time needed for all fresh oranges to rot. Since rotting spreads level-by-level (minute-by-minute) to neighboring cells, we use BFS. To simplify the implementation and avoid nested level-by-level loops (`while(sz--)`), we store the coordinates and the time at which each orange rots directly inside the queue as a struct `Orange { int r, c, t; }`. We initialize the queue with all initially rotten oranges and track the remaining fresh ones.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
 * Problem: Rotting Oranges (LeetCode 994)
 * Determine the minimum number of minutes that must elapse until no cell has a fresh orange.
 * If this is impossible, return -1.
 *
 * Pattern: Multi-source BFS / Grid / Queue
 *
 * Complexity:
 * - Time Complexity: O(M * N) where M is the number of rows and N is columns in the grid.
 *   We scan the grid to initialize the queue and visit each cell at most once.
 * - Space Complexity: O(M * N) for the BFS queue containing rotten orange nodes.
 *
 * BFS Simplification:
 * - We avoid nested level-by-level loops (such as while(size--)) by storing the current time
 *   directly alongside the orange coordinates in the queue using a simple struct.
 * - This provides a clean, single-loop traversal.
 *
 * Visualizations:
 * Orange grid states over time:
 * (2 = rotten, 1 = fresh, 0 = empty)
 *
 * Minute 0:            Minute 1:            Minute 2:
 *   [2, 1, 0]            [2, 2, 0]            [2, 2, 0]
 *   [1, 1, 0]    --->    [2, 1, 0]    --->    [2, 2, 0]
 *   [0, 1, 1]            [0, 1, 1]            [0, 2, 2]
 *
 * Memorization Hook:
 * "Push all rotten oranges onto a queue with time = 0 and count fresh oranges.
 * Pop each rotten orange, update max_time, rot its fresh neighbors, decrement fresh count,
 * and push them with time + 1. If fresh count is 0, return max_time, else -1."
 *
 * 1-Minute Quick Revision:
 * 1. Define a struct `Orange { int r, c, t; }` to hold coordinates and current time.
 * 2. Count all fresh oranges and push all initial rotten oranges into a `queue<Orange> q` with time 0.
 * 3. Loop while `q` is not empty:
 *    - Pop the front orange `curr`.
 *    - Update `max_time = max(max_time, curr.t)`.
 *    - Visit 4 neighbors: if bounds match and cell is 1 (fresh), set grid to 2 (rotten), decrement `fresh`, and push `{ni, nj, curr.t + 1}`.
 * 4. After BFS, return `fresh == 0 ? max_time : -1`.
 *
 * Dry Run:
 * grid = [
 *   [2, 1, 1],
 *   [1, 1, 0],
 *   [0, 1, 1]
 * ]
 * Initial state: fresh = 6, rotten oranges pushed to queue: [{0, 0, 0}]
 *
 * | Pop Orange | Neighbors (r, c) | Fresh -> Rotten | fresh count update | Queue Pushes                 | max_time update |
 * |------------|------------------|-----------------|--------------------|------------------------------|-----------------|
 * | {0, 0, 0}  | (1,0), (0,1)     | Yes             | 6 - 2 = 4          | {1,0,1}, {0,1,1}             | max(0, 0) = 0   |
 * | {1, 0, 1}  | (1,1)            | Yes             | 4 - 1 = 3          | {1,1,2}                      | max(0, 1) = 1   |
 * | {0, 1, 1}  | (0,2)            | Yes             | 3 - 1 = 2          | {0,2,2}                      | max(1, 1) = 1   |
 * | {1, 1, 2}  | -                | -               | 2                  | -                            | max(1, 2) = 2   |
 * | {0, 2, 2}  | (1,2) [water]    | -               | 2                  | -                            | max(2, 2) = 2   |
 * | -          | -                | -               | -                  | Queue empty, fresh = 2 (> 0) | Returns -1      |
 */
class Solution {
private:
    struct Orange {
        int r;
        int c;
        int t; // Minutes elapsed when this orange rotted
    };

public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<Orange> q;
        int fresh = 0;
        
        // Scan the grid to count fresh oranges and queue initial rotten oranges
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fresh++;
                } else if (grid[i][j] == 2) {
                    q.push({i, j, 0});
                }
            }
        }
        
        // 4 directions of movement (Down, Up, Right, Left)
        vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int max_time = 0;
        
        // Single flat loop structure without nested level loops
        while (!q.empty()) {
            Orange curr = q.front();
            q.pop();
            
            // Record maximum time taken
            max_time = max(max_time, curr.t);
            
            for (auto d : dir) {
                int ni = curr.r + d.first;
                int nj = curr.c + d.second;
                
                // If the neighbor is within boundaries and contains a fresh orange
                if (ni >= 0 && nj >= 0 && ni < m && nj < n && grid[ni][nj] == 1) {
                    grid[ni][nj] = 2; // Rot the fresh orange
                    fresh--;
                    q.push({ni, nj, curr.t + 1}); // Queue it with incremented time
                }
            }
        }
        
        // If there are still fresh oranges left, it's impossible to rot all of them
        return fresh == 0 ? max_time : -1;
    }
};
```
