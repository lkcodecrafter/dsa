# Sliding Window Pattern – 25 Lessons (With Dry Runs & Visualizations)

## 📌 Introduction to Sliding Window Pattern
The **Sliding Window** pattern efficiently processes contiguous subarrays or substrings by moving a window over the data.

---

## 1. Maximum Sum Subarray of Size K (Easy)

### Idea
Keep a window of size `k` and slide it forward.

### C++ Code
```cpp
int maxSumSubarray(int k, vector<int>& nums) {
    int left = 0, sum = 0, ans = 0;
    for(int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        if(right >= k-1) {
            ans = max(ans, sum);
            sum -= nums[left++];
        }
    }
    return ans;
}
```

### Dry Run
`nums = [2,1,5,1,3,2], k = 3`

Window sums:
- [2,1,5] = 8
- [1,5,1] = 7
- [5,1,3] = 9 ✅
- [1,3,2] = 6

---

## 2. Smallest Subarray With a Greater Sum (Easy)

### C++ Code
```cpp
int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0, sum = 0, ans = INT_MAX;
    for(int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        while(sum >= target) {
            ans = min(ans, right-left+1);
            sum -= nums[left++];
        }
    }
    return ans == INT_MAX ? 0 : ans;
}
```

### Dry Run
`target=7, nums=[2,3,1,2,4,3]`
Smallest window: `[4,3]` → length = 2

---

## 3. Longest Substring with K Distinct Characters (Medium)

Let's use this example:

### Dry Run

Let's dry run the algorithm for:

```
s = "eceba"
k = 2
```

**Initial State**  
- `mp = {}` (empty map)  
- `left = 0`  
- `ans = 0`  

**Step-by-Step Execution**

1. `right = 0`, `s[right] = 'e'`  
    - Add 'e' to `mp`: `mp = {'e': 1}`  
    - `mp.size() = 1` (≤ 2), so skip while loop.  
    - Update `ans = max(0, 0-0+1) = 1`

2. `right = 1`, `s[right] = 'c'`  
    - Add 'c': `mp = {'e': 1, 'c': 1}`  
    - `mp.size() = 2` (≤ 2), skip while loop.  
    - Update `ans = max(1, 1-0+1) = 2`

3. `right = 2`, `s[right] = 'e'`  
    - Increment 'e': `mp = {'e': 2, 'c': 1}`  
    - `mp.size() = 2` (≤ 2), skip while loop.  
    - Update `ans = max(2, 2-0+1) = 3`

4. `right = 3`, `s[right] = 'b'`  
    - Add 'b': `mp = {'e': 2, 'c': 1, 'b': 1}`  
    - `mp.size() = 3` (> 2), enter while loop:  
      - Decrement 'e': `mp = {'e': 1, 'c': 1, 'b': 1}`; `left = 1`  
      - Still 3 keys, decrement 'c': `mp = {'e': 1, 'c': 0, 'b': 1}`; erase 'c'; `mp = {'e': 1, 'b': 1}`; `left = 2`  
    - Now `mp.size() = 2`  
    - Update `ans = max(3, 3-2+1) = 2` (no change)

5. `right = 4`, `s[right] = 'a'`  
    - Add 'a': `mp = {'e': 1, 'b': 1, 'a': 1}`  
    - `mp.size() = 3` (> 2), enter while loop:  
      - Decrement 'e': `mp = {'e': 0, 'b': 1, 'a': 1}`; erase 'e'; `mp = {'b': 1, 'a': 1}`; `left = 3`  
    - Now `mp.size() = 2`  
    - Update `ans = max(3, 4-3+1) = 2` (no change)

**Final Result**  
The longest substring with at most 2 distinct characters is `"ece"` (length 3).  
The function returns `3`.
Update ans = max(1, 1-0+1) = 2
3. right = 2, s[right] = 'e'
Increment 'e': mp = {'e': 2, 'c': 1}
mp.size() = 2 (≤ 2), skip while loop.
Update ans = max(2, 2-0+1) = 3
4. right = 3, s[right] = 'b'
Add 'b': mp = {'e': 2, 'c': 1, 'b': 1}
mp.size() = 3 (> 2), enter while loop:
Decrement 'e': mp = {'e': 1, 'c': 1, 'b': 1}; left = 1
Still 3 keys, decrement 'c': mp = {'e': 1, 'c': 0, 'b': 1}; erase 'c'; mp = {'e': 1, 'b': 1}; left = 2
Now mp.size() = 2
Update ans = max(3, 3-2+1) = 2 (no change)
5. right = 4, s[right] = 'a'
Add 'a': mp = {'e': 1, 'b': 1, 'a': 1}
mp.size() = 3 (> 2), enter while loop:
Decrement 'e': mp = {'e': 0, 'b': 1, 'a': 1}; erase 'e'; mp = {'b': 1, 'a': 1}; left = 3
Now mp.size() = 2
Update ans = max(3, 4-3+1) = 2 (no change)
Final Result
The longest substring with at most 2 distinct characters is "ece" (length 3).
The function returns 3.
Key Points
The sliding window expands with right, and contracts with left when more than k distinct characters are present.
The map tracks character counts to know when to remove a character from the window.

### C++ Code
```cpp
int longestKDistinct(string s, int k) {
    unordered_map<char,int> mp;
    int left=0, ans=0;
    for(int right=0; right<s.size(); right++){
        mp[s[right]]++;
        while(mp.size() > k){
            if(--mp[s[left]] == 0) mp.erase(s[left]);
            left++;
        }
        ans = max(ans, right-left+1);
    }
    return ans;
}
```

### Dry Run
`s = "araaci", k = 2`
Longest substring = `"araa"` → length 4

---

## 4. Fruits into Baskets (Medium)
Same as longest substring with at most **2 distinct characters**.

---
## 5. Longest Substring with Same Letters after Replacement (Hard)

### Dry Run

Let's dry run for `s = "AABABBA", k = 1`:

- Initialize: `freq = [0]*26`, `left = 0`, `maxFreq = 0`, `ans = 0`

| right | s[right] | freq (main letter) | maxFreq | Window Size | (Window Size - maxFreq) | Action                | ans |
|-------|----------|-------------------|---------|-------------|------------------------|-----------------------|-----|
| 0     | A        | A:1               | 1       | 1           | 0                      | Expand                | 1   |
| 1     | A        | A:2               | 2       | 2           | 0                      | Expand                | 2   |
| 2     | B        | B:1, A:2          | 2       | 3           | 1                      | Expand                | 3   |
| 3     | A        | A:3, B:1          | 3       | 4           | 1                      | Expand                | 4   |
| 4     | B        | A:3, B:2          | 3       | 5           | 2                      | Shrink left to 1      | 4   |
| 5     | B        | A:2, B:3          | 3       | 5           | 2                      | Shrink left to 2      | 4   |
| 6     | A        | A:2, B:3          | 3       | 5           | 2                      | Shrink left to 3      | 4   |

- At each step, if `(right - left + 1) - maxFreq > k`, move `left` forward and update frequencies.
- The answer is the maximum window size where at most `k` replacements are needed.

**Final Answer:** `4` (substring `"AABA"` or `"ABBA"`)


### C++ Code
```cpp
int characterReplacement(string s, int k) {
    vector<int> freq(26,0);
    int left=0, maxFreq=0, ans=0;
    for(int right=0; right<s.size(); right++){
        freq[s[right]-'A']++;
        maxFreq = max(maxFreq, freq[s[right]-'A']);
        while((right-left+1) - maxFreq > k){
            freq[s[left]-'A']--;
            left++;
        }
        ans = max(ans, right-left+1);
    }
    return ans;
}
```

### Dry Run
`s = "AABABBA", k = 1`
Answer = 4

---
## 6. Longest Subarray with Ones after Replacement (Hard)

Given a binary array, find the length of the longest subarray containing only 1s after replacing at most `k` 0s with 1s.

### C++ Code
```cpp
int longestOnes(vector<int>& nums, int k) {
    int left = 0, zeros = 0, ans = 0;
    for (int right = 0; right < nums.size(); right++) {
        if (nums[right] == 0) zeros++;
        while (zeros > k) {
            if (nums[left++] == 0) zeros--;
        }
        ans = max(ans, right - left + 1);
    }
    return ans;
}
```

### Dry Run

`nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2`

| right | nums[right] | zeros | left | Window         | Action                | ans |
|-------|-------------|-------|------|----------------|-----------------------|-----|
| 0     | 1           | 0     | 0    | [1]            | Expand                | 1   |
| 1     | 1           | 0     | 0    | [1,1]          | Expand                | 2   |
| 2     | 1           | 0     | 0    | [1,1,1]        | Expand                | 3   |
| 3     | 0           | 1     | 0    | [1,1,1,0]      | Expand                | 4   |
| 4     | 0           | 2     | 0    | [1,1,1,0,0]    | Expand                | 5   |
| 5     | 0           | 3     | 0    | [1,1,1,0,0,0]  | Shrink left to 1      | 5   |
|       |             | 2     | 1    | [1,1,0,0,0]    | Shrink left to 2      |     |
|       |             | 2     | 2    | [1,0,0,0]      |                       |     |
| 6     | 1           | 2     | 2    | [1,0,0,0,1]    | Expand                | 5   |
| 7     | 1           | 2     | 2    | [1,0,0,0,1,1]  | Expand                | 6   |
| 8     | 1           | 2     | 2    | [1,0,0,0,1,1,1]| Expand                | 7   |
| 9     | 1           | 2     | 2    | [1,0,0,0,1,1,1,1]| Expand              | 8   |
| 10    | 0           | 3     | 2    | [1,0,0,0,1,1,1,1,0]| Shrink left to 3  | 8   |
|       |             | 2     | 3    | [0,0,0,1,1,1,1,0]|                      |     |
|       |             | 2     | 4    | [0,0,1,1,1,1,0]|                       |     |

**Final Answer:** `8` (subarray `[1,1,0,0,1,1,1,1]`)

---
Same logic as above but applied to binary arrays.


---

## 7. Permutation in a String (Hard)


### C++ Code
```cpp
bool checkInclusion(string p, string s) {
    vector<int> cnt(26,0);
    for(char c:p) cnt[c-'a']++;
    int left=0, need=p.size();
    for(int right=0; right<s.size(); right++){
        if(cnt[s[right]-'a']-- > 0) need--;
        if(need==0) return true;
        if(right-left+1 == p.size()){
            if(cnt[s[left]-'a']++ >= 0) need++;
            left++;
        }
    }
    return false;
}
```
Purpose
This function checks if any permutation of string p exists as a substring in string s.
It uses a sliding window approach with a frequency counter.

Step-by-Step Explanation
1. Initialize Frequency Counter
cnt is a vector of size 26 (for each lowercase letter).
For each character in p, increment its count in cnt.

2. Set Up Sliding Window
left is the start index of the window.
need is the number of characters we still need to match.
3. Iterate Over s with Right Pointer

```cpp
for(int right=0; right<s.size(); right++){
    if(cnt[s[right]-'a']-- > 0) need--;
    if(need==0) return true;
    if(right-left+1 == p.size()){
        if(cnt[s[left]-'a']++ >= 0) need++;
        left++;
    }
}
```
For each character at right:
Decrement its count in cnt.
If the count was positive, it means this character was needed, so decrement need.
If need becomes 0, all characters matched: return true.
If the window size equals p.size(), slide the window:
Increment the count for the character at left (since it’s leaving the window).
If the count was non-negative, increment need (we now need this character again).
Move left forward.
4. Return False if No Permutation Found

```cpp
return false;
```

Dry Run Example
Suppose:

p = "ab"
s = "eidbaooo"
Initialization
cnt = [1,1,0,...,0] (1 for 'a', 1 for 'b')
left = 0
need = 2
Iteration

right	s[right]	cnt after --	need	Window	Action
0	'e'	-1	2	e	Not needed, move on
1	'i'	-1	2	ei	Not needed, move on
2	'd'	-1	2	eid	Not needed, move on
3	'b'	0	1	eidb	Needed, need--
4	'a'	0	0	eidba	Needed, need--, found
At right=4, need becomes 0, so the function returns true.

Key Points / Gotchas
The cnt vector tracks how many of each character are still needed.
The window size is always the length of p.
The need variable is crucial: it tells us when all required characters are matched.
The code is efficient: O(N) time, O(1) space.

---

## 8. Smallest Window Containing Substring (Hard)
Classic sliding window with frequency map.

Example:
```
S = ADOBECODEBANC
T = ABC
Answer = BANC
```

---

## 9. Counting Subarrays with Product Less than Target (Hard)

### C++ Code
```cpp
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if(k<=1) return 0;
    int left=0;
    long prod=1;
    int count=0;
    for(int right=0; right<nums.size(); right++){
        prod *= nums[right];
        while(prod >= k) prod /= nums[left++];
        count += right-left+1;
    }
    return count;
}
```

### Dry Run
`nums=[10,5,2,6], k=100` → Output = 8

---

## ✅ Summary
- Sliding Window = O(n) time
- Expand with `right`, shrink with `left`
- Best for substring/subarray problems
