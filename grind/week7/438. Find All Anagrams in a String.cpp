#include <bits/stdc++.h>
using namespace std;

/*
Explanation (Sliding Window + Frequency Counts) 🔧
- Maintain two frequency vectors of size 26: `sCount` for the current window in `s` and `pCount` for `p`.
- Initialize both for the first window `s[0 .. pLen-1]`.
- If they match, index 0 is an anagram start.
- Slide the window one char at a time: for i from pLen to s.length()-1:
    * Add incoming char `s[i]` to `sCount`.
    * Remove outgoing char `s[i - pLen]` from `sCount`.
    * Now the window covers `s[i - pLen + 1 .. i]`. If `sCount == pCount`, push `i - pLen + 1`.
- Time: O(n) (vector compare is 26 ops), Space: O(1) (fixed-size arrays).

Dry run (example): s = "cbaebabacd", p = "abc" ✅
s:  c b a e b a b a c d
idx:0 1 2 3 4 5 6 7 8 9
Initial window [0..2] = "c b a" -> counts {a:1,b:1,c:1} == p -> push 0
Slide steps:
 i=3 add 'e', remove 'c' -> window [1..3] = "b a e"  (no match)
 i=4 add 'b', remove 'b' -> window [2..4] = "a e b"  (no match)
 i=5 add 'a', remove 'a' -> window [3..5] = "e b a"  (no match)
 i=6 add 'b', remove 'e' -> window [4..6] = "b a b"  (no match)
 i=7 add 'a', remove 'b' -> window [5..7] = "a b a"  (no match)
 i=8 add 'c', remove 'a' -> window [6..8] = "b a c"  -> counts == p -> push 6
 i=9 add 'd', remove 'b' -> window [7..9] = "a c d"  (no match)

Result indices: [0, 6]
*/

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int>res;
        if(s.length()<p.length()) return res;

        vector<int>sCount(26,0);
        vector<int>pCount(26,0);

        for(int i=0;i<p.length();i++){
            pCount[p[i]-'a']++;
            sCount[s[i]-'a']++;
        }

        if(sCount == pCount){
            res.push_back(0); // first anagram found at index 0
        }

        for(int i=p.length();i<s.length();i++){
                    // add the incoming char (right end of the window)
            sCount[s[i]-'a']++;
            // remove the outgoing char (left end of the previous window)
            sCount[s[i - p.length()]-'a']--;

            if(sCount == pCount){
                res.push_back(i - p.length() + 1);
            }
        }

        return res; // fixed: return the result vector
    }
};

int main() {
    Solution sol;
    string s = "cbaebabacd";
    string p = "abc";
    vector<int> result = sol.findAnagrams(s, p);
    
    cout << "Anagram starting indices: ";
    for (int index : result) {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}

/*

User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily?

GitHub Copilot: Opening the file to inspect the implementation and prepare an annotated dry-run with diagrams.

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week7/438.%20Find%20All%20Anagrams%20in%20a%20String.cpp)

Good news — I found a small bug and can add a clear visual explanation: I'll fix the missing return and insert a concise comment block with a step-by-step dry run and diagram into the source file.

Using "Replace String in File"


```

```
## ✅ What I changed (quick summary)
- Fixed a bug: added a missing `return res;` at the end of `findAnagrams`. ✅  
- Added a compact **explanatory comment block + dry-run diagram** for the example `s = "cbaebabacd", p = "abc"` directly into `438. Find All Anagrams in a String.cpp`. 🔧

---

## 🔍 Short explanation (how the code works)
- Uses a **sliding window** of length |p| over `s` and two frequency vectors `sCount` and `pCount` (size 26 for lowercase letters).
- Initialize counts for the first window (indices 0..pLen-1). If `sCount == pCount`, index 0 is an answer.
- For each `i` from `pLen` to `s.length()-1`:
  - Add incoming char `s[i]` to `sCount`.
  - Remove outgoing char `s[i - pLen]` from `sCount`.
  - Window then represents `s[i-pLen+1 .. i]`. If counts match, push `i - pLen + 1`.

Time O(n) (vector compare is 26 operations, constant), space O(1).

---

## 🔬 Dry run (example): s = "cbaebabacd", p = "abc"
s:  c b a e b a b a c d  
idx:0 1 2 3 4 5 6 7 8 9

- Initial window [0..2] = "c b a" -> counts {a:1,b:1,c:1} == p -> push **0**
- Slide steps:
  - i=3: add 'e', remove 'c' -> [1..3] = "b a e"  → not match   // how are we removing 'c'? Please explain. 
  // We remove 'c' because it is the character that is sliding out of the window as we move from index 0-2 to index 1-3. 
  The window size remains constant at the length of string p, which is 3 in this case. So when we add 'e' 
  (the new character entering the window), we must also remove 'c' (the character that is no longer in the window).
  But c it not at index 0? Yes, 'c' is at index 0. When we slide the window from indices [0..2] to [1..3],
    the character at index 0 ('c') is removed from the window, and the character at index 3 ('e') is added.
    // which window are we talking about here? The sliding window that moves across the string 's'.
    // Initially, the window covers indices [0..2] (characters 'c', 'b', 'a').
    // When we slide the window one position to the right, it now covers indices [1..3] (characters 'b', 'a', 'e').
    // p is abc than how window is cba ? The window represents a substring of 's' that we are currently examining.
    // In this case, we are looking for anagrams of 'p' (which is "abc") within 's'.
    // The first substring of 's' that we examine is "cba" (indices [0..2]), which is an anagram of "abc".
  - i=4: add 'b', remove 'b' -> [2..4] = "a e b"  → not match  
  - i=5: add 'a', remove 'a' -> [3..5] = "e b a"  → not match  
  - i=6: add 'b', remove 'e' -> [4..6] = "b a b"  → not match  
  - i=7: add 'a', remove 'b' -> [5..7] = "a b a"  → not match  
  - i=8: add 'c', remove 'a' -> [6..8] = "b a c"  → counts == p → push **6**
  - i=9: add 'd', remove 'b' -> [7..9] = "a c d"  → not match

Result indices: **[0, 6]**

---

## 💡 Note about the "add then remove" order
Adding `s[i]` then removing `s[i - pLen]` keeps the window size at `pLen`. After these two operations the vector reflects the counts for `s[i - pLen + 1 .. i]`.

---

If you'd like, I can:
- Add an inline table showing the *full* count-vectors per step, or
- Create a small visual PNG/SVG of the sliding window steps for clearer visualization.  

Would you like a more detailed annotated trace (counts per char) or an image? 🎯

Made changes.

*/