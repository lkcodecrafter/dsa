/*
199. Binary Tree Right Side View

Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.


Example 1:

Input: root = [1,2,3,null,5,null,4]

Output: [1,3,4]

Explanation:


Example 2:

Input: root = [1,2,3,4,null,null,null,5]

Output: [1,3,4,5]
*/
#include <iostream>
#include <vector>
#include<queue>
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
    void preOrder(TreeNode* root, int level, vector<int>& result){
        if(root == nullptr){
            return;
        }
        if(result.size()<level){
            result.push_back(root->val);
        }
        preOrder(root->right, level+ 1, result);
        preOrder(root->left, level+1, result);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int>result;
        preOrder(root, 1, result);
        return result;
    }

    vector<int> rightSideViewUsingQueue(TreeNode* root) {
        if(root== nullptr){
            return {};
        }
        vector<int>output;
        queue<TreeNode*>q;
        q.push(root);
        while(!q.empty()){
            int n = q.size();
            int lastValue =0;
            for(int i=0;i<n;i++){
                TreeNode* node = q.front();
                q.pop();
                lastValue = node->val;
                if(node->left !=nullptr){
                    q.push(node->left);
                }
                if(node->right !=nullptr){
                    q.push(node->right);
                }
            }
            output.push_back(lastValue);
        }
        return output;
    }
};

/*

🎯 So Why is Left Level = 2?

Because:

At node 1, level = 1
When going left → level + 1 = 2

👉 It has NOTHING to do with what happened on the right side earlier.

Call A: preOrder(1, level=1)
   |
   |-- Call B: preOrder(3, level=2)
   |       |
   |       |-- Call C: preOrder(4, level=3)
   |
   |-- Call D: preOrder(2, level=2)
*/

int main() {

    return 0;
}