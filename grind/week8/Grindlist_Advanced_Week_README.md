# Grind 75 - Advanced Week (Hard Problems)

This README contains:
- Easy-to-understand explanations
- Optimal C++ solutions
- Interview notes
- Dry runs
- Pattern recognition

---

# 1. Kth Smallest Element in a BST

## Pattern
Inorder Traversal

BST inorder = sorted order

```cpp
class Solution {
public:
    int ans;
    int k;

    void inorder(TreeNode* root){
        if(!root) return;

        inorder(root->left);

        k--;
        if(k==0){
            ans=root->val;
            return;
        }

        inorder(root->right);
    }

    int kthSmallest(TreeNode* root, int K) {
        k=K;
        inorder(root);
        return ans;
    }
};
```

### Dry Run

BST:
      5
     / \
    3   6
   / \
  2   4

Inorder:
2 3 4 5 6

k=3

Answer = 4

Time: O(n)

---

# 2. Minimum Window Substring

## Pattern
Sliding Window

```cpp
class Solution {
public:
    string minWindow(string s, string t) {

        vector<int> cnt(128,0);

        for(char c:t)
            cnt[c]++;

        int required=t.size();
        int left=0;
        int start=0;
        int minLen=INT_MAX;

        for(int right=0; right<s.size(); right++) {

            if(cnt[s[right]]>0)
                required--;

            cnt[s[right]]--;

            while(required==0){

                if(right-left+1 < minLen){
                    minLen=right-left+1;
                    start=left;
                }

                cnt[s[left]]++;

                if(cnt[s[left]]>0)
                    required++;

                left++;
            }
        }

        return minLen==INT_MAX ? "" :
               s.substr(start,minLen);
    }
};
```

### Dry Run

s = ADOBECODEBANC
t = ABC

Answer = BANC

---

# 3. Serialize and Deserialize Binary Tree

## Pattern
Preorder DFS

```cpp
class Codec {
public:

    void serializeDFS(TreeNode* root,string& s){

        if(!root){
            s += "#,";
            return;
        }

        s += to_string(root->val)+",";

        serializeDFS(root->left,s);
        serializeDFS(root->right,s);
    }

    string serialize(TreeNode* root) {

        string s;
        serializeDFS(root,s);

        return s;
    }

    TreeNode* build(stringstream& ss){

        string token;
        getline(ss,token,',');

        if(token=="#")
            return nullptr;

        TreeNode* node =
            new TreeNode(stoi(token));

        node->left=build(ss);
        node->right=build(ss);

        return node;
    }

    TreeNode* deserialize(string data) {

        stringstream ss(data);

        return build(ss);
    }
};
```

Time: O(n)

---

# 4. Trapping Rain Water

## Pattern
Two Pointer

```cpp
class Solution {
public:
    int trap(vector<int>& h) {

        int left=0;
        int right=h.size()-1;

        int leftMax=0;
        int rightMax=0;

        int water=0;

        while(left<right){

            if(h[left] < h[right]){

                leftMax=max(leftMax,h[left]);

                water += leftMax-h[left];

                left++;
            }
            else{

                rightMax=max(rightMax,h[right]);

                water += rightMax-h[right];

                right--;
            }
        }

        return water;
    }
};
```

### Dry Run

0 1 0 2 1 0 1 3

Collected Water = 6

---

# 5. Find Median from Data Stream

## Pattern
Two Heaps

```cpp
class MedianFinder {

    priority_queue<int> left;

    priority_queue<int,
        vector<int>,
        greater<int>> right;

public:

    void addNum(int num) {

        left.push(num);

        right.push(left.top());
        left.pop();

        if(right.size() > left.size()){
            left.push(right.top());
            right.pop();
        }
    }

    double findMedian() {

        if(left.size()>right.size())
            return left.top();

        return (left.top()+right.top())/2.0;
    }
};
```

Time:
Add = O(log n)
Median = O(1)

---

# 6. Word Ladder

## Pattern
BFS

```cpp
class Solution {
public:
    int ladderLength(string beginWord,
                     string endWord,
                     vector<string>& wordList) {

        unordered_set<string> dict(
            wordList.begin(),
            wordList.end());

        queue<string> q;
        q.push(beginWord);

        int level=1;

        while(!q.empty()){

            int size=q.size();

            while(size--){

                string word=q.front();
                q.pop();

                if(word==endWord)
                    return level;

                for(int i=0;i<word.size();i++){

                    char original=word[i];

                    for(char c='a'; c<='z'; c++){

                        word[i]=c;

                        if(dict.count(word)){
                            q.push(word);
                            dict.erase(word);
                        }
                    }

                    word[i]=original;
                }
            }

            level++;
        }

        return 0;
    }
};
```

---

# 7. Basic Calculator

## Pattern
Stack

```cpp
class Solution {
public:
    int calculate(string s) {

        stack<int> st;

        long result=0;
        int sign=1;

        for(int i=0;i<s.size();i++){

            if(isdigit(s[i])){

                long num=0;

                while(i<s.size() &&
                      isdigit(s[i])){

                    num=num*10+s[i]-'0';
                    i++;
                }

                result += sign*num;
                i--;
            }
            else if(s[i]=='+')
                sign=1;

            else if(s[i]=='-')
                sign=-1;

            else if(s[i]=='('){

                st.push(result);
                st.push(sign);

                result=0;
                sign=1;
            }
            else if(s[i]==')'){

                result*=st.top();
                st.pop();

                result+=st.top();
                st.pop();
            }
        }

        return result;
    }
};
```

---

# 8. Maximum Profit in Job Scheduling

## Pattern
DP + Binary Search

```cpp
class Solution {
public:

    int jobScheduling(
        vector<int>& startTime,
        vector<int>& endTime,
        vector<int>& profit) {

        vector<vector<int>> jobs;

        for(int i=0;i<profit.size();i++)
            jobs.push_back(
                {startTime[i],
                 endTime[i],
                 profit[i]});

        sort(jobs.begin(),jobs.end());

        map<int,int> dp;
        dp[0]=0;

        for(auto &job:jobs){

            int curProfit =
                prev(dp.upper_bound(job[0]))
                ->second + job[2];

            if(curProfit > dp.rbegin()->second)
                dp[job[1]]=curProfit;
        }

        return dp.rbegin()->second;
    }
};
```

---

# 9. Merge K Sorted Lists

## Pattern
Min Heap

```cpp
class Solution {
public:

    struct cmp{
        bool operator()(ListNode* a,
                        ListNode* b){
            return a->val > b->val;
        }
    };

    ListNode* mergeKLists(
        vector<ListNode*>& lists) {

        priority_queue<
            ListNode*,
            vector<ListNode*>,
            cmp> pq;

        for(auto node:lists)
            if(node) pq.push(node);

        ListNode dummy(0);
        ListNode* tail=&dummy;

        while(!pq.empty()){

            auto node=pq.top();
            pq.pop();

            tail->next=node;
            tail=node;

            if(node->next)
                pq.push(node->next);
        }

        return dummy.next;
    }
};
```

Time: O(N log K)

---

# 10. Largest Rectangle in Histogram

## Pattern
Monotonic Stack

```cpp
class Solution {
public:
    int largestRectangleArea(
        vector<int>& heights) {

        stack<int> st;

        int ans=0;

        heights.push_back(0);

        for(int i=0;i<heights.size();i++){

            while(!st.empty() &&
                  heights[st.top()]
                  > heights[i]){

                int h=heights[st.top()];
                st.pop();

                int w=st.empty() ?
                      i :
                      i-st.top()-1;

                ans=max(ans,h*w);
            }

            st.push(i);
        }

        return ans;
    }
};
```

### Dry Run

[2,1,5,6,2,3]

Largest Rectangle

5 x 2 = 10

Answer = 10

---

# Revision Table

| Problem | Pattern |
|----------|----------|
| Kth Smallest BST | Inorder |
| Minimum Window | Sliding Window |
| Serialize Tree | DFS |
| Trapping Rain Water | Two Pointer |
| Median Stream | Heap |
| Word Ladder | BFS |
| Basic Calculator | Stack |
| Job Scheduling | DP + Binary Search |
| Merge K Lists | Heap |
| Largest Histogram | Monotonic Stack |

# Must Remember

1. Sliding Window
2. Monotonic Stack
3. BFS
4. DFS
5. Heap
6. DP
7. Binary Search
8. Two Pointer

These are among the most frequently asked Google/Meta/Amazon hard patterns.
