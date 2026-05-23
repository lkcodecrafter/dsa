#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

// https://www.youtube.com/watch?v=n_kL8BkURVA

class Solution
{
public:
    int t[1001][1001];
    bool solve(string &s, int l, int r)
    {
        if (l >= r)
            return 1;

        if (t[l][r] != -1)
        {
            return t[l][r];
        }

        if (s[l] == s[r])
        {
            return t[l][r] = solve(s, l + 1, r - 1);
        }

        return t[l][r] = false;
    }

    string longestPalindrome(string s)
    {
        int n = s.length();

        int maxlen = INT_MIN;
        int startingIndex = 0;

        memset(t, -1, sizeof(t));

        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {

                if (solve(s, i, j))
                {
                    if (j - i + 1 > maxlen)
                    {
                        startingIndex = i;
                        maxlen = j - i + 1;
                    }
                }
            }
        }

        return s.substr(startingIndex, maxlen);
    }
};

/*


📝 Dry Run Example

Input:


s = "babad"
Step-by-step:
Initialize longest_palindrome = "b"

Fill diagonal of DP table (memo[i][i] = true)

Expand:

"bab" found → update longest_palindrome = "bab"

"aba" found → update longest_palindrome = "aba" (same length as "bab")

No longer palindrome found.

Output:
Code
"bab" or "aba"
📊 Visualization of DP Table for "babad"
Code
    b   a   b   a   d
b [ T   F   T   F   F ]
a [     T   F   T   F ]
b [         T   F   F ]
a [             T   F ]
d [                 T ]
T = True means substring is palindrome.

Notice "bab" (memo[2][0] = True) and "aba" (memo[3][1] = True).



---


User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily?

GitHub Copilot: I'll read the code and help you understand it with explanations and visualizations.

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week6/5.%20Longest%20Palindromic%20Substring.cpp)

Perfect! I can see the code. This is a **Longest Palindromic Substring** problem solved using **Dynamic Programming**. Let me explain it with detailed visualizations and a dry run.

## 📚 Algorithm Overview

This solution uses a **2D DP table** where `memo[i][j]` represents whether the substring from index `j` to `i` is a palindrome.

### Key Idea:
1. A single character is always a palindrome
2. Two adjacent characters are palindromes if they match
3. A longer substring is a palindrome if its characters match at both ends AND the inner substring is also a palindrome

---

## 🎯 Dry Run with Example: `"babad"`

### Step 1: Initialize
```
longest_palindrome = "b" (first character)
n = 5
```

### Step 2: Mark all single characters as palindromes
```
memo[0][0] = true (b)
memo[1][1] = true (a)
memo[2][2] = true (b)
memo[3][3] = true (a)
memo[4][4] = true (d)
```

### Step 3: Build DP Table by Expanding
```
Indices:  0   1   2   3   4
Chars:    b   a   b   a   d

         0   1   2   3   4
    0: [ T   F   T   F   F ]   (b...b)
    1: [     T   F   T   F ]
    2: [         T   F   F ]
    3: [             T   F ]
    4: [                 T ]
```

### Detailed Expansion Process:

**i=0 (char 'b'): j goes from -1 downward** → no iterations

**i=1 (char 'a'): j=0**
- s[1]='a' ≠ s[0]='b' → skip

**i=2 (char 'b'): j=1, j=0**
- j=1: s[2]='b' ≠ s[1]='a' → skip
- j=0: s[2]='b' == s[0]='b' ✓
  - i-j+1=3 (middle char at index 1)
  - Check memo[1][1]=true ✓ → **"bab" is palindrome!**
  - Update longest_palindrome = "bab" (length 3)

**i=3 (char 'a'): j=2, j=1, j=0**
- j=2: s[3]='a' ≠ s[2]='b' → skip
- j=1: s[3]='a' == s[1]='a' ✓
  - Check memo[2][2]=true ✓ → **"aba" is palindrome!**
  - Length = 3 (same as current, no update needed)
- j=0: s[3]='a' ≠ s[0]='b' → skip

**i=4 (char 'd'): j=3, j=2, j=1, j=0**
- All characters don't match 'd' → skip

### Final Output: **`"bab"`** (or `"aba"`, both length 3)

---

## 📊 Visual DP Table Building

```
Index:     0(b)  1(a)  2(b)  3(a)  4(d)

After diagonals:
           [T]   [ ]   [ ]   [ ]   [ ]
           [ ]   [T]   [ ]   [ ]   [ ]
           [ ]   [ ]   [T]   [ ]   [ ]
           [ ]   [ ]   [ ]   [T]   [ ]
           [ ]   [ ]   [ ]   [ ]   [T]

After checking pairs (i, j-1):
           [T]   [F]   [?]   [?]   [F]
           [ ]   [T]   [F]   [?]   [F]
           [ ]   [ ]   [T]   [F]   [F]
           [ ]   [ ]   [ ]   [T]   [F]
           [ ]   [ ]   [ ]   [ ]   [T]

Final table:
           [T]   [F]   [T✓] [F]   [F]    ← memo[2][0]="bab"
           [ ]   [T]   [F]   [T✓] [F]    ← memo[3][1]="aba"
           [ ]   [ ]   [T]   [F]   [F]
           [ ]   [ ]   [ ]   [T]   [F]
           [ ]   [ ]   [ ]   [ ]   [T]
```

---

## ⏱️ Complexity Analysis
- **Time**: O(n²) - two nested loops
- **Space**: O(n²) - DP table

## 💡 Why This Works
The algorithm avoids redundant checking by storing previous results. When we find matching characters at both ends, we only need to verify the inner substring was already marked as a palindrome.

Does this explanation help? Would you like me to walk through another example or clarify any specific part?
*/