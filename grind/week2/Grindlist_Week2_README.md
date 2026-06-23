# Grind 75 - Week 2 (C++)

# 1. First Bad Version

## Idea
Use Binary Search to find the first bad version.

```cpp
class Solution {
public:
    int firstBadVersion(int n) {
        long long left = 1;
        long long right = n;

        while(left < right) {
            long long mid = left + (right - left) / 2;

            if(isBadVersion(mid))
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
};
```

### Dry Run
Versions = [1,2,3,4,5]
First Bad = 4

mid=3 -> good
Search right side

mid=4 -> bad
Answer = 4

Time: O(log n)
Space: O(1)


where is BadVersion API?
isBadVersion(int version) is a predefined API that you can call to determine if a given version is bad. It returns true if the version is bad and false if it is good. You do not need to implement this API; it is provided by the system. You can use it in your solution to check if a specific version is bad or not while performing the binary search to find the first bad version.
---

# 2. Ransom Note

## Idea
Count characters using frequency array.
Means how many times each character appears in the magazine and then check if we can construct the ransom note using those characters.


```cpp
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {

        vector<int> freq(26,0);

        for(char c:magazine)
            freq[c-'a']++;

        for(char c:ransomNote) {
            freq[c-'a']--;
            if(freq[c-'a'] < 0)
                return false;
        }

        return true;
    }
};
```

### Dry Run

ransom = "aa"
magazine = "aab"

count(a)=2

Need a -> left=1
Need a -> left=0

Answer = true

Why return true at the end?
We return true at the end because if we have successfully decremented the frequency of all characters in the ransom note without any frequency going negative, it means that we have enough characters in the magazine to construct the ransom note. If any character's frequency goes negative, it means that we do not have enough of that character in the magazine to construct the ransom note, and we return false immediately. If we reach the end of the loop without returning false, it means that all characters in the ransom note can be constructed from the magazine, so we return true.

Example:
ransomNote = "aa"
magazine = "aab"
Frequency after counting magazine:
a: 2
b: 1
Decrementing for ransomNote:
Need 'a' -> frequency of 'a' becomes 1
Need 'a' -> frequency of 'a' becomes 0
Since we never had a negative frequency, we return true at the end, indicating that we can


what means freq[c-'a'] < 0?
freq[c-'a'] < 0 means that the frequency of the character c has become negative after decrementing it for the ransom note. This indicates that we have used more instances of that character than are available in the magazine. For example, if we have a frequency of 2 for the character 'a' in the magazine, and we need to use 'a' twice for the ransom note, we will decrement the frequency twice. After the first decrement, the frequency will become 1, and after the second decrement, it will become 0. If we try to use 'a' again, the frequency will become -1, which means we do not have enough 'a' characters in the magazine to construct the ransom note, and we should return false.

example: of false case 
ransomNote = "aa"
magazine = "ab"
Frequency after counting magazine:
a: 1
b: 1
Decrementing for ransomNote:
Need 'a' -> frequency of 'a' becomes 0
Need 'a' -> frequency of 'a' becomes -1 (negative)
Since we have a negative frequency, we return false immediately, indicating that we cannot construct the ransom note from the magazine because we do not have enough 'a' characters.    
---

# 3. Climbing Stairs

## Idea
Same as Fibonacci.

```cpp
class Solution {
public:
    int climbStairs(int n) {

        if(n<=2) return n;

        int a=1,b=2;

        for(int i=3;i<=n;i++) {
            int c=a+b;
            a=b;
            b=c;
        }

        return b;
    }
};
```

### Dry Run

n=5

1
2
3
5
8

Answer = 8

---

# 4. Longest Palindrome

## Idea
Use frequency counting.

```cpp
class Solution {
public:
    int longestPalindrome(string s) {

        unordered_map<char,int> mp;

        for(char c:s)
            mp[c]++;

        int ans=0;
        bool odd=false;

        for(auto &x:mp) {

            if(x.second%2==0)
                ans+=x.second;
            else {
                ans+=x.second-1;
                odd=true;
            }
        }

        if(odd) ans++;

        return ans;
    }
};
```

### Dry Run

abccccdd

ccccc -> use 4
dd -> use 2
a,b -> use 1 center

Answer = 7


longest palindrome means ?
Longest palindrome means the longest string that can be formed by rearranging the characters of the given string such that it reads the same forwards and backwards. For example, in the string "abccccdd", the longest palindrome that can be formed is "dccaccd" or "dccbccd", which has a length of 7. The characters 'c' and 'd' can be used to form pairs, while 'a' and 'b' can only be used once as the center of the palindrome.
---

# 5. Reverse Linked List

## Idea
Reverse pointers one by one.

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        ListNode* prev=nullptr;

        while(head) {

            ListNode* next=head->next;

            head->next=prev;

            prev=head;
            head=next;
        }

        return prev;
    }
};
```

### Dry Run

1->2->3

After reverse

3->2->1

---

# 6. Majority Element

## Boyer Moore Voting Algorithm

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {

        int candidate=0;
        int count=0;

        for(int num:nums) {

            if(count==0)
                candidate=num;

            if(num==candidate)
                count++;
            else
                count--;
        }

        return candidate;
    }
};
```

### Dry Run

[2,2,1,1,1,2,2]

Answer = 2

Dry run explanation:
- Start with candidate = 0 and count = 0.
- Iterate through the array:
  - num = 2: count is 0, so candidate becomes 2. Since num is equal to candidate, count becomes 1.
  - num = 2: num is equal to candidate (2), so count becomes 2.
  - num = 1: num is not equal to candidate (2), so count becomes 1.
  - num = 1: num is not equal to candidate (2), so count becomes 0.
  - num = 1: count is 0, so candidate becomes 1. Since num is equal to candidate, count becomes 1.
  - num = 2: num is not equal to candidate (1), so count becomes 0.
  - num = 2: count is 0, so candidate becomes 2. Since num is equal to candidate, count becomes 1.
- At the end of the iteration, the candidate is 2, which is the majority element in the array, as it appears more than n/2 times.   

---

# 7. Add Binary

```cpp
class Solution {
public:
    string addBinary(string a, string b) {

        string ans="";
        int carry=0;

        int i=a.size()-1;
        int j=b.size()-1;

        while(i>=0 || j>=0 || carry) {

            int sum=carry;

            if(i>=0) sum+=a[i--]-'0';
            if(j>=0) sum+=b[j--]-'0';

            ans.push_back(sum%2+'0');

            carry=sum/2;
        }

        reverse(ans.begin(),ans.end());

        return ans;
    }
};
```

### Dry Run

11 + 1

3 -> binary 11 + carry

Answer = 100

Dry run explanation:
- Start with carry = 0.
- Add the least significant bits (rightmost): 1 + 1 + 0 = 2. Write down 0, carry 1.
- Next bits: 1 + 1 + 1 = 3. Write down 1, carry 1.
- Next bits: 1 + 0 + 1 = 2. Write down 0, carry 1.
- Next bits: 0 + 0 + 1 = 1. Write down 1, carry 0.
- Final result (reversed): 100

strings "11" and "1" represent the binary numbers 3 and 1, respectively. When we add them together, we get 4, which is represented in binary as "100". The algorithm correctly handles the addition of binary digits and carries to produce the correct result.

---

# 8. Diameter of Binary Tree

## Idea
Diameter = longest path between any two nodes.

```cpp
class Solution {
public:

    int diameter=0;

    int height(TreeNode* root) {

        if(!root)
            return 0;

        int left=height(root->left);
        int right=height(root->right);

        diameter=max(diameter,left+right);

        return 1+max(left,right);
    }

    int diameterOfBinaryTree(TreeNode* root) {

        height(root);

        return diameter;
    }
};
```

### Dry Run

      1
     / \
    2   3
   / \
  4   5

Diameter = 4->2->1->3

Answer = 3 edges

---

# 9. Middle of Linked List

## Fast and Slow Pointer

```cpp
class Solution {
public:
    ListNode* middleNode(ListNode* head) {

        ListNode* slow=head;
        ListNode* fast=head;

        while(fast && fast->next) {
            slow=slow->next;
            fast=fast->next->next;
        }

        return slow;
    }
};
```

### Dry Run

1->2->3->4->5

slow = 3

---

# 10. Maximum Depth of Binary Tree

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {

        if(!root)
            return 0;

        return 1 + max(
            maxDepth(root->left),
            maxDepth(root->right)
        );
    }
};
```

### Dry Run

1
|
2
|
3

Depth = 3

---

# 11. Contains Duplicate

```cpp
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {

        unordered_set<int> st;

        for(int x:nums) {

            if(st.count(x))
                return true;

            st.insert(x);
        }

        return false;
    }
};
```

### Dry Run

[1,2,3,1]

1 already exists

Answer = true

---

# 12. Maximum Subarray

## Kadane Algorithm

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        int curr=nums[0];
        int best=nums[0];

        for(int i=1;i<nums.size();i++) {

            curr=max(nums[i], curr+nums[i]);

            best=max(best,curr);
        }

        return best;
    }
};
```

### Dry Run

[-2,1,-3,4,-1,2,1,-5,4]

Best subarray

4 + (-1) + 2 + 1 = 6

Answer = 6

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
