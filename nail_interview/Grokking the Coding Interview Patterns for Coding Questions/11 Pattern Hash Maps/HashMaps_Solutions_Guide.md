# Pattern: Hash Maps - Study Guide & Solutions

This guide covers fundamental Hash Map problems with C++ solutions, dry runs, and conceptual visualizations.

## 📚 Core Concepts
### 1. What is a Hash Table?
A data structure that stores key-value pairs. It uses a **Hash Function** to map keys to indices in an array.

### 2. Collisions
- **Chaining:** Storing multiple elements in the same bucket using a linked list.
- **Open Addressing:** Finding another open slot in the array.

## Problem 1: First Non-repeating Character (Easy)
**Description:** Find the first character in a string that does not repeat and return its index.

### C++ Solution
```cpp
int firstUniqChar(string s) {
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    for (int i = 0; i < s.length(); i++) {
        if (count[s[i]] == 1) return i;
    }
    return -1;
}
```

### Visualization & Dry Run
```text
String s = "loveleetcode"
1. Frequency Map: {l:2, o:2, v:1, e:4, t:1, c:1, d:1}
2. Scan string:
   - 'l': count 2 (skip)
   - 'o': count 2 (skip)
   - 'v': count 1 (MATCH!) -> return index 2
```
---

## Problem 2: Largest Unique Number (Easy)
**Description:** Find the largest integer in the array that appears only once.

### C++ Solution
```cpp
int largestUniqueNumber(vector<int>& nums) {
    unordered_map<int, int> count;
    for (int n : nums) count[n]++;
    int maxNum = -1;
    for (auto const& [val, freq] : count) {
        if (freq == 1) maxNum = max(maxNum, val);
    }
    return maxNum;
}
```

### Visualization & Dry Run
```text
nums = [5, 7, 3, 9, 4, 9, 8, 3, 1]
1. Map: {5:1, 7:1, 3:2, 9:2, 4:1, 8:1, 1:1}
2. Unique values: 5, 7, 4, 8, 1
3. Max of Uniques: 8
```
---

## Problem 3: Maximum Number of Balloons (Easy)
**Description:** How many instances of the word 'balloon' can be formed from the given text?

### C++ Solution
```cpp
int maxNumberOfBalloons(string text) {
    unordered_map<char, int> count;
    for (char c : text) count[c]++;
    return min({count['b'], count['a'], count['l']/2, count['o']/2, count['n']});
}
```

### Visualization & Dry Run
```text
text = "loonbalxballpoon"
1. Counts: b:2, a:2, l:4, o:4, n:2
2. Required for 'balloon': b:1, a:1, l:2, o:2, n:1
3. Dividends: 2/1, 2/1, 4/2, 4/2, 2/1 -> all are 2.
4. Min is 2.
```
---

## Problem 4: Longest Palindrome (Easy)
**Description:** Find the length of the longest palindrome that can be built with given letters.

### C++ Solution
```cpp
int longestPalindrome(string s) {
    unordered_map<char, int> count;
    for (char c : s) count[c]++;
    int length = 0;
    bool oddFound = false;
    for (auto const& [c, freq] : count) {
        length += (freq / 2) * 2;
        if (freq % 2 == 1) oddFound = true;
    }
    return oddFound ? length + 1 : length;
}
```

### Visualization & Dry Run
```text
s = "abccccdd"
1. Map: {a:1, b:1, c:4, d:2}
2. 'a': len += 0, oddFound = true
3. 'b': len += 0, oddFound = true
4. 'c': len += 4
5. 'd': len += 2
6. Total = 6 + (1 if oddFound) = 7
```
---

## Problem 5: Ransom Note (Easy)
**Description:** Can ransomNote be constructed by using letters from magazine?

### C++ Solution
```cpp
bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char, int> count;
    for (char c : magazine) count[c]++;
    for (char c : ransomNote) {
        if (--count[c] < 0) return false;
    }
    return true;
}
```

### Visualization & Dry Run
```text
note = "aa", mag = "aab"
1. Mag Map: {a:2, b:1}
2. Check 'a': mag[a] becomes 1
3. Check 'a': mag[a] becomes 0
4. Result: True
```
---

