# Module 10: Hashing & Dynamic Programming (Lectures 143–148)

## 📋 Syllabus
*   **Hashing:** Collision Handling, Hash Maps.
*   **DP Intro:** Climbing Stairs, House Robber 1 & 2.

---

## 🟢 Section 1: Hashing

### 🎯 Solution 10.1: Collision Handling in Hashing (Chaining & Linear Probing)
*   **Concept:** Hashing maps keys to indices using a hash function. Collisions (when multiple keys map to the same index) are resolved using Chaining (linked lists at each bucket) or Open Addressing (finding another empty slot, like Linear Probing).
*   **C++ Code:**
```cpp
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

// Hashing with Collision Handling (Separate Chaining)
class HashTable {
    int BUCKET;
    std::vector<std::list<int>> table;
    int hashFunction(int x) { return x % BUCKET; }
public:
    HashTable(int b) {
        BUCKET = b;
        table.resize(BUCKET);
    }
    
    void insertItem(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }
    
    void deleteItem(int key) {
        int index = hashFunction(key);
        auto it = std::find(table[index].begin(), table[index].end(), key);
        if (it != table[index].end()) {
            table[index].erase(it);
        }
    }
    
    bool searchItem(int key) {
        int index = hashFunction(key);
        auto it = std::find(table[index].begin(), table[index].end(), key);
        return it != table[index].end();
    }
};
```
*   **🔍 Dry Run:**
    *   Initialize `HashTable ht(7)` -> Buckets indexed `0` to `6`.
    *   `ht.insertItem(15)`: `15 % 7 = 1` -> Insert in bucket 1. Bucket 1 list: `[15]`.
    *   `ht.insertItem(11)`: `11 % 7 = 4` -> Insert in bucket 4. Bucket 4 list: `[11]`.
    *   `ht.insertItem(22)`: `22 % 7 = 1` -> Collision! Appended to list at bucket 1. Bucket 1 list: `[15 -> 22]`.
*   **Complexity:** Time: Average $O(1)$ for insert/delete/search, Worst $O(N)$ (if all elements hash to the same bucket). Space: $O(N)$ total elements stored.

---

## 🟢 Section 2: Dynamic Programming

### 🎯 Solution 10.2: Climbing Stairs (Space Optimized DP)
*   **Problem:** Find the number of distinct ways to reach the top of $N$ stairs if you can climb 1 or 2 steps at a time.
*   **C++ Code:**
```cpp
int climbStairs(int n) {
    if (n <= 1) return 1;
    int prev2 = 1; // ways(i - 2)
    int prev1 = 1; // ways(i - 1)
    
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
```
*   **Complexity:** Time: $O(N)$, Space: $O(1)$ auxiliary.

### 🎯 Solution 10.3: House Robber 1 & 2
*   **Problem:**
    *   **House Robber 1:** Rob houses in a row to maximize money without robbing two adjacent houses.
    *   **House Robber 2:** Same as above, but houses are arranged in a circle (first and last are adjacent).
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

// 1. House Robber 1 (Linear array)
int robLinear(const std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    int prev2 = 0;
    int prev1 = nums[0];
    
    for (int i = 1; i < n; i++) {
        int pick = nums[i] + prev2;
        int nonPick = prev1;
        int curr = std::max(pick, nonPick);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

// Helper for House Robber 2
int robHelper(const std::vector<int>& nums, int start, int end) {
    int prev2 = 0;
    int prev1 = 0;
    for (int i = start; i <= end; i++) {
        int temp = std::max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = temp;
    }
    return prev1;
}

// 2. House Robber 2 (Circular array)
int robCircular(const std::vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    
    // Max of: (rob excluding last house) or (rob excluding first house)
    return std::max(robHelper(nums, 0, n - 2), robHelper(nums, 1, n - 1));
}
```
*   **🔍 Dry Run (House Robber 1 on `{2, 7, 9, 3, 1}`):**
    *   `prev2 = 0`, `prev1 = nums[0] (2)`.
    *   `i = 1 (7)`: `curr = max(7 + 0, 2) = 7`. `prev2 = 2`, `prev1 = 7`.
    *   `i = 2 (9)`: `curr = max(9 + 2, 7) = 11`. `prev2 = 7`, `prev1 = 11`.
    *   `i = 3 (3)`: `curr = max(3 + 7, 11) = 11`. `prev2 = 11`, `prev1 = 11`.
    *   `i = 4 (1)`: `curr = max(1 + 11, 11) = 12`. `prev2 = 11`, `prev1 = 12`.
    *   **Result:** `12`.
*   **Complexity:** Time: $O(N)$, Space: $O(1)$ auxiliary.
