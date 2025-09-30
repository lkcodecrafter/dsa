#include <iostream>
#include <math.h>
#include <queue>
using namespace std;

class Node
{
public:
    int val;
    Node *left;
    Node *right;

    Node(int val)
    {
        this->val = val;
        left = right = NULL;
    }
};

// Problem 1: Size of Binary Tree
int sizeOfTree(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + sizeOfTree(root->left) + sizeOfTree(root->right);
}

// Problem 2: Sum of Binary Tree
int sumOfTree(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return root->val + sumOfTree(root->left) + sumOfTree(root->right);
}

// Problem 3: Count Leaves in Binary Tree
int countLeaves(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL && root->right == NULL)
        return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

// Problem 4: Count Non-Leaves in Binary Tree
int countNonLeaves(Node *root)
{
    if (root == NULL || (root->left == NULL && root->right == NULL))
    {
        return 0;
    }
    return 1 + countNonLeaves(root->left) + countNonLeaves(root->right);
}

// Problem 5: Height of Binary Tree
int height(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + max(height(root->left), height(root->right));
}

// Problem 7: Largest Value in Each Level
void largestValueEachLevel(Node *root)
{
    if(root == NULL){
        return;
    }
    int maxElement= INT_MIN;
    queue<Node *> q;
    q.push(root);
    while (!q.empty()){
        int n = q.size();
        while (n--)
        {
            Node *node = q.front();
            q.pop();
            maxElement = max(maxElement, node->val);
            if (node->left)
            {
                q.push(node->left);
            }
            if(node->right){
                q.push(node->right);
            }
        }
        cout<<maxElement<<" ";
    }
    
}
int main(int argc, char const *argv[])
{
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    cout << "size of Tree " << sizeOfTree(root) << endl;
    cout << "sum of Tree " << sumOfTree(root) << endl;
    cout << "count Leaves " << countLeaves(root) << endl;
    cout << "cout Non Leaves " << countNonLeaves(root) << endl;
    cout << "Height of Tree " << height(root) << endl;
    largestValueEachLevel(root);
    return 0;
}
