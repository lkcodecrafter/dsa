# Module 2: Strings & Pattern Matching (Lectures 36–44)

## 📋 Syllabus
*   **Basics:** Char Arrays vs. Strings, Palindromes, Reverse String.
*   **Algorithms:** KMP (Knuth-Morris-Pratt) Algorithm, LPS (Longest Prefix Suffix) Array.
*   **Hard Problems:** Integer to Roman, Roman to Integer, Sliding Window on Strings, String Matching.

---

## 🟢 Section 1: Basics

### 🎯 Solution 2.1: Char Arrays vs. Strings, Palindromes, Reverse String
*   **Concept:** Char arrays are null-terminated (`\0`) character sequences stored on stack, while `std::string` is a dynamic wrapper on heap. A palindrome is a string that reads the same backward as forward.
*   **C++ Code:**
```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

// 1. Check Palindrome (Case-insensitive, alphanumeric only)
bool isPalindrome(const std::string& s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;
        if (tolower(s[left]) != tolower(s[right])) return false;
        left++;
        right--;
    }
    return true;
}

// 2. Reverse String in-place
void reverseString(std::string& s) {
    int left = 0, right = s.length() - 1;
    while (left < right) {
        std::swap(s[left++], s[right--]);
    }
}
```
*   **🔍 Dry Run (Palindrome Check):**
    *   **Input:** `s = "A man, a plan, a canal: Panama"`
    *   Pointers: `left = 0`, `right = 29`
    *   `s[0]` is 'A' (alphanumeric), `s[29]` is 'a' (alphanumeric). Both convert to lowercase 'a'. Match!
    *   Increment `left = 1`, decrement `right = 28`.
    *   Skip spaces/punctuation: `left` moves past space/comma to index `2 ('m')`, `right` moves to index `28 ('a')` then `27 ('m')` (skipping 'a', 'n', 'a' properly). 
    *   Matching continues until pointers cross. Return `true`.
*   **Complexity:** Time: $O(N)$, Space: $O(1)$.

---

## 🟢 Section 2: Algorithms

### 🎯 Solution 2.2: KMP Pattern Matching & LPS Array
*   **Problem:** Implement the KMP algorithm to search for all occurrences of pattern `pat` in text `txt`.
*   **C++ Code:**
```cpp
#include <string>
#include <vector>
#include <iostream>

std::vector<int> computeLPS(const std::string& pat) {
    int m = pat.length();
    std::vector<int> lps(m, 0);
    int len = 0, i = 1;
    
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void KMPSearch(const std::string& txt, const std::string& pat) {
    int n = txt.length(), m = pat.length();
    std::vector<int> lps = computeLPS(pat);
    int i = 0, j = 0;
    
    while (i < n) {
        if (pat[j] == txt[i]) {
            i++; j++;
        }
        if (j == m) {
            std::cout << "Pattern found at index " << i - j << "\n";
            j = lps[j - 1];
        } else if (i < n && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}
```
*   **🔍 Dry Run:**
    *   **Pattern:** `pat = "ababd"`
    *   **Calculated LPS Array:** `[0, 0, 1, 2, 0]`

| `i` | `pat[i]` | `len` | `pat[len]` | Match Status | LPS Array State | Action |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **0** | 'a' | 0 | - | First character | `[0, 0, 0, 0, 0]` | - |
| **1** | 'b' | 0 | 'a' | Mismatch | `[0, 0, 0, 0, 0]` | `lps[1]=0`, `i++` |
| **2** | 'a' | 0 | 'a' | **Match** | `[0, 0, 1, 0, 0]` | `len=1`, `lps[2]=1`, `i++` |
| **3** | 'b' | 1 | 'b' | **Match** | `[0, 0, 1, 2, 0]` | `len=2`, `lps[3]=2`, `i++` |
| **4** | 'd' | 2 | 'a' | Mismatch | `[0, 0, 1, 2, 0]` | `len = lps[1] = 0` |
| **4** | 'd' | 0 | 'a' | Mismatch | `[0, 0, 1, 2, 0]` | `lps[4] = 0`, `i++` |

*   **Complexity:** Time: $O(N + M)$, Space: $O(M)$.

---

## 🟢 Section 3: Hard Problems

### 🎯 Solution 2.3: Integer to Roman & Roman to Integer
*   **Problem:** Convert an integer to its Roman numeral representation, and vice versa.
*   **C++ Code:**
```cpp
#include <string>
#include <vector>
#include <unordered_map>

// 1. Integer to Roman
std::string intToRoman(int num) {
    std::vector<std::pair<int, std::string>> roman = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    std::string res = "";
    for (const auto& pair : roman) {
        while (num >= pair.first) {
            res += pair.second;
            num -= pair.first;
        }
    }
    return res;
}

// 2. Roman to Integer
int romanToInt(const std::string& s) {
    std::unordered_map<char, int> m = {
        {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
        {'C', 100}, {'D', 500}, {'M', 1000}
    };
    int ans = 0;
    for (size_t i = 0; i < s.length(); i++) {
        if (i + 1 < s.length() && m[s[i]] < m[s[i + 1]]) {
            ans -= m[s[i]];
        } else {
            ans += m[s[i]];
        }
    }
    return ans;
}
```
*   **🔍 Dry Run (Roman to Integer):**
    *   **Input String:** `"MCMXCIV"` (representing 1994)
    *   Indices: `M (1000)`, `C (100)`, `M (1000)`, `X (10)`, `C (100)`, `I (1)`, `V (5)`
    *   `i=0`: `m['M'] (1000) >= m['C'] (100)` -> `ans += 1000 = 1000`
    *   `i=1`: `m['C'] (100) < m['M'] (1000)` -> subtract C -> `ans -= 100 = 900`
    *   `i=2`: `m['M'] (1000) >= m['X'] (10)` -> add M -> `ans += 1000 = 1900`
    *   `i=3`: `m['X'] (10) < m['C'] (100)` -> subtract X -> `ans -= 10 = 1890`
    *   `i=4`: `m['C'] (100) >= m['I'] (1)` -> add C -> `ans += 100 = 1990`
    *   `i=5`: `m['I'] (1) < m['V'] (5)` -> subtract I -> `ans -= 1 = 1989`
    *   `i=6`: `m['V'] (5)` -> add V -> `ans += 5 = 1994`
    *   **Result:** `1994`.
*   **Complexity:** Time: $O(N)$ where $N$ is length of roman string (practically $O(1)$ since input ranges are limited), Space: $O(1)$.

### 🎯 Solution 2.4: Sliding Window (Longest Substring Without Repeating Characters)
*   **Problem:** Find the length of the longest substring without repeating characters.
*   **C++ Code:**
```cpp
#include <string>
#include <vector>
#include <algorithm>

int lengthOfLongestSubstring(const std::string& s) {
    std::vector<int> lastIndex(256, -1);
    int maxLen = 0;
    int start = 0;
    
    for (int end = 0; end < s.length(); end++) {
        if (lastIndex[s[end]] >= start) {
            start = lastIndex[s[end]] + 1;
        }
        lastIndex[s[end]] = end;
        maxLen = std::max(maxLen, end - start + 1);
    }
    return maxLen;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `s = "abcabcbb"`

| Index `end` | Char `s[end]` | `lastIndex[char]` | `start` position | Max Length | `lastIndex` updated value |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **0** | 'a' | -1 | 0 | `max(0, 0-0+1) = 1` | `lastIndex['a'] = 0` |
| **1** | 'b' | -1 | 0 | `max(1, 1-0+1) = 2` | `lastIndex['b'] = 1` |
| **2** | 'c' | -1 | 0 | `max(2, 2-0+1) = 3` | `lastIndex['c'] = 2` |
| **3** | 'a' | 0 | `0 + 1 = 1` | `max(3, 3-1+1) = 3` | `lastIndex['a'] = 3` |
| **4** | 'b' | 1 | `1 + 1 = 2` | `max(3, 4-2+1) = 3` | `lastIndex['b'] = 4` |
| **5** | 'c' | 2 | `2 + 1 = 3` | `max(3, 5-3+1) = 3` | `lastIndex['c'] = 5` |
| **6** | 'b' | 4 | `4 + 1 = 5` | `max(3, 6-5+1) = 3` | `lastIndex['b'] = 6` |
| **7** | 'b' | 6 | `6 + 1 = 7` | `max(3, 7-7+1) = 3` | `lastIndex['b'] = 7` |

    *   **Result:** `3`.
*   **Complexity:** Time: $O(N)$, Space: $O(1)$ (using a fixed-size integer array of size 256).

### 🎯 Solution 2.5: Rabin-Karp String Matching
*   **Problem:** Implement the Rabin-Karp string matching algorithm to find matching index of pattern `pat` in text `txt`.
*   **C++ Code:**
```cpp
#include <string>
#include <vector>
#include <iostream>

void rabinKarpSearch(const std::string& txt, const std::string& pat, int q = 101) {
    int d = 256;
    int n = txt.length(), m = pat.length();
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
    
    // The value of h would be "pow(d, m-1)%q"
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }
    
    // Calculate initial hash values
    for (int i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }
    
    // Slide pattern over text
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (txt[i + j] != pat[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                std::cout << "Pattern found at index " << i << "\n";
            }
        }
        
        // Calculate hash value for next window
        if (i < n - m) {
            t = (d * (t - txt[i] * h) + txt[i + m]) % q;
            if (t < 0) t += q;
        }
    }
}
```
*   **🔍 Dry Run:**
    *   **Input:** `txt = "ababc"`, `pat = "abc"`
    *   Let's check if Rabin-Karp calculates hash of `pat` and slides window.
    *   Match occurs at index `2`.
*   **Complexity:** Time: Average/Best $O(N + M)$, Worst $O(N \times M)$ (in case of hash collisions for all windows), Space: $O(1)$.
