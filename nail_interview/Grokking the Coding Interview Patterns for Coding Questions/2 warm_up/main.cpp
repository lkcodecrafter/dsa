#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Pair Sum - Sorted
vector<int> pair_sum_sorted(vector<int> arr, int target)
{
    int left = 0, right = arr.size() - 1;
    while (left < right)
    {
        int sum = arr[left] + arr[right];
        if (sum == target)
        {
            return {left, right};
        }
        if (sum < target)
        {
            left++;
        }
        else
        {
            right--;
        }
    }
    return {-1, -1};
}

// Triplet Sum
vector<int> triplet_sum(vector<int> arr, int target)
{
}

/*Problem:** Given an integer array, return true if any value appears at
least twice.
**Idea:** Use a set to track seen numbers. */
bool containsDuplicate(vector<int> &nums)
{
    unordered_set<int> set;
    for (auto x : nums)
    {
        if (set.count(x))
        {
            return true;
        }
        set.insert(x);
    }
    return false;
}

/*## 2. **Pangram (Easy)**

**Problem:** Check whether a sentence contains all 26 English letters.\
**Idea:** Count letters using a boolean array.

**C++ Code:**

*/
bool checkIfPangram(string s)
{
    vector<int> c(26, 0);
    for (char x : s)
    {
        c[x - 'a'] = 1;
    }
    for (int x : c)
    {
        if (x == 0)
        {
            return false;
        }
    }
    return true;
}

/*## 3. **Reverse Vowels (Easy)**

**Idea:** Two-pointer swap on vowels.

**C++ Code:** */

bool isVowel(char c)
{
    return string("aeiouAEIOU").find(c) != string::npos;
}

string reverseVowels(string s)
{
    int l = 0, r = s.size() - 1;
    while (l < r)
    {
        if (!isVowel(s[l]))
        {
            l++;
        }
        else if (!isVowel(s[r]))
        {
            r--;
        }
        else
        {
            swap(s[l++], s[r--]);
        }
    }
    return s;
}

/*
isalnum - isalnum is a function or method in programming languages like Python
and C that checks if a character or string is alphanumeric, meaning it contains only letters
(\(a-z\), \(A-Z\)) and numbers (\(0-9\)). It returns a boolean value: True (or a non-zero integer)
if all characters are alphanumeric, and False (or zero) otherwise.

## 4. **Valid Palindrome (Easy)**

**Idea:** Two pointers skipping non-alphanumeric.

**C++ Code:**
*/
bool isPalindrome(string s)
{

    string t = "";
    for (char x : s)
    {
        if (isalnum(x))
        {
            t += tolower(x);
        }
    }
    int l = 0, r = t.size() - 1;
    while (l < r)
    {
        if (t[l] != t[r])
        {
            return false;
        }
        l++, r--;
    }
    return true;
}

/*
## 5. **Valid Anagram (Easy)**

**Idea:** Count frequency of characters.

**C++ Code:**

``` cpp
*/
bool isAnagram(string s, string t) {
    if(s.length() != t.length()){
        return false;
    }
    vector<char>fre(26,0);
    for(int i=0;i<s.length();i++){
        fre[s[i]-'a']++;
        fre[t[i]-'a']--;
    }

    for(auto x : fre){
        if(x!=0){
            return false;
        }
    }
    return true;
}

/*
## 6. **Shortest Word Distance (Easy)**

**Idea:** Track latest index of each word.

**C++ Code:**

``` cpp
*/
int shortestDistance(vector<string>& words, string w1, string w2) {

    int i1=-1, i2=-1, ans=INT_MAX;
    for(int i=0;i<words.size();i++){
        if(words[i]==w1) i1=i;
        if(words[i]==w2) i2 = i;

        if(i1!= -1 && i2!=-1)
        ans = min(ans, abs(i1-i2));
    }
    return ans;
}
/*
## 7. **Number of Good Pairs (Easy)**

**Idea:** Count frequency and compute pairs.

**C++ Code:**
*/

int numIdenticalPairs(vector<int>& nums) {

    //Below is specified we can you unordered_map<int,int> as key as value and value will be frequency
    vector<int>freq(101,0);
    int ans =0;
    for(int x : nums){
        ans+=freq[x];
        freq[x]++;
    }
return ans;
}

/*
## 8. **Sqrt (Medium)**

**Idea:** Binary search for integer sqrt.

**C++ Code:**
*/


int mySqrt(int x) {
int l=0,r=x, ans =0;
while(l<=r){
    int mid = (l+r)/2;
    if(mid * mid <=x){
        ans = mid;
        l= mid+1;
    }else{
        r = mid-1;
    }
}
return ans;
}
int main(int argc, char const *argv[])
{
    vector<int> arr = {1, 2, 3, 4, 5,1};
    int target = 5;
    vector<int> result = pair_sum_sorted(arr, target);
    for (auto x : result)
    {
        cout << x;
    }

    cout << containsDuplicate(arr) << endl;
    string str = "abcdefghijklmnopqrstuvwxyz";
    cout << checkIfPangram(str) << endl;

    string str1 = "leetcode";
    cout << reverseVowels(str1) << endl;

    string str2 = "madam";
    cout << isPalindrome(str2)<<endl;

    cout<<isAnagram(str2,str1)<<endl;

    vector<string>words = {"madam", "makes", "sir", "coding", "makes"};
    string w1 = "madam";
    string w2 = "coding";
    cout<<shortestDistance(words, w1,w2)<<endl;

    cout<<numIdenticalPairs(arr)<<endl;
    cout<<mySqrt(25)<<endl;
    return 0;
}
