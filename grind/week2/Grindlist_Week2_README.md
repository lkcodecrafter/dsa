# Grind 75 - Week 2 (C++)

# 1. First Bad Version

## Idea
Use Binary Search to find the first bad version.


```cpp
/*
 * Problem: Find the first bad version. You are given an API isBadVersion(version) which returns whether a version is bad.
 * 
 * Pattern: Binary Search (Boundary Finding / Leftmost Match)
 * 
 * Complexity:
 * - Time Complexity: O(log n)
 * - Space Complexity: O(1)
 *
 * Memorization Hook:
 * "Search range is [1, n]. Find mid. If mid is bad, the first bad version is either mid or to its left (right = mid).
 * If mid is good, the first bad version must be to its right (left = mid + 1). Narrow down until left == right."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize left = 1, right = n.
 * 2. Loop while left < right:
 *    - mid = left + (right - left) / 2.
 *    - If isBadVersion(mid) is true, move right to mid.
 *    - Else, move left to mid + 1.
 * 3. Return left (pointing to the first bad version).
 * 
 * Dry Run:
 * n = 5, first bad = 4
 *
 * | Iteration | left | right | mid | isBadVersion(mid) | Action / State Update |
 * |    ---    |---   |---    |---  |---                |         ---         |
 * | 1         | 1    | 5     | 3   | false (good)      | left = mid + 1 = 4  |
 * | 2         | 4    | 5     | 4   | true (bad)        | right = mid = 4     |
 * | Loop Ends | 4 (left == right) | | | | Return 4        |
 */
class Solution {
public:
    int firstBadVersion(int n) {
        long long left = 1;  // Start boundary of versions
        long long right = n; // End boundary of versions

        // Binary search to narrow down to the first bad version
        while (left < right) {
            // Prevent integer overflow during mid calculation
            long long mid = left + (right - left) / 2;

            if (isBadVersion(mid)) {
                // If mid is bad, the first bad version is either mid or to the left of mid
                right = mid;
            } else {
                // If mid is good, the first bad version must be to the right of mid
                left = mid + 1;
            }
        }
        // When left == right, we have found the first bad version
        return left;
    }
};
```


where is BadVersion API?
isBadVersion(int version) is a predefined API that you can call to determine if a given version is bad. It returns true if the version is bad and false if it is good. You do not need to implement this API; it is provided by the system. You can use it in your solution to check if a specific version is bad or not while performing the binary search to find the first bad version.
---

# 2. Ransom Note

## Idea
Count characters using frequency array.

```cpp
/*
 * Problem: Given two strings ransomNote and magazine, return true if ransomNote can be constructed from magazine and false otherwise.
 * 
 * Pattern: Frequency Count (Array Hash Map)
 * 
 * Complexity:
 * - Time Complexity: O(n + m) where n is the length of ransomNote and m is the length of magazine
 * - Space Complexity: O(1) as the frequency vector size is fixed at 26
 *
 * Memorization Hook:
 * "Count the letters in magazine first. Then, read ransomNote character by character, decrementing the frequency map.
 * If any character's count drops below zero, it means we don't have enough, so return false. Otherwise, return true."
 *
 * 1-Minute Quick Revision:
 * 1. Create a frequency array of size 26 initialized to 0.
 * 2. Loop over magazine to count characters.
 * 3. Loop over ransomNote: decrement the character's frequency. If it drops below 0, return false.
 * 4. Return true if all characters are matched successfully.
 * 
 * Dry Run:
 * ransomNote = "aa", magazine = "aab"
 *
 * | Char | freq[c-'a'] (before) | freq[c-'a'] (after) | Condition (< 0) | Action     |
 * | ---  |         ---          |         ---          |       ---       |    ---     |
 * | 'a'  | 2                    | 1                    | false           | Keep going |
 * | 'a'  | 1                    | 0                    | false           | Keep going |
 */
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        vector<int> freq(26, 0); // Frequency counter for letters 'a' through 'z'

        // Count character occurrences in the magazine
        for (char c : magazine) {
            freq[c - 'a']++;
        }

        // Verify if we can construct ransomNote
        for (char c : ransomNote) {
            // Execution trace for ransomNote = "aa", magazine = "aab"
            // Char 1: c = 'a' -> freq['a'-'a'] decrements from 2 to 1. Condition (1 < 0) is false.
            // Char 2: c = 'a' -> freq['a'-'a'] decrements from 1 to 0. Condition (0 < 0) is false.
            freq[c - 'a']--;

            if (freq[c - 'a'] < 0) {
                return false; // Mismatch: character count exhausted
            }
        }

        return true; // Successfully matched all characters
    }
};
```

---

# 3. Climbing Stairs

## Idea
Same as Fibonacci.

```cpp
/*
 * Problem: It takes n steps to reach the top. Each time you can either climb 1 or 2 steps.
 * In how many distinct ways can you climb to the top?
 * 
 * Pattern: Dynamic Programming (Fibonacci)
 * 
 * Complexity:
 * - Time Complexity: O(n)
 * - Space Complexity: O(1)
 *
 * Memorization Hook:
 * "To reach step i, you must come from step i-1 or step i-2. So, ways(i) = ways(i-1) + ways(i-2).
 * Maintain the last two states to achieve constant space."
 *
 * 1-Minute Quick Revision:
 * 1. If n <= 2, return n.
 * 2. Initialize a = 1 (ways for step 1), b = 2 (ways for step 2).
 * 3. Loop from 3 to n:
 *    - c = a + b
 *    - a = b
 *    - b = c
 * 4. Return b.
 * 
 * Dry Run:
 * n = 5
 *
 * | Step (i) |  a  |  b  |  c = a + b  | Updated a | Updated b | Notes                         |
 * |   ---    | --- | --- |     ---     |    ---    |    ---    |              ---              |
 * | Initial  | 1   | 2   | -           | 1         | 2         | Base states for steps 1 and 2 |
 * | 3        | 1   | 2   | 3           | 2         | 3         | c = 1 + 2 = 3                 |
 * | 4        | 2   | 3   | 5           | 3         | 5         | c = 2 + 3 = 5                 |
 * | 5        | 3   | 5   | 8           | 5         | 8         | c = 3 + 5 = 8                 |
 * | End Loop | -   | -   | -           | 5         | 8         | Return b (8 ways)             |
 */
class Solution {
public:
    int climbStairs(int n) {
        // Base case: 1 step has 1 way, 2 steps have 2 ways
        if (n <= 2) return n;

        int a = 1; // Ways to reach step 1
        int b = 2; // Ways to reach step 2

        // Iteratively calculate ways up to step n
        for (int i = 3; i <= n; i++) {
            // Execution trace for n = 5:
            // i = 3: c = 1 + 2 = 3 | a becomes 2 | b becomes 3
            // i = 4: c = 2 + 3 = 5 | a becomes 3 | b becomes 5
            // i = 5: c = 3 + 5 = 8 | a becomes 5 | b becomes 8
            int c = a + b;
            a = b;
            b = c;
        }

        return b; // Total ways to reach step n
    }
};
```

---

# 4. Longest Palindrome

## Idea
Use frequency counting.


```cpp
/*
 * Problem: Given a string s containing lowercase/uppercase letters, return the length of the longest palindrome that can be built from those letters.
 * 
 * Pattern: Frequency Count (Greedy)
 * 
 * Complexity:
 * - Time Complexity: O(n) where n is the length of string s
 * - Space Complexity: O(k) where k is the size of the character set (constant memory)
 *
 * Memorization Hook:
 * "To build a palindrome, we need pairs of characters. Add all even counts. For odd counts,
 * add (count - 1) and set a flag. If the flag is set, add 1 at the end for the center character."
 *
 * 1-Minute Quick Revision:
 * 1. Build a character frequency map.
 * 2. Loop through each count:
 *    - If count is even, add all to answer.
 *    - If count is odd, add count - 1 to answer and set odd flag = true.
 * 3. If odd flag is true, add 1 to the answer.
 * 4. Return answer.
 *
 * Dry Run:
 * s = "abccccdd"
 * Map frequency: a:1, b:1, c:4, d:2
 *
 * | Character | Count | Count % 2 == 0 | Contribution | New Ans | Has Odd? | Notes                            |
 * |    ---    |  ---  |      ---       |     ---      |   ---   |   ---    |               ---                |
 * | 'a'       | 1     | false          | 1 - 1 = 0    | 0       | true     | Odd count seen. Add 0, flag odd. |
 * | 'b'       | 1     | false          | 1 - 1 = 0    | 0       | true     | Odd count seen. Add 0, flag odd. |
 * | 'c'       | 4     | true           | 4            | 4       | true     | Even count. Add all 4.           |
 * | 'd'       | 2     | true           | 2            | 6       | true     | Even count. Add all 2.           |
 * | End Loop  | -     | -              | +1 for center| 7       | true     | Since has_odd is true, add 1.    |
 */
class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> mp; // Frequency map for characters

        // Count frequency of each character in s
        for (char c : s) {
            mp[c]++;
        }

        int ans = 0;      // Length of the longest palindrome
        bool odd = false; // Flag to check if we have any character with an odd count

        for (auto &x : mp) {
            // Execution trace for s = "abccccdd" with mp = {{'a', 1}, {'b', 1}, {'c', 4}, {'d', 2}}
            // Iteration 1 (key='a'): x.second = 1
            // Iteration 2 (key='b'): x.second = 1
            // Iteration 3 (key='c'): x.second = 4
            // Iteration 4 (key='d'): x.second = 2

            if (x.second % 2 == 0) {
                ans += x.second;     // Iteration 3: ans = 0 + 4 = 4 | Iteration 4: ans = 4 + 2 = 6
            } else {
                ans += x.second - 1; // Iteration 1: ans = 0 | Iteration 2: ans = 0
                odd = true;          // Iteration 1: odd = true | Iteration 2: odd = true
            }
        }

        // If there was at least one character with an odd count, 
        // we can place one of them in the center of the palindrome
        if (odd) {
            ans++;
        }

        return ans;
    }
};
```

longest palindrome means ?
Longest palindrome means the longest string that can be formed by rearranging the characters of the given string such that it reads the same forwards and backwards. For example, in the string "abccccdd", the longest palindrome that can be formed is "dccaccd" or "dccbccd", which has a length of 7. The characters 'c' and 'd' can be used to form pairs, while 'a' and 'b' can only be used once as the center of the palindrome.
---

# 5. Reverse Linked List

## Idea
Reverse pointers one by one.

```cpp
/*
 * Problem: Given the head of a singly linked list, reverse the list, and return the reversed list.
 * 
 * Pattern: Pointer Manipulation (Three-pointer technique: prev, curr, next)
 * 
 * Complexity:
 * - Time Complexity: O(n) where n is the number of nodes in the linked list
 * - Space Complexity: O(1) auxiliary space
 *
 * Memorization Hook:
 * "Keep track of the prev node (initially null) and curr node (initially head). In each step, save curr->next,
 * point curr->next to prev, then advance both prev and curr one step forward."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize prev = nullptr, curr = head.
 * 2. Loop while curr is not null:
 *    - next = curr->next
 *    - curr->next = prev
 *    - prev = curr
 *    - curr = next
 * 3. Return prev (pointing to the new head).
 * 
 * Dry Run:
 * Input list: 1 -> 2 -> 3 -> null
 *
 * | Step | curr Node | curr->next (before) | curr->next (after) | prev (updated) | curr (updated) | Notes                       |
 * | ---  |    ---    |         ---         |        ---         |      ---       |      ---       |             ---             |
 * | Init | -         | -                   | -                  | nullptr        | 1              | Initial pointer states      |
 * | 1    | 1         | 2                   | nullptr            | 1              | 2              | Node 1 now points to null   |
 * | 2    | 2         | 3                   | 1                  | 2              | 3              | Node 2 now points to Node 1 |
 * | 3    | 3         | nullptr             | 2                  | 3              | nullptr        | Node 3 now points to Node 2 |
 * | End  | nullptr   | -                   | -                  | 3              | nullptr        | Return prev (Node 3)        |
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr; // Track the previous node
        ListNode* curr = head;    // Track the current node

        while (curr) {
            // Execution trace for list: 1 -> 2 -> 3 -> null
            // Iteration 1: next = 2 | 1->next = nullptr | prev = 1 | curr = 2
            // Iteration 2: next = 3 | 2->next = 1       | prev = 2 | curr = 3
            // Iteration 3: next = null | 3->next = 2     | prev = 3 | curr = null
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        return prev; // prev points to the new head of the reversed list
    }
};
```

---

# 6. Majority Element

## Boyer Moore Voting Algorithm

```cpp
/*
 * Problem: Given an array nums of size n, return the majority element.
 * The majority element is the element that appears more than ⌊n / 2⌋ times.
 * 
 * Pattern: Boyer-Moore Voting Algorithm
 * 
 * Complexity:
 * - Time Complexity: O(n)
 * - Space Complexity: O(1)
 *
 * Memorization Hook:
 * "Think of balanced votes canceling out. A candidate gets +1 if we see them, and loses -1 otherwise.
 * If votes count hits 0, select the current element as the new candidate. The majority candidate will survive."
 *
 * 1-Minute Quick Revision:
 * 1. Set candidate = 0, count = 0.
 * 2. Loop through each number num in nums:
 *    - If count == 0, set candidate = num.
 *    - If num == candidate, increment count.
 *    - Else, decrement count.
 * 3. Return candidate.
 * 
 * Dry Run:
 * nums = [2, 2, 1, 1, 1, 2, 2]
 *
 * | Step | num | count (before) | candidate (before) | count (after) | candidate (after) | Notes                                    |
 * | ---  | --- |      ---       |        ---         |      ---      |        ---        |                   ---                    |
 * | 1    | 2   | 0              | 0                  | 1             | 2                 | count was 0, candidate = 2, count++      |
 * | 2    | 2   | 1              | 2                  | 2             | 2                 | num == candidate, count++                |
 * | 3    | 1   | 2              | 2                  | 1             | 2                 | num != candidate, count--                |
 * | 4    | 1   | 1              | 2                  | 0             | 2                 | num != candidate, count--                |
 * | 5    | 1   | 0              | 2                  | 1             | 1                 | count was 0, candidate = 1, count++      |
 * | 6    | 2   | 1              | 1                  | 0             | 1                 | num != candidate, count--                |
 * | 7    | 2   | 0              | 1                  | 1             | 2                 | count was 0, candidate = 2, count++      |
 * | End  | -   | -              | -                  | 1             | 2                 | Return candidate (2)                     |
 */
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = 0; // Current candidate for majority element
        int count = 0;     // Net vote count for the candidate

        for (int num : nums) {
            // Execution trace for nums = [2, 2, 1, 1, 1, 2, 2]:
            // num = 2: count is 0 -> candidate becomes 2. num == candidate -> count becomes 1
            // num = 2: num == candidate -> count becomes 2
            // num = 1: num != candidate -> count becomes 1
            // num = 1: num != candidate -> count becomes 0
            // num = 1: count is 0 -> candidate becomes 1. num == candidate -> count becomes 1
            // num = 2: num != candidate -> count becomes 0
            // num = 2: count is 0 -> candidate becomes 2. num == candidate -> count becomes 1
            if (count == 0) {
                candidate = num;
            }

            if (num == candidate) {
                count++;
            } else {
                count--;
            }
        }

        return candidate;
    }
};
```

---


# 7. Add Binary

```cpp
/*
 * Problem: Given two binary strings a and b, return their sum as a binary string.
 * 
 * Pattern: Math Simulation (Two Pointers & Carry)
 * 
 * Complexity:
 * - Time Complexity: O(max(n, m)) where n and m are lengths of strings a and b
 * - Space Complexity: O(1) auxiliary space (excluding output string)
 *
 * Memorization Hook:
 * "Traverse strings from right to left. Add digits and carry. Sum % 2 gives the current binary digit,
 * and Sum / 2 gives the new carry. Append, and then reverse the result string at the end."
 *
 * 1-Minute Quick Revision:
 * 1. Set pointers i = a.size() - 1, j = b.size() - 1, carry = 0, ans = "".
 * 2. Loop while i >= 0, j >= 0, or carry > 0:
 *    - sum = carry
 *    - If i >= 0, sum += a[i--] - '0'.
 *    - If j >= 0, sum += b[j--] - '0'.
 *    - Append sum % 2 to ans, set carry = sum / 2.
 * 3. Reverse ans and return.
 * 
 * Dry Run:
 * a = "11", b = "1"
 *
 * | i  | j  | carry (before) | sum = carry + digits | ans digit (sum % 2) | carry (after) | ans (so far) | Notes                              |
 * |--- |--- |----------------|----------------------|---------------------|---------------|--------------|------------------------------------|
 * | 1  | 0  | 0              | 0 + 1 + 1 = 2        | 2 % 2 = 0           | 2 / 2 = 1     | "0"          | Rightmost digits: 1 + 1            |
 * | 0  | -1 | 1              | 1 + 1 = 2            | 2 % 2 = 0           | 2 / 2 = 1     | "00"         | Middle digit of a: 1 + carry       |
 * | -1 | -1 | 1              | 1                    | 1 % 2 = 1           | 1 / 2 = 0     | "001"        | Only carry remains                 |
 * | -  | -  | -              | -                    | -                   | -             | "100"        | Loop ends. Reverse "001" -> "100"  |


how sum = carry + a[i] + b[j]:
    - Loop 1 (Rightmost digits): 0 + 1 + 1 = 2
      * 0 comes from carry (initial carry = 0)
      * 1 comes from a[1] ('1' from "11"), added when the first condition `if (i >= 0)` is met.
      * 1 comes from b[0] ('1' from "1"), added when the next condition `if (j >= 0)` is met.
    - Loop 2 (Middle digit of a): 1 + 1 + 0 = 2
      * 1 comes from carry (from Loop 1: 2 / 2 = 1)
      * 1 comes from a[0] ('1' from "11"), added when the first condition `if (i >= 0)` is met.
      * 0 comes from b[j] (since j is -1, the next condition `if (j >= 0)` is false, adding nothing).
    - Loop 3 (Final carry): 1 + 0 + 0 = 1
      * 1 comes from carry (from Loop 2: 2 / 2 = 1)
      * 0 comes from a[i] (since i is -1, the condition `if (i >= 0)` is false, adding nothing).
      * 0 comes from b[j] (since j is -1, the condition `if (j >= 0)` is false, adding nothing).

sum % 2 gives the current binary digit:
    - Loop 1: 2 % 2 = 0 
    - Loop 2: 2 % 2 = 0
    - Loop 3: 1 % 2 = 1

sum / 2 gives the new carry value:
    - Loop 1: 2 / 2 = 1 (carried to Loop 2)
    - Loop 2: 2 / 2 = 1 (carried to Loop 3)
    - Loop 3: 1 / 2 = 0 (loop terminates)
 
 */
class Solution {
public:
    string addBinary(string a, string b) {
        string ans = "";
        int carry = 0;

        int i = a.size() - 1;
        int j = b.size() - 1;

        // Traverse both strings from right to left
        while (i >= 0 || j >= 0 || carry) {
            // Execution trace for a = "11", b = "1":
            // Loop 1: i=1, j=0, carry=0 -> sum = 0 + 1 + 1 = 2. ans = "0", carry = 1
            // Loop 2: i=0, j=-1, carry=1 -> sum = 1 + 1 = 2. ans = "00", carry = 1
            // Loop 3: i=-1, j=-1, carry=1 -> sum = 1. ans = "001", carry = 0
            int sum = carry;

            if (i >= 0) sum += a[i--] - '0'; 
            if (j >= 0) sum += b[j--] - '0'; 

            ans.push_back(sum % 2 + '0'); // Append the binary digit
            carry = sum / 2;              // Determine new carry value
        }

        reverse(ans.begin(), ans.end()); // Reverse since we computed from right to left

        return ans;
    }
};
```

---

# 8. Diameter of Binary Tree

## Idea
Diameter = longest path between any two nodes.

```cpp
/*
 * Problem: Find the length of the longest path between any two nodes in a tree.
 * The path may or may not pass through the root.
 * 
 * Pattern: Tree DFS (Recursive Height calculation)
 * 
 * Complexity:
 * - Time Complexity: O(n) as we visit every node exactly once
 * - Space Complexity: O(h) recursive stack space where h is the tree height
 *
 * Memorization Hook:
 * "The diameter at any node is left_height + right_height. Recursively compute height of left and right subtrees.
 * Update the global max diameter with left_height + right_height at each node, and return 1 + max(left_height, right_height) for height."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize diameter = 0.
 * 2. Write helper height(root):
 *    - If root is null, return 0.
 *    - Calculate left_height = height(root->left) and right_height = height(root->right).
 *    - Update diameter = max(diameter, left_height + right_height).
 *    - Return 1 + max(left_height, right_height).
 * 3. Call height(root) from main function, return diameter.
 * 
 * Tree Visualization & Dry Run:
 *        1 (ht=3, left_ht=2, right_ht=1, node_diameter=3)
 *       / \
 *      2   3 (ht=1, left_ht=0, right_ht=0, node_diameter=0)
 *     / \
 *    4   5 (ht=1, left_ht=0, right_ht=0, node_diameter=0)
 *
 * | Node | Left Ht | Right Ht | Node Diameter (Left + Right) | Global Diameter (updated) | Return Height |
 * | ---  |   ---   |   ---    |             ---              |            ---            |      ---      |
 * | 4    | 0       | 0        | 0                            | 0                         | 1             |
 * | 5    | 0       | 0        | 0                            | 0                         | 1             |
 * | 2    | 1       | 1        | 2                            | 2                         | 2             |
 * | 3    | 0       | 0        | 0                            | 2                         | 1             |
 * | 1    | 2       | 1        | 3                            | 3                         | 3             |
 */
class Solution {
public:
    int diameter = 0; // Track the maximum diameter found so far

    int height(TreeNode* root) {
        if (!root) {
            return 0; // Height of null node is 0
        }

        // Recursively compute heights of subtrees
        int left = height(root->left);
        int right = height(root->right);

        // Update the maximum diameter through any node
        diameter = max(diameter, left + right);

        // Return height of current node
        return 1 + max(left, right);
    }

    int diameterOfBinaryTree(TreeNode* root) {
        height(root); // Invoke recursive helper to traverse tree
        return diameter;
    }
};
```

---

# 9. Middle of Linked List

## Fast and Slow Pointer

```cpp
/*
 * Problem: Given the head of a singly linked list, return the middle node of the list.
 * If there are two middle nodes, return the second middle node.
 * 
 * Pattern: Two-Pointer (Fast & Slow / Floyd's Tortoise and Hare)
 * 
 * Complexity:
 * - Time Complexity: O(n) where n is the number of nodes in the linked list
 * - Space Complexity: O(1) auxiliary space
 *
 * Memorization Hook:
 * "Start both slow and fast pointers at head. Move slow by 1 step and fast by 2 steps.
 * When fast or fast->next hits null, slow will be exactly at the middle."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize slow = head, fast = head.
 * 2. Loop while fast is not null and fast->next is not null:
 *    - slow = slow->next
 *    - fast = fast->next->next
 * 3. Return slow.
 * 
 * Dry Run:
 * List: 1 -> 2 -> 3 -> 4 -> 5 -> null
 *
 * | Step | slow (val) | fast (val) | fast && fast->next | Action                                |
 * | ---  |    ---     |    ---     |        ---         |                  ---                  |
 * | Init | 1          | 1          | true               | Initial state                         |
 * | 1    | 2          | 3          | true               | slow moves 1 step, fast moves 2 steps |
 * | 2    | 3          | 5          | false (5->next=x)  | slow moves 1 step, fast moves 2 steps |
 * | End  | 3          | 5          | -                  | Loop terminates, return slow (Node 3) |
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head; // Moves 1 step at a time
        ListNode* fast = head; // Moves 2 steps at a time

        // Traverse the list until fast pointer reaches the end
        while (fast && fast->next) {
            // Execution trace for list: 1 -> 2 -> 3 -> 4 -> 5
            // Iteration 1: slow moves to 2, fast moves to 3
            // Iteration 2: slow moves to 3, fast moves to 5. (fast->next is null, loop ends)
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow; // Points to the middle node
    }
};
```

---

# 10. Maximum Depth of Binary Tree

```cpp
/*
 * Problem: Find the maximum depth of a binary tree (number of nodes along the longest path).
 * 
 * Pattern: DFS Recursion / Divide and Conquer
 * 
 * Complexity:
 * - Time Complexity: O(n) as we visit every node exactly once
 * - Space Complexity: O(h) recursive stack space where h is tree height
 *
 * Memorization Hook:
 * "The depth of a tree is 1 + max(depth(left), depth(right)). If the node is null, depth is 0."
 *
 * 1-Minute Quick Revision:
 * 1. If root is null, return 0.
 * 2. Return 1 + max(maxDepth(root->left), maxDepth(root->right)).
 * 
 * Tree Visualization & Call Trace:
 *      1 (returns 1 + max(2, 0) = 3)
 *     /
 *    2 (returns 1 + max(1, 0) = 2)
 *   /
 *  3 (returns 1 + max(0, 0) = 1)

 so the ans is 3 
 *
 * Call Trace:
 * - maxDepth(1) -> returns 1 + max(maxDepth(2), maxDepth(nullptr))
 *   - maxDepth(2) -> returns 1 + max(maxDepth(3), maxDepth(nullptr))
 *     - maxDepth(3) -> returns 1 + max(nullptr, nullptr) = 1 + 0 = 1
 *
 
one more tree visualization 

         1
        / \
       2   3
      / \
     4   5
    /
   6

call Trace 

maxDepth(1) -> 1 + max(maxDepth(2), maxDepth(3)) maxDepth(1) = 1+max(2,1) = 3
  maxDepth(2) -> 1 + max(maxDepth(4), maxDepth(5)) maxDepth(2) = 1+max(1,1) =2
     maxDepth(4) -> 1 + max(maxDepth(6), maxDepth(null)) maxDepth(4) = 1+max(1,0) =2
        maxDepth(6) -> 1 + max(maxDepth(null), maxDepth(null)) maxDepth(6) = 1+max(0,0) =1
     maxDepth(5) -> 1 + max(maxDepth(null), maxDepth(null)) maxDepth(5) = 1+max(0,0) =1
  maxDepth(3) -> 1 + max(maxDepth(null), maxDepth(null)) maxDepth(3) = 1+max(0,0) =1

so the answer will be 4 (1->2->4->6) is the longest path and height of tree is 4 


 */ 
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0; // Base case: depth of null node is 0
        }

        // Return 1 (current node) + maximum of left and right child heights
        return 1 + max(maxDepth(root->left),maxDepth(root->right));
    }
};
```

---

# 11. Contains Duplicate

```cpp
/*
 * Problem: Return true if any value appears at least twice in the array, and false if every element is distinct.
 * 
 * Pattern: Hash Set (Fast Lookup)
 * 
 * Complexity:
 * - Time Complexity: O(n) amortized average time
 * - Space Complexity: O(n) to store distinct elements in set
 *
 * Memorization Hook:
 * "Traverse the array. For each element, check if it's already in our hash set. If yes, we found a duplicate,
 * return true. If no, insert it and continue. If the loop ends, return false."
 *
 * 1-Minute Quick Revision:
 * 1. Create a hash set st.
 * 2. Loop through each number x in nums:
 *    - If st.count(x) is true, return true.
 *    - Insert x into st.
 * 3. Return false.
 * 
 * Dry Run:
 * nums = [1, 2, 3, 1]
 *
 * | i | x | st status (before) | st.count(x) | Action / Result        |
 * |---|---|--------------------|-------------|------------------------|
 * | 0 | 1 | {}                 | false       | Insert 1 -> {1}        |
 * | 1 | 2 | {1}                | false       | Insert 2 -> {1, 2}     |
 * | 2 | 3 | {1, 2}             | false       | Insert 3 -> {1, 2, 3}  |
 * | 3 | 1 | {1, 2, 3}          | true        | Duplicate! Return true |
 */
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> st; // Set to store unique elements

        for (int x : nums) {
            // Execution trace for nums = [1, 2, 3, 1]:
            // x = 1: st does not count 1 -> insert 1
            // x = 2: st does not count 2 -> insert 2
            // x = 3: st does not does not count 3 -> insert 3
            // x = 1: st counts 1 -> duplicate found! Return true
            if (st.count(x)) {
                return true; // Duplicate found
            }

            st.insert(x); // Record current element
        }

        return false; // All elements are unique
    }
};
```

---

# 12. Maximum Subarray

## Kadane Algorithm

```cpp
/*
 * Problem: Find the contiguous subarray which has the largest sum and return its sum.
 * 
 * Pattern: Kadane's Algorithm (Greedy / Dynamic Programming)
 * 
 * Complexity:
 * - Time Complexity: O(n)
 * - Space Complexity: O(1)
 *
 * Memorization Hook:
 * "At each position i, decide whether to extend the current subarray sum (curr_sum + nums[i])
 * or start a fresh subarray from nums[i] itself. Update the global best_sum at each step."
 *
 * 1-Minute Quick Revision:
 * 1. Initialize curr = nums[0], best = nums[0].
 * 2. Loop from index 1 to nums.size() - 1:
 *    - curr = max(nums[i], curr + nums[i])
 *    - best = max(best, curr)
 * 3. Return best.
 * 
 * Dry Run:
 * nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
 *
 * | i | nums[i] | curr (before) | curr = max(num, curr+num) | best (updated) | Notes                               |
 * |---|---------|---------------|---------------------------|----------------|-------------------------------------|
 * | - | -       | -             | -                         | -2             | Initialize curr = best = nums[0]    |
 * | 1 | 1       | -2            | max(1, -2+1) = 1          | max(-2, 1) = 1 | Start fresh subarray at 1           |
 * | 2 | -3      | 1             | max(-3, 1-3) = -2         | max(1, -2) = 1 | Extend to include -3                |
 * | 3 | 4       | -2            | max(4, -2+4) = 4          | max(1, 4) = 4  | Start fresh subarray at 4           |
 * | 4 | -1      | 4             | max(-1, 4-1) = 3          | max(4, 3) = 4  | Extend to include -1                |
 * | 5 | 2       | 3             | max(2, 3+2) = 5           | max(4, 5) = 5  | Extend to include 2                 |
 * | 6 | 1       | 5             | max(1, 5+1) = 6           | max(5, 6) = 6  | Extend to include 1 (max reached)   |
 * | 7 | -5      | 6             | max(-5, 6-5) = 1          | max(6, 1) = 6  | Extend to include -5                |
 * | 8 | 4       | 1             | max(4, 1+4) = 5           | max(6, 5) = 6  | Extend to include 4                 |
 */
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int curr = nums[0]; // Track maximum subarray sum ending at current position
        int best = nums[0]; // Track global maximum subarray sum found

        for (int i = 1; i < nums.size(); i++) {
            // Execution trace for nums = [-2, 1, -3, 4, ...]:
            // i = 1: curr = max(1, -2 + 1) = 1 | best = max(-2, 1) = 1
            // i = 2: curr = max(-3, 1 - 3) = -2 | best = max(1, -2) = 1
            // i = 3: curr = max(4, -2 + 4) = 4 | best = max(1, 4) = 4
            // i = 4: curr = max(-1, 4 - 1) = 3 | best = max(4, 3) = 4
            // i = 5: curr = max(2, 3 + 2) = 5 | best = max(4, 5) = 5
            // i = 6: curr = max(1, 5 + 1) = 6 | best = max(5, 6) = 6
            curr = max(nums[i], curr + nums[i]);
            best = max(best, curr);
        }

        return best;
    }
};
```

---

# Week 2 Revision Table

| Problem | Pattern |
|----------|----------|
| First Bad Version | Binary Search |
| Ransom Note | Frequency Count |
| Climbing Stairs | DP / Fibonacci |
| Longest Palindrome | Hash Map |
| Reverse Linked List | Pointer Manipulation |
| Majority Element | Boyer Moore |
| Add Binary | Simulation |
| Diameter Tree | DFS |
| Middle Linked List | Fast Slow |
| Maximum Depth | DFS |
| Contains Duplicate | Hash Set |
| Maximum Subarray | Kadane Algorithm |

# Important Interview Patterns

1. Binary Search
2. Hash Map
3. Fast & Slow Pointer
4. DFS Recursion
5. Dynamic Programming
6. Kadane Algorithm
7. Boyer Moore Voting

Master these patterns and you can solve many interview questions.
