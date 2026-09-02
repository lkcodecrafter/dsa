# Grind 75 - Week 3 (C++)

# 1. Insert Interval

## Idea
The problem requires inserting a `newInterval` into a sorted list of non-overlapping intervals and merging them if there is any overlap. We can process this in a single pass of three stages:
1. Add all intervals that end before `newInterval` starts (no overlap).
2. Merge all overlapping intervals with `newInterval` by updating the start to the minimum start and the end to the maximum end.
3. Add all remaining intervals that start after `newInterval` ends.

```cpp
/*
 * Problem: Given a set of non-overlapping intervals sorted by start time, insert a new interval into the intervals (merge if necessary).
 * 
 * Pattern: Linear Scan / Merge Intervals
 * 
 * Complexity:
 * - Time Complexity: O(N) where N is the number of intervals, as we perform a single linear scan.
 * - Space Complexity: O(1) auxiliary space (excluding the output container).
 *
 * Memorization Hook:
 * "Left: while current end < new start, keep.
 * Merge: while current start <= new end, update new start/end to min/max.
 * Right: keep remaining."
 *
 * 1-Minute Quick Revision:
 * 1. Maintain index i = 0 and dynamic newInterval.
 * 2. Loop 1: Push intervals ending before newInterval[0].
 * 3. Loop 2: While intervals overlap (intervals[i][0] <= newInterval[1]), merge them into newInterval.
 * 4. Push the merged newInterval.
 * 5. Loop 3: Push remaining intervals.
 * 
 * Dry Run:
 * intervals = [[1,3],[6,9]], newInterval = [2,5]
 *
 * | Iteration / Step | i | Current Interval | overlap condition? | newInterval (updated) | Action / Result State |
 * |------------------|---|------------------|--------------------|-----------------------|-----------------------|
 * | Before Loop      | 0 | -                | -                  | [2, 5]                | ans = []              |
 * | Loop 1 (Left)    | 0 | [1, 3]           | 3 < 2 is false     | [2, 5]                | Left loop doesn't run |
 * | Loop 2 (Merge)   | 0 | [1, 3]           | 1 <= 5 is true     | [min(2,1), max(5,3)]  | newInterval = [1, 5]   |
 * | Loop 2 (Merge)   | 1 | [6, 9]           | 6 <= 5 is false    | [1, 5]                | Merge loop ends       |
 * | Push newInterval | 1 | -                | -                  | [1, 5]                | ans = [[1, 5]]        |
 * | Loop 3 (Right)   | 1 | [6, 9]           | -                  | -                     | ans = [[1, 5], [6, 9]]|
 */
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> ans;
        int i = 0;
        int n = intervals.size();

        // 1. Add all intervals that end before the new interval starts (no overlap)
        // [1,3] [2,5] -> [] because 3 > 2 is false.
        // [1,2] [6,9], newInterval = [3,7] -> [] because 2 > 3 is false.
        // [1,2] [6,9], newInterval = [3,7] -> [1,2] because 2 < 3 is true.
        // -> [1,2], [3,4] because 4 > 4 is false.
        // -> [1,2], [3,4], [6,9] because 4 < 6 is true.
        while (i < n && intervals[i][1] < newInterval[0]) {
            ans.push_back(intervals[i++]);
        }

        // 2. Merge all overlapping intervals with newInterval
        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval); // Add the merged interval

        // 3. Add all remaining intervals that start after the new interval ends
        while (i < n) {
            ans.push_back(intervals[i++]);
        }

        return ans;
    }
};
```

---

# 2. 01 Matrix

## Idea
We need to find the shortest distance of each cell to its nearest `0`. Since all edge weights are 1, BFS is optimal. We initialize the BFS queue with all cells containing `0` (multi-source BFS). We track distances in the output matrix directly to simplify execution.

```cpp
/*
 * Problem: Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
 * 
 * Pattern: Multi-source BFS
 * 
 * Complexity:
 * - Time Complexity: O(R * C) where R is the number of rows and C is columns.
 * - Space Complexity: O(R * C) for the queue.
 *
 * Visualizations:
 * Original Grid:      BFS Queue Init:     Step 1 (Dist=1):    Step 2 (Dist=2):
 *   [1, 1, 1]           [q, q, q]           [1, 1, 1]           [2, 1, 2]
 *   [1, 0, 1]     --->  [q, 0, q]     --->  [1, 0, 1]     --->  [1, 0, 1]
 *   [1, 1, 1]           [q, q, q]           [1, 1, 1]           [2, 1, 2]
 *
 * Memorization Hook:
 * "Push all 0s into the queue. Initialize unvisited cells to -1.
 * Pop a cell, check its 4 neighbors. If unvisited (-1), update its distance to current + 1 and push to queue."
 *
 * BFS Simplification Note:
 * - Visited array is omitted: the `dist` array initialized to -1 directly indicates whether a cell has been visited.
 * - Single loop structure: no nested loops are used to process level-by-level, as queue pops naturally increment distances.
 *
 * 1-Minute Quick Revision:
 * 1. Initialize `dist` matrix with 0 for all mat[r][c] == 0, and -1 for others.
 * 2. Push all (r, c) of 0s into a queue.
 * 3. While queue is not empty:
 *    - Pop (r, c).
 *    - Loop through 4 directions.
 *    - If neighbor is within bounds and dist[nr][nc] == -1, set dist[nr][nc] = dist[r][c] + 1 and push.
 *
 * Dry Run:
 * Grid = [[0,0,0],[0,1,0],[1,1,1]]
 * dist = [[0,0,0],[0,-1,0],[-1,-1,-1]]
 *
 * | Pop Cell | Neighbor | Unvisited? | dist[Neighbor] Update | Queue Push |
 * |----------|----------|------------|-----------------------|------------|
 * | (0, 0)   | -        | -          | -                     | -          |
 * | (0, 1)   | (1, 1)   | Yes (-1)   | dist[1][1] = 0 + 1 = 1| Push (1,1) |
 * | (1, 0)   | (2, 0)   | Yes (-1)   | dist[2][0] = 0 + 1 = 1| Push (2,0) |
 * | (1, 2)   | (2, 2)   | Yes (-1)   | dist[2][2] = 0 + 1 = 1| Push (2,2) |
 * | (1, 1)   | (2, 1)   | Yes (-1)   | dist[2][1] = 1 + 1 = 2| Push (2,1) |
 */
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        queue<pair<int, int>> q;

        // Simplify BFS: Use the output distance matrix directly instead of a separate visited array
        vector<vector<int>> dist(m, vector<int>(n, -1));

        // Initialize queue with all 0s and set their distance to 0
        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (mat[r][c] == 0) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }
            }
        }

        // 4 directions of movement (Up, Down, Left, Right)
        int dirs[4][2] = {{-1, 0}, 
                          {1, 0}, 
                          {0, -1}, 
                          {0, 1}
                        };

        // Single loop structure (no nested level-by-level loop)
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (auto& dir : dirs) {
                int nr = r + dir[0];
                int nc = c + dir[1];

                // Check boundaries and if cell is unvisited (distance is -1)
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1; // Update distance directly
                    q.push({nr, nc});
                }
            }
        }

        return dist;
    }
};
```

---

# 3. K Closest Points to Origin

## Idea
We want to find the $K$ points closest to $(0,0)$. We can maintain a Max Heap of size $K$. When a new point's distance is smaller than the maximum distance in our heap, we pop the maximum and insert the new point.

```cpp
/*
 * Problem: Find the k closest points to the origin (0, 0) in a 2D plane.
 * 
 * Pattern: Heap / Priority Queue
 * 
 * Complexity:
 * - Time Complexity: O(N * log K) where N is the number of points.
 * - Space Complexity: O(K) to store the heap elements.
 *
 * Detailed STL Mechanics for Custom Comparators:
 * 1. Functor Instantiation:
 *    The `std::priority_queue` is declared as:
 *    `std::priority_queue<vector<int>, vector<vector<int>>, Compare> maxHeap;`
 *    Here, `Compare` is a custom struct acting as a functor (function object) containing a member function `operator()`.
 *    The priority_queue instantiates an instance of this struct.
 * 
 * 2. Internal Invocation:
 *    Whenever a new point is pushed, the container calls `Compare::operator()(point_A, point_B)` to establish relative ordering.
 * 
 * 3. Boolean Return & Heap Priority:
 *    - In C++ `std::priority_queue`, the default underlying helper is `std::make_heap`, which constructs a Max Heap.
 *    - The heap condition requires that parent nodes have higher priority (larger values) than child nodes.
 *    - If `Compare()(a, b)` returns `true`, it tells the heap that `a` has LOWER priority than `b`.
 *    - Therefore, `a` will be bubbled-down relative to `b`.
 *    - By returning `distA < distB`, the point with the larger distance (larger `distA`) is evaluated as having lower priority, so it bubbles down to the bottom? 
 *      Wait, no! If `distA < distB` is true, then `a` has lower priority than `b`.
 *      So `b` (with larger distance) is placed higher up (i.e. top).
 *      This creates a Max Heap where the element with the MAXIMUM distance resides at the top (top() of the priority_queue).
 *
 * Memorization Hook:
 * "Max Heap of size K. If size exceeds K, pop. We are left with the K smallest elements."
 *
 * 1-Minute Quick Revision:
 * 1. Define Compare functor calculating x^2 + y^2. Return distA < distB for Max Heap.
 * 2. Push points to maxHeap.
 * 3. If maxHeap.size() > k, pop top.
 * 4. Move remaining points from heap to output vector.
 * 
 * Dry Run:
 * Points = [[1, 3], [-2, 2]], K = 1
 *
 * | Point    | Dist^2 | Heap State (Top to Bottom) | Action                 |
 * |----------|--------|----------------------------|------------------------|
 * | [1, 3]   | 10     | [[1, 3]]                   | Push [1, 3]            |
 * | [-2, 2]  | 8      | [[1, 3], [-2, 2]]          | Push [-2, 2], size > K |
 * | -        | -      | [[-2, 2]]                  | Pop top ([1, 3])       |
 */
struct Compare {
    bool operator()(const vector<int>& a, const vector<int>& b) const {
        int distA = a[0] * a[0] + a[1] * a[1];
        int distB = b[0] * b[0] + b[1] * b[1];
        // Returns true if a's distance is less than b's distance.
        // This tells std::priority_queue that a has lower priority than b.
        // Therefore, b (larger distance) is placed closer to the top.
        // This creates a MAX heap where the point with maximum distance is at top().
        return distA < distB;
    }
};

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // maxHeap of size k to keep track of the k closest points
        priority_queue<vector<int>, vector<vector<int>>, Compare> maxHeap;

        for (const auto& point : points) {
            maxHeap.push(point);
            if (maxHeap.size() > k) {
                maxHeap.pop(); // Pop the farthest point to maintain size K
            }
        }

        vector<vector<int>> ans;
        while (!maxHeap.empty()) {
            ans.push_back(maxHeap.top());
            maxHeap.pop();
        }
        return ans;
    }
};
```

---

# 4. Longest Substring Without Repeating Characters

## Idea
Using a sliding window with two pointers (`left` and `right`), we expand the window to the right. We maintain the last seen index of each character. If we see a character that is already in our window (i.e. its last seen index is $\ge$ `left`), we shrink the window by moving `left` to `last_seen[char] + 1`.

```cpp
/*
 * Problem: Find the length of the longest substring without repeating characters.
 * 
 * Pattern: Sliding Window (Two Pointers)
 * 
 * Complexity:
 * - Time Complexity: O(N) where N is the length of the string.
 * - Space Complexity: O(1) auxiliary space (fixed character map of size 128).
 *
 * Memorization Hook:
 * "Store last seen indices. Slide right.
 * If right char last seen >= left, update left = last_seen + 1.
 * Record max(right - left + 1)."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize vector `last_seen` of size 128 with -1.
 * 2. Set left = 0, max_len = 0.
 * 3. Loop right from 0 to n-1:
 *    - If last_seen[s[right]] >= left, set left = last_seen[s[right]] + 1.
 *    - Update last_seen[s[right]] = right.
 *    - max_len = max(max_len, right - left + 1).
 * 
 * Dry Run:
 * s = "pwwkew"
 *
 * | right | Char | Left (before) | Left (after)   | Window Len | Max Len | Last Seen Array Update | condition: (last_seen[curr] >= left) |
 * |-------|------|---------------|----------------|------------|---------|------------------------|----------------------------------------|
 * | 0     | 'p'  | 0             | 0              | 1          | 1       | last_seen['p'] = 0     | false                                  |
 * | 1     | 'w'  | 0             | 0              | 2          | 2       | last_seen['w'] = 1     | false                                  |
 * | 2     | 'w'  | 0             | max(0, 1 + 1)=2| 1          | 2       | last_seen['w'] = 2     | true                                   |
 * | 3     | 'k'  | 2             | 2              | 2          | 2       | last_seen['k'] = 3     | false                                  |
 * | 4     | 'e'  | 2             | 2              | 3          | 3       | last_seen['e'] = 4     | false                                  |
 * | 5     | 'w'  | 2             | max(2, 2 + 1)=3| 3          | 3       | last_seen['w'] = 5     | true                                   |
 */
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // Map to store the last seen index of characters (initialized to -1)
        vector<int> last_seen(128, -1);
        int max_len = 0;
        int left = 0; // Left pointer of the sliding window

        for (int right = 0; right < s.length(); ++right) {
            char curr = s[right];
            
            // If the character is already inside the current window, move the left pointer
            // When will it be true? When last_seen[curr] < left, it will be false.
            // left is the start of the current window. So if last_seen[curr] is less than left, 
            // it means the character was seen before the current window started, so it's not inside the current window.
            // Dry run example s = "abad", left=0, right=1
            // right=0, curr = 'a'. last_seen['a'] = -1. -1 < 0. left = 0. last_seen['a'] = 0. max_len = 1
            // right=1, curr = 'b'. last_seen['b'] = -1. -1 < 0. left = 0. last_seen['b'] = 1. max_len = 2
            // right=2, curr = 'a'. last_seen['a'] = 0. 0 >= 0. left = 0 + 1 = 1. last_seen['a'] = 2. max_len = 2
            // right=3, curr = 'd'. last_seen['d'] = -1. -1 < 1. left = 1. last_seen['d'] = 3. max_len = 3
            
            if (last_seen[curr] >= left) {
                left = last_seen[curr] + 1;
            }

            last_seen[curr] = right; // Update last seen position
            max_len = max(max_len, right - left + 1); // Update maximum length
        }

        return max_len;
    }
};
```

---

# 5. 3Sum

## Idea
To find triplets that sum to 0, we can sort the array first. This allows us to use a two-pointer approach for each element `nums[i]` and easily skip duplicates to avoid duplicate triplets in the output.

```cpp
/*
 * Problem: Find all unique triplets in the array which gives the sum of zero.
 * 
 * Pattern: Sorting + Two Pointers
 * 
 * Complexity:
 * - Time Complexity: O(N^2) where N is the size of the array.
 * - Space Complexity: O(1) auxiliary space (excluding space needed for sorting/output).
 *
 * Memorization Hook:
 * "Sort. Loop i. If nums[i] > 0 break. Skip i duplicate.
 * Use two pointers: left = i+1, right = n-1.
 * If sum == 0, record, skip duplicates for left and right. Move both."
 *
 * 1-Minute Quick Revision:
 * 1. Sort the input array.
 * 2. Loop i from 0 to n-3. If nums[i] > 0, break. If i > 0 and nums[i] == nums[i-1], skip.
 * 3. Set left = i + 1, right = n - 1.
 * 4. While left < right:
 *    - sum = nums[i] + nums[left] + nums[right].
 *    - If sum == 0, add triplet to output, increment left, decrement right, skipping duplicates.
 *    - If sum < 0, left++.
 *    - If sum > 0, right--.
 * 
 * Dry Run:
 * nums = [-1, 0, 1, 2, -1, -4] -> Sorted: [-4, -1, -1, 0, 1, 2]
 *
 * | i  | nums[i] | left | right | sum               | Action / State Update              |
 * |----|---------|------|-------|-------------------|------------------------------------|
 * | 0  | -4      | 1    | 5     | -4 + (-1) + 2 = -3| sum < 0 -> left++                  |
 * | 0  | -4      | 2    | 5     | -4 + (-1) + 2 = -3| sum < 0 -> left++                  |
 * | 0  | -4      | 3    | 5     | -4 + 0 + 2 = -2   | sum < 0 -> left++                  |
 * | 0  | -4      | 4    | 5     | -4 + 1 + 2 = -1   | sum < 0 -> left++ (ends loop)      |
 * | 1  | -1      | 2    | 5     | -1 + (-1) + 2 = 0 | Found: [-1, -1, 2]. left++, right--|
 * | 1  | -1      | 3    | 4     | -1 + 0 + 1 = 0    | Found: [-1, 0, 1]. left++, right-- |
 */
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int n = nums.size();
        sort(nums.begin(), nums.end()); // Sort to enable two-pointer search and skip duplicates

        for (int i = 0; i < n - 2; ++i) {
            // Optimization: if first element is > 0, no triplet can sum to 0
            if (nums[i] > 0) break;

            // Skip duplicate values for the first element i
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    ans.push_back({nums[i], nums[left], nums[right]});
                    
                    // Skip duplicates for left and right pointers
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;

                    left++;
                    right--;
                } else if (sum < 0) {
                    left++; // Sum too small, move left pointer to increase sum
                } else {
                    right--; // Sum too large, move right pointer to decrease sum
                }
            }
        }
        return ans;
    }
};
```

---

# 6. Binary Tree Level Order Traversal

## Idea
We want to return node values grouped by tree levels. To adhere to BFS simplification rules, we avoid nested level-by-level loops by pushing pairs of `{TreeNode*, int level}` into the queue. This processes nodes in a single flat loop.

```cpp
/*
 * Problem: Return the level order traversal of its nodes' values.
 * 
 * Pattern: BFS / Queue
 * 
 * Complexity:
 * - Time Complexity: O(N) where N is the number of nodes.
 * - Space Complexity: O(N) for queue storage.
 *
 * Visualizations:
 *        3 [Level 0]
 *       / \
 *      9   20 [Level 1]
 *         /  \
 *        15   7 [Level 2]
 *
 * Memorization Hook:
 * "Queue holds {node, level}. Pop, push val into ans[level].
 * Push left/right child with level + 1."
 *
 * BFS Simplification Note:
 * - Avoids nested `while(sz--)` loops by tracking the level directly in the queue items.
 *
 * 1-Minute Quick Revision:
 * 1. Queue stores pair {node, level}. Push {root, 0}.
 * 2. While queue is not empty:
 *    - Pop {node, level}.
 *    - If ans.size() == level, push an empty vector to ans.
 *    - Append node->val to ans[level].
 *    - Push left/right children with level + 1.
 * 
 * Dry Run:
 *
 * | Popped Node | Level | ans size (before) | Action / ans Update       | Queue Pushes          |
 * |-------------|-------|--------------------|---------------------------|-----------------------|
 * | 3           | 0     | 0                  | Add list; ans[0] = [3]    | Push (9, 1), (20, 1)  |
 * | 9           | 1     | 1                  | Add list; ans[1] = [9]    | -                     |
 * | 20          | 1     | 2                  | ans[1] = [9, 20]          | Push (15, 2), (7, 2)  |
 * | 15          | 2     | 2                  | Add list; ans[2] = [15]   | -                     |
 * | 7           | 2     | 3                  | ans[2] = [15, 7]          | -                     |
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (!root) return ans;

        // BFS Simplification: Queue stores pairs of {node, level} to avoid nested level-by-level loops
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, level] = q.front();
            q.pop();

            // If we are visiting a level for the first time, add a new row
            if (ans.size() == level) {
                ans.push_back({});
            }

            ans[level].push_back(node->val); // Group values by level

            // Push left and right children with incremented level
            if (node->left) q.push({node->left, level + 1});
            if (node->right) q.push({node->right, level + 1});
        }

        return ans;
    }
};
```

---

# 7. Clone Graph

## Idea
We need to clone a connected undirected graph. Using DFS, we copy each node we visit. To prevent cycles and infinite recursion, we use an `unordered_map` mapping original nodes to their cloned copies.

```cpp
/*
 * Problem: Clone an undirected connected graph.
 * 
 * Pattern: DFS / Graph traversal
 * 
 * Complexity:
 * - Time Complexity: O(V + E) where V is vertices and E is edges.
 * - Space Complexity: O(V) for the hash map and recursion stack.
 *
 * Visualizations:
 * Original:             Cloned map:            Cloned Graph:
 *   1 --- 2               1 -> [1']              1' --- 2'
 *   |     |               |     |                |      |
 *   4 --- 3               4 -> [4']              4' --- 3'
 *
 * Memorization Hook:
 * "Use clone map. If node in map, return clone.
 * Else clone, put in map, recursively clone neighbors."
 *
 * 1-Minute Quick Revision:
 * 1. Define global clone map: unordered_map<Node*, Node*>.
 * 2. DFS function `cloneGraph(node)`:
 *    - If node is null, return null.
 *    - If clone map has node, return map[node].
 *    - Create copy node, add to map.
 *    - Iterate through neighbors, clone recursively, and append to copy's neighbors.
 *    - Return copy.
 * 
 * Dry Run:
 * Nodes 1, 2, 3 in a ring: 1 - 2 - 3 - 1
 *
 * | DFS Call on Node | Map State (Original -> Clone) | Action / Cloned Neighbor Connections |
 * |------------------|-------------------------------|--------------------------------------|
 * | cloneGraph(1)    | {1: 1'}                       | Clone node 1; invoke cloneGraph(2)  |
 * | cloneGraph(2)    | {1: 1', 2: 2'}                | Clone node 2; invoke cloneGraph(3)  |
 * | cloneGraph(3)    | {1: 1', 2: 2', 3: 3'}          | Clone node 3; invoke cloneGraph(1)  |
 * | cloneGraph(1)    | {1: 1', 2: 2', 3: 3'}          | 1 is already in map, return 1'       |
 * | Back to 3        | {1: 1', 2: 2', 3: 3'}          | Connect 3' -> 1' and 3' -> 2'        |
 * | Back to 2        | {1: 1', 2: 2', 3: 3'}          | Connect 2' -> 3' and 2' -> 1'        |
 */
class Solution {
private:
    // Hash map to map original nodes to their cloned copies
    unordered_map<Node*, Node*> cloned;

public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        // If the node is already cloned, return its copy to prevent cycles
        if (cloned.find(node) != cloned.end()) {
            return cloned[node];
        }

        // Create a clone of the current node
        Node* copy = new Node(node->val);
        cloned[node] = copy;

        // Recursively clone and link all neighbors
        for (Node* neighbor : node->neighbors) {
            copy->neighbors.push_back(cloneGraph(neighbor));
        }

        return copy;
    }
};
```

---

# 8. Evaluate Reverse Polish Notation

## Idea
For RPN expression evaluation, we scan tokens from left to right. When we see a number, we push it onto a stack. When we see an operator, we pop two numbers, apply the operator (second popped is left operand, first popped is right operand), and push the result back.

```cpp
/*
 * Problem: Evaluate the value of an arithmetic expression in Reverse Polish Notation.
 * 
 * Pattern: Stack
 * 
 * Complexity:
 * - Time Complexity: O(N) where N is the number of tokens.
 * - Space Complexity: O(N) to store values in the stack.
 *
 * Accumulator Trace Clarity Note:
 * - Stack arithmetic: order of operands is critical for subtraction/division.
 *   op2 is popped first (right operand), then op1 is popped second (left operand).
 *   Result = op1 (operator) op2.
 *
 * Memorization Hook:
 * "Number? Push. Operator? Pop two. Compute (first pop is right, second is left). Push result."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize stack<int> s.
 * 2. Loop token in tokens:
 *    - If token is an operator:
 *      * op2 = s.top(); s.pop();
 *      * op1 = s.top(); s.pop();
 *      * Push computation result (op1 + op2, op1 - op2, op1 * op2, or op1 / op2).
 *    - Else push stoi(token).
 * 3. Return s.top().
 * 
 * Dry Run:
 * tokens = ["2", "1", "+", "3", "*"]
 *
 * | Token | Action | Pop Operand 1 (Right) | Pop Operand 2 (Left) | Computation | Push Result | Stack State (Bottom to Top) |
 * |-------|--------|-----------------------|----------------------|-------------|-------------|-----------------------------|
 * | "2"   | Push   | -                     | -                    | -           | 2           | [2]                         |
 * | "1"   | Push   | -                     | -                    | -           | 1           | [2, 1]                      |
 * | "+"   | Op     | 1                     | 2                    | 2 + 1 = 3   | 3           | [3]                         |
 * | "3"   | Push   | -                     | -                    | -           | 3           | [3, 3]                      |
 * | "*"   | Op     | 3                     | 3                    | 3 * 3 = 9   | 9           | [9]                         |
 */
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> s;

        for (const string& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                // Pop the two operands (first popped is right operand, second is left)
                int op2 = s.top(); s.pop();
                int op1 = s.top(); s.pop();

                if (token == "+") s.push(op1 + op2);
                else if (token == "-") s.push(op1 - op2);
                else if (token == "*") s.push(op1 * op2);
                else if (token == "/") s.push(op1 / op2);
            } else {
                s.push(stoi(token)); // Token is a number, push to stack
            }
        }
        return s.top();
    }
};
```