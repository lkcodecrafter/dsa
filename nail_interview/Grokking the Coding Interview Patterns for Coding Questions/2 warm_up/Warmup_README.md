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
```

------------------------------------------------------------------------

## 3. **Reverse Vowels (Easy)**

**Idea:** Two-pointer swap on vowels.

**C++ Code:**

``` cpp
bool isVowel(char c){
    return string("aeiouAEIOU").find(c) != string::npos;
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
