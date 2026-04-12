# 🚀 Google Interview DSA Sheet (C++)

This README contains **clean C++ solutions + intuition (short)** for top Google interview questions.

---

## 🟢 1. Two Sum
**Approach:** Hash Map

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;
        for(int i=0;i<nums.size();i++){
            int rem = target - nums[i];
            if(mp.count(rem)) return {mp[rem], i};
            mp[nums[i]] = i;
        }
        return {};
    }
};
```

---

## 🟢 2. Palindrome Number
```cpp
class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;
        long rev = 0, temp = x;
        while(temp){
            rev = rev*10 + temp%10;
            temp/=10;
        }
        return rev == x;
    }
};
```

---

## 🟡 3. Add Two Numbers (Linked List)
```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* cur = &dummy;
        int carry = 0;
        while(l1 || l2 || carry){
            int sum = carry;
            if(l1) sum += l1->val, l1 = l1->next;
            if(l2) sum += l2->val, l2 = l2->next;
            carry = sum/10;
            cur->next = new ListNode(sum%10);
            cur = cur->next;
        }
        return dummy.next;
    }
};
```

---

## 🟢 4. Best Time to Buy and Sell Stock
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mn = INT_MAX, profit = 0;
        for(int p : prices){
            mn = min(mn, p);
            profit = max(profit, p - mn);
        }
        return profit;
    }
};
```

---

## 🟢 5. Longest Common Prefix
```cpp
class Solution {
public:
    // Means the longest common prefix of the first and last string after sorting will be the longest common prefix of the whole array.
    // example : ["flower","flow","flight"] after sorting becomes ["flight","flow","flower"] and the longest common prefix of "flight" and "flower" is "fl" which is the longest common prefix of the whole array.

    // Time complexity: O(n log n) for sorting + O(m) for comparing first and last string, where n is the number of strings and m is the length of the longest common prefix.
    string longestCommonPrefix(vector<string>& strs) { //
        sort(strs.begin(), strs.end());
        string a = strs.front(), b = strs.back(); // first and last string after sorting // example : ["flower","flow","flight"] after sorting becomes ["flight","flow","flower"] and the first string is "flight" and the last string is "flower"
        // a = "flight", b = "flower"
        string res="";
        for(int i=0;i<a.size();i++){ // loop through a.size() because the longest common prefix cannot be longer than the first string after sorting.
            if(a[i]==b[i]) res+=a[i]; // example : a = "flight", b = "flower" and the longest common prefix is "fl"
            else break;
        }
        return res;
    }
};
```

---

## 🟡 6. Longest Consecutive Sequence
```cpp
class Solution {
public:
// Problem: Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
// Example: Input: nums = [100,4,200,1,3,2] Output: 4 Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> st(nums.begin(), nums.end());
        int ans = 0;

        for (int x : st) {
            if (!st.count(x - 1)) {
                int curr = x, len = 1;
                while (st.count(curr + 1)) {
                    curr++, len++;
                }
                ans = max(ans, len);
            }
        }

        return ans;
    }
};
```

---

## 🔴 7. Trapping Rain Water
```cpp
class Solution {
public:
    int trap(vector<int>& h) {
        int l=0, r=h.size()-1, lmax=0, rmax=0, ans=0;
        while(l<r){
            if(h[l] < h[r]){
                lmax = max(lmax, h[l]);
                ans += lmax - h[l];
                l++;
            } else {
                rmax = max(rmax, h[r]);
                ans += rmax - h[r];
                r--;
            }
        }
        return ans;
    }
};
```

---

## 🟡 8. Longest Substring Without Repeating Characters
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> mp(256, -1);
        int l=0, ans=0;
        for(int r=0;r<s.size();r++){
            if(mp[s[r]] >= l) l = mp[s[r]] + 1;
            mp[s[r]] = r;
            ans = max(ans, r-l+1);
        }
        return ans;
    }
};
```

---

## 🟢 9. Roman to Integer
```cpp
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char,int> mp={{'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}};
        int ans=0;
        for(int i=0;i<s.size();i++){
            if(i+1<s.size() && mp[s[i]]<mp[s[i+1]]) ans-=mp[s[i]];
            else ans+=mp[s[i]];
        }
        return ans;
    }
};
```

---

## 🔴 10. Median of Two Sorted Arrays
```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        if(A.size() > B.size()) return findMedianSortedArrays(B,A);
        int n=A.size(), m=B.size();
        int l=0, r=n;
        while(l<=r){
            int cut1=(l+r)/2;
            int cut2=(n+m+1)/2 - cut1;

            int l1 = (cut1==0)?INT_MIN:A[cut1-1];
            int l2 = (cut2==0)?INT_MIN:B[cut2-1];
            int r1 = (cut1==n)?INT_MAX:A[cut1];
            int r2 = (cut2==m)?INT_MAX:B[cut2];

            if(l1<=r2 && l2<=r1){
                if((n+m)%2==0) return (max(l1,l2)+min(r1,r2))/2.0;
                else return max(l1,l2);
            }
            else if(l1>r2) r=cut1-1;
            else l=cut1+1;
        }
        return 0;
    }
};
```

---

# 🚀 FULL GOOGLE INTERVIEW SHEET (C++)

Below are **concise C++ solutions** for all major problems you listed.
(Optimized for revision + interviews)

---

## 🟢 EASY PROBLEMS

### Two Sum
```cpp
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int,int> mp;
    for(int i=0;i<nums.size();i++){
        int rem = target - nums[i];
        if(mp.count(rem)) return {mp[rem], i};
        mp[nums[i]] = i;
    }
    return {};
}
```

### Palindrome Number
```cpp
bool isPalindrome(int x) {
    if(x<0) return false;
    long rev=0;
    int t=x;
    while(t){ rev=rev*10+t%10; t/=10; }
    return rev==x;
}
```

### Valid Parentheses
```cpp
bool isValid(string s) {
    stack<char> st;
    for(char c:s){
        if(c=='('||c=='{'||c=='[') st.push(c);
        else{
            if(st.empty()) return false;
            char t=st.top(); st.pop();
            if((c==')'&&t!='(')||(c=='}'&&t!='{')||(c==']'&&t!='[')) return false;
        }
    }
    return st.empty();
}
```

### Single Number (Bit)
```cpp
int singleNumber(vector<int>& nums) {
    int x=0;
    for(int n:nums) x^=n;
    return x;
}
```

### Move Zeroes
```cpp
void moveZeroes(vector<int>& nums) {
    int j=0;
    for(int i=0;i<nums.size();i++)
        if(nums[i]!=0) swap(nums[i],nums[j++]);
}
```

---

## 🟡 MEDIUM PROBLEMS

### 3Sum
```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    vector<vector<int>> res;
    for(int i=0;i<nums.size();i++){
        if(i && nums[i]==nums[i-1]) continue;
        int l=i+1,r=nums.size()-1;
        while(l<r){
            int sum=nums[i]+nums[l]+nums[r];
            if(sum==0){
                res.push_back({nums[i],nums[l],nums[r]});
                while(l<r && nums[l]==nums[l+1]) l++;
                while(l<r && nums[r]==nums[r-1]) r--;
                l++; r--;
            }
            else if(sum<0) l++;
            else r--;
        }
    }
    return res;
}
```

### Merge Intervals
```cpp
vector<vector<int>> merge(vector<vector<int>>& a) {
    sort(a.begin(),a.end());
    vector<vector<int>> res;
    for(auto &it:a){
        if(res.empty()||res.back()[1]<it[0]) res.push_back(it);
        else res.back()[1]=max(res.back()[1],it[1]);
    }
    return res;
}
```

### Container With Most Water
```cpp
int maxArea(vector<int>& h) {
    int l=0,r=h.size()-1,ans=0;
    while(l<r){
        ans=max(ans,min(h[l],h[r])*(r-l));
        if(h[l]<h[r]) l++; else r--;
    }
    return ans;
}
```

### Longest Substring Without Repeat
```cpp
int lengthOfLongestSubstring(string s) {
    vector<int> mp(256,-1);
    int l=0,ans=0;
    for(int r=0;r<s.size();r++){
        if(mp[s[r]]>=l) l=mp[s[r]]+1;
        mp[s[r]]=r;
        ans=max(ans,r-l+1);
    }
    return ans;
}
```

### Group Anagrams
```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string,vector<string>> mp;
    for(auto s:strs){
        string t=s;
        sort(t.begin(),t.end());
        mp[t].push_back(s);
    }
    vector<vector<string>> res;
    for(auto &p:mp) res.push_back(p.second);
    return res;
}
```

---

## 🔴 HARD PROBLEMS

### Trapping Rain Water
```cpp
int trap(vector<int>& h) {
    int l=0,r=h.size()-1,lm=0,rm=0,ans=0;
    while(l<r){
        if(h[l]<h[r]){
            lm=max(lm,h[l]);
            ans+=lm-h[l]; l++;
        } else {
            rm=max(rm,h[r]);
            ans+=rm-h[r]; r--;
        }
    }
    return ans;
}
```

### Sliding Window Maximum
```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> res;
    for(int i=0;i<nums.size();i++){
        while(!dq.empty() && dq.front()<=i-k) dq.pop_front();
        while(!dq.empty() && nums[dq.back()]<=nums[i]) dq.pop_back();
        dq.push_back(i);
        if(i>=k-1) res.push_back(nums[dq.front()]);
    }
    return res;
}
```

### N-Queens
```cpp
void solve(int col, vector<string>& board, vector<vector<string>>& res, vector<int>& left, vector<int>& ld, vector<int>& ud, int n){
    if(col==n){ res.push_back(board); return; }
    for(int row=0;row<n;row++){
        if(!left[row] && !ld[row+col] && !ud[n-1+col-row]){
            board[row][col]='Q';
            left[row]=ld[row+col]=ud[n-1+col-row]=1;
            solve(col+1,board,res,left,ld,ud,n);
            board[row][col]='.';
            left[row]=ld[row+col]=ud[n-1+col-row]=0;
        }
    }
}
```

---

# ⚡ FINAL NOTES

✔ This is a **compact full sheet (Google-level)**
✔ Covers **most asked patterns**
✔ Optimized for **revision, not theory**

---

## 🔥 NEXT LEVEL (Highly Recommended for YOU)

Since you said:
- weak in recursion
- like dry runs
- prefer visual learning

👉 Next I can upgrade this into:

- 📘 FULL README with **DRY RUN + STEP-BY-STEP**
- 📊 Visual diagrams (like you love)
- 🧠 Pattern memory tricks (super useful in interviews)

Just say:
👉 **"MAKE IT INTERVIEW READY"**

