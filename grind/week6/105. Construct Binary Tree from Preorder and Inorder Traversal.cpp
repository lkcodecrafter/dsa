#include<iostream>
#include<vector>
#include<map>
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        map<int,int>mp;
        for(int i=0;i<inorder.size();i++){
            mp[inorder[i]]=i; // it'll print as value and its index in inorder traversal for 
            //example inorder={9,3,15,20,7} then mp will be {9:0,3:1,15:2,20:3,7:4}
        }

        return build(preorder, 0, preorder.size()-1, inorder, 0, inorder.size()-1, mp);
    }

    TreeNode* build(vector<int>& preorder,int pStart, int pEnd, vector<int>& inorder, int iStart, int iEnd, map<int,int>& mp) {
        if(pStart> pEnd || iStart > iEnd){
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[pStart]);
        int index      = mp[root->val]; // for example if root->val=3 then index=1 from the above mp why taken index 
        //because in inorder 3 is at index 1
        // left subtree size = index - iStart
        // right subtree size = iEnd - index
        // why required size? to divide the preorder array into left and right subtree
        root->left  = build(preorder, pStart+1, pStart+index-iStart, inorder, iStart, index-1, mp);
        root->right = build(preorder, pStart+index-iStart+1, pEnd, inorder, index+1, iEnd, mp);
        return root;

    }
};