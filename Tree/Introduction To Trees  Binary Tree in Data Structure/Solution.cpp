#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x)
    {
        val = x;
        left = NULL;
        right = NULL;
    }
};

class Solution
{
};
int main(int argc, char const *argv[])
{
    cout << "Enter root value" << endl;
    int rootVal;
    cin >> rootVal;
    TreeNode *root = new TreeNode(rootVal);
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *temp = q.front();
        q.pop();
        // cout<<root->val<<endl;

        cout << "Enter left child of " << temp->val << endl;
        int left;
        cin >> left;
        if (left != -1)
        {
            temp->left = new TreeNode(left);
            q.push(temp->left);
        }
        cout << "Enter right child of " << temp->val << endl;
        int right;
        cin >> right;
        if (right != -1)
        {
            temp->right = new TreeNode(right);
            q.push(temp->right);
        }
    }

    return 0;
}
