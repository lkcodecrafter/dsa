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

/*
Summary (remember this rule of thumb for interviews ⭐)
Condition	Meaning	Action
if (root == nullptr)	The tree is empty.	Return an empty list.
while (!q.empty())	There are still nodes to process.	Continue processing the next level
we use a queue to keep track of the nodes at the current level. We process each node, add its value to the current level list, and enqueue its children for the next level. Once we finish processing all nodes at the current level, we add the level list to our result and move on to the next level until there are no more nodes to process.
it's also called breadth-first search (BFS) traversal of the binary tree, which is a common technique for level order traversal.
One-line intuition (interview gold ⭐)
*/