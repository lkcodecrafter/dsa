#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(nullptr), right(nullptr){};
    
    TreeNode(int data): val(data), left(nullptr), right(nullptr){};
    TreeNode(int data, TreeNode* l, TreeNode* r): val(data), left(l), right(r){};
};

class Solution {
public:
   vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> list;
        if (root == nullptr) {
            return list;
        }
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            vector<int> l;
            while (n--) {
                TreeNode* node = q.front();
                q.pop();
                if (node != nullptr) {
                    l.push_back(node->val);
                }
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            list.push_back(l);
        }

        return list;
    }
};