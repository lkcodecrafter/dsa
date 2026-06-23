# Grind List - Week 1 (C++)

# 1. Two Sum
**Idea:** Store visited numbers in a hash map.

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> mp;
        for(int i=0;i<nums.size();i++){
            int need = target - nums[i];
            if(mp.count(need)) return {mp[need], i};
            mp[nums[i]] = i;
        }
        return {};
    }
};
```

**Dry Run:** nums=[2,7,11,15], target=9
- i=0 -> store 2
- i=1 -> need=2 found
- Answer = [0,1]

---

# 2. Valid Parentheses
```cpp
class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(char c:s){
            if(c=='('||c=='{'||c=='[') st.push(c);
            else{
                if(st.empty()) return false;
                if((c==')'&&st.top()!='(')||
                   (c=='}'&&st.top()!='{')||
                   (c==']'&&st.top()!='['))
                    return false;
                st.pop();
            }
        }
        return st.empty();
    }
};
```

**Dry Run:** "()[]{}" -> push, match, pop -> valid.

---

# 3. Merge Two Sorted Lists
```cpp
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail=&dummy;

        while(l1 && l2){
            if(l1->val < l2->val){
                tail->next=l1;
                l1=l1->next;
            }else{
                tail->next=l2;
                l2=l2->next;
            }
            tail=tail->next;
        }
        tail->next=l1?l1:l2;
        return dummy.next;
    }
};
```

---

# 4. Best Time to Buy and Sell Stock
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mn=INT_MAX, profit=0;
        for(int p:prices){
            mn=min(mn,p);
            profit=max(profit,p-mn);
        }
        return profit;
    }
};
```

**Dry Run:** [7,1,5,3,6,4]
- buy=1
- sell=6
- profit=5

---

# 5. Valid Palindrome
```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        string t="";
        for(char c:s)
            if(isalnum(c)) // isalnum ? 
                t+=tolower(c);

        int l=0,r=t.size()-1;
        while(l<r){
            if(t[l++]!=t[r--]) return false;
        }
        return true;
    }
};
```
Digits are kept (isalnum returns true) and compared like characters,
so numbers must mirror to be a palindrome — e.g. "A1b1A" -> true, "123" -> false.
---

# 6. Invert Binary Tree
```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return nullptr;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};
```
Dry Run: 1
         / \
        2   3
       / \
      4   5
- swap 2 and 3
- swap 4 and 5
- Answer: 1
         / \
        3   2
       / \
      5   4

Is there any other way to do it? Yes, BFS with a queue.
```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return nullptr;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* node=q.front();
            q.pop();
            swap(node->left, node->right);
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        return root;
    }
};
---

# 7. Valid Anagram
```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size()!=t.size()) return false;
        vector<int> cnt(26,0);

        for(char c:s) cnt[c-'a']++;
        for(char c:t) cnt[c-'a']--;

        for(int x:cnt)
            if(x) return false; // if any count is not zero, then s and t are not anagrams if(x) means x!=0, which means there is a mismatch in character counts between s and t. If x>0, it means s has more of that character than t; if x<0, it means t has more of that character than s. In either case, s and t cannot be anagrams, so we return false.
            //can also write if(x!=0) return false; for clarity, but if(x) is a common shorthand in C++ to check if x is non-zero.
        return true;
    }
};
```
Anagram: same characters, different order. So we can count frequency of each character and compare.

Dry Run: s="anagram", t="nagaram"
- count a: 3, n: 1, g: 1, r: 1, m: 1
- count a: -3, n: -1, g: -1, r: -1, m: -1
- all counts are zero -> anagram.   

c-a means index of character c in the alphabet, so 'a'->0, 'b'->1, ..., 'z'->25.
like 'a'-'a'=0, 'b'-'a'=1, ..., 'z'-'a'=25. This way we can use a vector of size 26 to count frequency of each character.
cnt[c-'a']++ means increment count of character c, cnt[c-'a']-- means decrement count of character c. Finally, if all counts are zero, s and t are anagrams.

b value of 'a' is 97, so 'a'-'a'=0, 'b'-'a'=1, ..., 'z'-'a'=25. This way we can use a vector of size 26 to count frequency of each character.
---

# 8. Binary Search
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l=0,r=nums.size()-1;

        while(l<=r){
            int mid=l+(r-l)/2;

            if(nums[mid]==target) return mid;
            if(nums[mid]<target) l=mid+1;
            else r=mid-1;
        }
        return -1;
    }
};
```

---

# 9. Flood Fill
```cpp
class Solution {
public:
    void dfs(vector<vector<int>>& img,int r,int c,int old,int color){
        if(r<0||c<0||r>=img.size()||c>=img[0].size()) return;
        if(img[r][c]!=old) return; // means if the current pixel is not the old color, then we should not change it to the new color and we should not continue the DFS from this pixel. This is because we only want to change the color of the connected component that has the same color as the starting pixel. If we encounter a pixel that has a different color, it means we have reached the boundary of the connected component and we should stop the DFS in that direction.

        if(img[r][c]==color) return; // means if the current pixel is already the new color, then we should not change it again and we should not continue the DFS from this pixel. This is because we have already changed the color of this pixel and we have already visited it in the DFS, so we should not visit it again to avoid infinite recursion.

        img[r][c]=color;

        dfs(img,r+1,c,old,color); // r+1 means down, r-1 means up, c+1 means right, c-1 means left. We need to check all four directions to change the color of the connected component.
        dfs(img,r-1,c,old,color);
        dfs(img,r,c+1,old,color);
        dfs(img,r,c-1,old,color);
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image,
                                  int sr,int sc,int color) {
        int old=image[sr][sc];
        if(old==color) return image;

        dfs(image,sr,sc,old,color);
        return image;
    }
};
```
flood fill is like coloring a connected component in a grid. We can use DFS or BFS to traverse the connected component and change its color. In this code, we use DFS to change the color of the connected component starting from (sr, sc) to the new color. We also check if the old color is the same as the new color to avoid infinite recursion.

help me understand the question and the solution:
- The question is asking us to change the color of a connected component in a 2D grid. The connected component is defined as all pixels that are connected to the starting pixel (sr, sc) and have the same color as the starting pixel. We need to change the color of all these pixels to the new color.

2d grid visualization:
0 0 0
0 1 1
0 0 0

- If we start from (1, 1) which has color 1, the connected component is {(1, 1), (1, 2)} because they are connected and have the same color. If we change their color to 2, the grid becomes:
0 0 0
0 2 2
0 0 0
than we can see that the connected component has been changed to the new color.

so 2 2 is the answer for this input.

Now here is how the code works:
- We first get the old color of the starting pixel (sr, sc) which is image[sr][sc]. If the old color is the same as the new color, we can return the image as it is because we don't need to change anything.
- If the old color is different from the new color, we call the dfs function to change the color of the connected component. The dfs function takes the current pixel (r, c), the old color, and the new color as parameters. It first checks if the current pixel is out of bounds or if its color is different from the old color or if its color is already the new color. If any of these conditions is true, we return from the dfs function because we should not change the color of this pixel or continue the DFS from this pixel.
- If the current pixel is valid, we change its color to the new color and then we call the dfs function recursively for its four neighbors (down, up, right, left) to continue the DFS and change the color of the connected component.
- Finally, we return the modified image after the DFS is complete.



---

# 10. Lowest Common Ancestor of BST
```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root,
                                   TreeNode* p,
                                   TreeNode* q) {

        while(root){
            if(p->val < root->val && q->val < root->val)
                root=root->left;
            else if(p->val > root->val && q->val > root->val)
                root=root->right;
            else
                return root;
        }
        return nullptr;
    }
};
```
Dry Run: p=2, q=8
- Start at root=6
- p and q are on different sides of root, so return root=6  
The idea is to use the property of BST. If both p and q are smaller than root, then LCA must be in left subtree. If both p and q are greater than root, then LCA must be in right subtree. Otherwise, root is the LCA.

Tree visualization:
        6
       / \
      2   8
     / \
    0   4
- If p=2 and q=8, we start at root=6. Since p and q are on different sides of root, we return root=6 as the LCA.
- If p=2 and q=4, we start at root=6. Since both p and q are smaller than root, we move to left subtree. Now root=2. Since p and q are on different sides of root, we return root=2 as the LCA.

---

# 11. Balanced Binary Tree
```cpp
class Solution {
public:
    int height(TreeNode* root){
        if(!root) return 0;

        int l=height(root->left);
        if(l==-1) return -1;

        int r=height(root->right);
        if(r==-1) return -1;

        if(abs(l-r)>1) return -1;

        return 1+max(l,r);
    }

    bool isBalanced(TreeNode* root) {
        return height(root)!=-1;
    }
};
```


The idea is to use a helper function height() that returns the height of the tree if it is balanced, and returns -1 if it is not balanced. The height of a tree is defined as the number of edges on the longest path from the root to a leaf node. A tree is balanced if for every node in the tree, the difference in height between its left and right subtrees is at most 1.
- We first check if the root is null, in which case we return 0 because the height of an empty tree is 0.
- We then recursively call height() for the left and right subtrees. If either of them returns -1, it means that subtree is not balanced, so we return -1 for the current node as well.
- If both left and right subtrees are balanced, we check if the difference in height is greater than 1. If it is, we return -1 because the current node is not balanced.
- If the current node is balanced, we return the height of the current node, which is 1 plus the maximum height of its left and right subtrees.
- Finally, in the isBalanced() function, we call height() for the root and check if it returns -1. If it does, we return false, otherwise we return true.

Tree visualization:
        1
       / \
      2   3
     / \
    4   5
- The height of node 4 is 0, the height of node 5 is 0, the height of node 2 is 1 + max(0, 0) = 1, the height of node 3 is 0, the height of node 1 is 1 + max(1, 0) = 2. The difference in height between node 1's left and right subtrees is 1, which is not greater than 1, so the tree is balanced.

Try with other way DFS code :
```cpp
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;

        int l=height(root->left);
        int r=height(root->right);

        if(abs(l-r)>1) return false; // if the difference in height is greater than 1, then the tree is not balanced

        return isBalanced(root->left) && isBalanced(root->right);
    }

    int height(TreeNode* root){
        if(!root) return 0;
        return 1+max(height(root->left), height(root->right));
    }
};
```
---

# 12. Linked List Cycle
```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slow=head,*fast=head;

        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;

            if(slow==fast) return true;
        }
        return false;
    }
};
```

**Remember:** Slow=1 step, Fast=2 steps.

---

# 13. Implement Queue using Stacks
```cpp
class MyQueue {
    stack<int> in,out;

public:
    void push(int x) {
        in.push(x);
    }

    int pop() {
        peek();
        int x=out.top(); // why two times out.top() ? because we need to get the value of the front element before popping it from the out stack. The peek() function will move all elements from the in stack to the out stack if the out stack is empty, so after calling peek(), the top of the out stack will be the front element of the queue. We can then store this value in x before popping it from the out stack.
        out.pop();
        return x;
    }

    int peek() {
        if(out.empty()){
            while(!in.empty()){
                out.push(in.top());
                in.pop();
            }
        }
        return out.top();
    }

    bool empty() {
        return in.empty() && out.empty();
    }
};
```

here we use two stacks, in and out. The push operation is O(1) because we just push the element to the in stack. The pop and peek operations are O(n) in the worst case because we may need to move all elements from the in stack to the out stack if the out stack is empty. However, if the out stack is not empty, then pop and peek operations are O(1). The empty operation is O(1) because we just check if both stacks are empty.

what is in and out stack?
- The in stack is used to store the elements that are pushed to the queue. The out stack is used to store the elements that are popped from the queue. When we need to pop or peek an element from the queue, we first check if the out stack is empty. If it is, we need to move all elements from the in stack to the out stack. This is done by popping elements from the in stack and pushing them to the out stack until the in stack is empty. After this, the top of the out stack will be the front of the queue, and we can pop or peek it as needed.

Please re-write the code 


---

# Interview Revision

| Problem | Pattern |
|----------|----------|
| Two Sum | Hash Map |
| Valid Parentheses | Stack |
| Merge Lists | Linked List |
| Stock | Sliding Minimum |
| Palindrome | Two Pointer |
| Invert Tree | DFS |
| Anagram | Frequency Count |
| Binary Search | Binary Search |
| Flood Fill | DFS |
| LCA BST | BST Property |
| Balanced Tree | DFS Height |
| Linked List Cycle | Fast & Slow |
| Queue Using Stacks | Stack Design |

Good luck!
