#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (root == NULL) return {};

        vector<int> output_list;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();
            int lastVal = 0;
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                lastVal = node->val; // keep updating, last one will be rightmost
                if (node->left != NULL) q.push(node->left);
                if (node->right != NULL) q.push(node->right);
            }
            output_list.push_back(lastVal);
        }

        return output_list;
    }
};

/*

📝 Dry Run Explanation
Let’s take an example tree:

        1
       / \
      2   3
       \    \
        5    4


Step-by-step BFS traversal:
Initialization:
queue = [1], output_list = []

Level 1:
Queue size = 1

Process node 1 → lastVal = 1

Add children: 2, 3

Queue = [2, 3]

Append lastVal → output_list = [1]

Level 2:
Queue size = 2

Process node 2 → lastVal = 2, add child 5

Process node 3 → lastVal = 3, add child 4

Queue = [5, 4]

Append lastVal → output_list = [1, 3]

Level 3:
Queue size = 2

Process node 5 → lastVal = 5 (no children)

Process node 4 → lastVal = 4 (no children)

Queue = []

Append lastVal → output_list = [1, 3, 4]

🎯 Final Output
Code
Right Side View = [1, 3, 4]
📊 Visualization of BFS Levels
Code
Level 1: [1] → rightmost = 1
Level 2: [2, 3] → rightmost = 3
Level 3: [5, 4] → rightmost = 4
So, the algorithm captures the last node at each level → that’s the right side view.

*/