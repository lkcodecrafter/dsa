# Warmup Problems (17 Lessons)

## 📌 Why Warmup?

Warmup questions build your fundamentals.\
They help you understand patterns, improve logic, and prepare for harder
problems.

------------------------------------------------------------------------

## 1. **Contains Duplicate (Easy)**

**Problem:** Given an integer array, return true if any value appears at
least twice.\
**Idea:** Use a set to track seen numbers.

**C++ Code:**

``` cpp
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> s;
    for(int x : nums){
        if(s.count(x)) return true;
        s.insert(x);
    }
    return false;
}
```

------------------------------------------------------------------------

## 2. **Pangram (Easy)**

**Problem:** Check whether a sentence contains all 26 English letters.\
**Idea:** Count letters using a boolean array.

**C++ Code:**

``` cpp
bool checkIfPangram(string s) {
    vector<int> a(26,0);
    for(char c:s) a[c-'a']=1;
    for(int x:a) if(x==0) return false;
    return true;
}


Step-by-step walkthrough

Suppose:

string s = "bad";
vector<int> a(26, 0);

Initially:

a = [0,0,0,0,0,...]
Character 'b'
'b' - 'a' = 1
a[1] = 1
a = [0,1,0,0,0,...]
Character 'a'
'a' - 'a' = 0
a[0] = 1
a = [1,1,0,0,0,...]
Character 'd'
'd' - 'a' = 3
a[3] = 1
a = [1,1,0,1,0,...]

Now the array tells us which letters have been seen.

```

------------------------------------------------------------------------

## 3. **Reverse Vowels (Easy)**

**Idea:** Two-pointer swap on vowels.

**C++ Code:**

``` cpp
bool isVowel(char c){
    return string("aeiouAEIOU").find(c) != string::npos; // mean
}
string reverseVowels(string s) {
    int l=0, r=s.size()-1;
    while(l<r){
        if(!isVowel(s[l])) l++;
        else if(!isVowel(s[r])) r--;
        else swap(s[l++], s[r--]);
    }
    return s;
}


Let's break it down piece by piece.

1. Understanding isVowel()
bool isVowel(char c){
    return string("aeiouAEIOU").find(c) != string::npos;
}
What is string("aeiouAEIOU")?

It creates a string containing all vowels:

"aeiouAEIOU"
What does .find(c) do?

It searches for character c in the string.

Example:

string vowels = "aeiouAEIOU";

vowels.find('a');  // returns 0
vowels.find('o');  // returns 4
vowels.find('E');  // returns 6
vowels.find('x');  // not found

When found, it returns the index.

What is string::npos?

npos means "not found".

Example:

vowels.find('x')

returns

string::npos

which is a very large number used to indicate failure.

So this expression:
string("aeiouAEIOU").find(c) != string::npos

means:

"If c exists in the vowel string, return true."

Examples:

isVowel('a')  -> true
isVowel('E')  -> true
isVowel('z')  -> false
isVowel('B')  -> false
2. Understanding reverseVowels()
string reverseVowels(string s) {
    int l=0, r=s.size()-1;

Two pointers:

l -> start
r -> end

Example:

s = "hello"

h e l l o
^         ^
l         r
Loop
while(l<r)

Keep moving until pointers meet.

Case 1: Left character is not a vowel
if(!isVowel(s[l]))
    l++;

Example:

h e l l o
^

h is not a vowel.

Move left pointer:

h e l l o
  ^
Case 2: Right character is not a vowel
else if(!isVowel(s[r]))
    r--;

Example:

h e l l o
        ^

If right side isn't a vowel, move it left.

Case 3: Both are vowels
else
    swap(s[l++], s[r--]);

Swap them.

Then:

l++ moves left pointer right
r-- moves right pointer left
Dry Run: "hello"
Initial
h e l l o
^       ^
l       r
Step 1

h is not vowel

l++;
h e l l o
  ^     ^
Step 2

e is vowel

o is vowel

Swap:

h o l l e

Move pointers:

h o l l e
    ^ ^
Step 3

l not vowel

l++;
h o l l e
      ^^

Now l >= r.

Stop.

Result:

"holle"
Another Example: "leetcode"

Vowels are:

e e o e

Reverse them:

e o e e

Result:

"leotcede"
A clearer version
bool isVowel(char c)
{
    string vowels = "aeiouAEIOU";

    if (vowels.find(c) != string::npos)
        return true;

    return false;
}

string reverseVowels(string s)
{
    int left = 0;
    int right = s.size() - 1;

    while (left < right)
    {
        if (!isVowel(s[left]))
        {
            left++;
        }
        else if (!isVowel(s[right]))
        {
            right--;
        }
        else
        {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }

    return s;
}

The key idea is:

Use two pointers. Skip consonants. When both pointers point to vowels, swap them.

```

------------------------------------------------------------------------

## 4. **Valid Palindrome (Easy)**

**Idea:** Two pointers skipping non-alphanumeric.

**C++ Code:**

``` cpp
bool isPalindrome(string s) {
    string t="";
    for(char c:s){
        if(isalnum(c)) t+=tolower(c);
    }
    int l=0, r=t.size()-1;
    while(l<r){
        if(t[l]!=t[r]) return false;
        l++; r--;
    }
    return true;
}
```

------------------------------------------------------------------------

## 5. **Valid Anagram (Easy)**

An anagram means both strings contain the same characters with the same frequencies, possibly in a different order.

**Idea:** Count frequency of characters.

**C++ Code:**

``` cpp
bool isAnagram(string s, string t) {
    if(s.size()!=t.size()) return false;
    vector<int> a(26,0);
    for(char c:s) a[c-'a']++;
    for(char c:t){
        if(--a[c-'a']<0) return false;
    }
    return true;
}

Why don't we need a final loop checking all counts are zero?

Because:

Lengths are equal.
We return false immediately if any count becomes negative.

If all characters of t are consumed without going negative, then every count must end at exactly zero.

Dry Run
s = "anagram"
t = "nagaram"

Count from s:

a:3
n:1
g:1
r:1
m:1

Process t:

n -> 0
a -> 2
g -> 0
a -> 1
r -> 0
a -> 0
m -> 0

No negative count.

return true;
Time and Space Complexity
Time

Two loops over the strings:

O(n) + O(n) = O(n)

So:

Time Complexity: O(n)

Space

Frequency array size is always 26:

vector<int> a(26,0);

Regardless of input size.

Space Complexity: O(1)

(Constant extra space)

Meaning of --a[c-'a']

This line often confuses beginners:

--a[c-'a']

It's a pre-decrement.

Equivalent to:

a[c-'a']--;
if(a[c-'a'] < 0)
    return false;

except the decrement happens before the value is checked.

Example:

a[1] = 0;

--a[1];   // becomes -1

Then:

if(-1 < 0)

returns true.

That's how the code detects an extra character in t.


```

------------------------------------------------------------------------

## 6. **Shortest Word Distance (Easy)**

**Idea:** Track latest index of each word.

**C++ Code:**

``` cpp
int shortestDistance(vector<string>& words, string w1, string w2) {
    int i1=-1, i2=-1, ans=INT_MAX;
    for(int i=0;i<words.size();i++){
        if(words[i]==w1) i1=i;
        if(words[i]==w2) i2=i;
        if(i1!=-1 && i2!=-1)
            ans=min(ans, abs(i1-i2));
    }
    return ans;
}

Dry run above code 




```

------------------------------------------------------------------------

## 7. **Number of Good Pairs (Easy)**

**Idea:** Count frequency and compute pairs.

**C++ Code:**

``` cpp
int numIdenticalPairs(vector<int>& nums) {
    vector<int> f(101,0);
    int ans=0;
    for(int x:nums){
        ans += f[x];
        f[x]++;
    }
    return ans;
}
```

------------------------------------------------------------------------

## 8. **Sqrt (Medium)**

**Idea:** Binary search for integer sqrt.

**C++ Code:**

``` cpp
int mySqrt(int x) {
    long l=0, r=x, ans=0;
    while(l<=r){
        long m=(l+r)/2;
        if(m*m<=x){
            ans=m;
            l=m+1;
        } else r=m-1;
    }
    return ans;
}
```

------------------------------------------------------------------------

## ⭐ More warmup lessons continue...

This file contains the first set of the warmup lesson solutions.
