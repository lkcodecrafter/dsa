#include <bits/stdc++.h>
using namespace std;


//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        return solve(root, k);
    }

    int solve(TreeNode* root, int &k){
        if(root==nullptr){
            return 0;
        }
        int left = solve(root->left, k);
        if(left){      // measn we found the kth smallest in the left subtree, so we return it up the call stack
            // value of left is the kth smallest, so we return it directly without further processing
            // what mean if(left) ?
            // if(left) checks if the left subtree call returned a non-zero value, which indicates that the kth smallest element was found in the left subtree. If it is non-zero, we return that value immediately, as it is the answer we are looking for. If it is zero, it means the kth smallest element was not found in the left subtree, and we continue processing the current node and then the right subtree.
            return left;
        }
        k=k-1;
        if(k==0){
            return root->val;
        }
        return solve(root->right, k);
    }
};