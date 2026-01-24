#include <iostream>
#include <queue>
using namespace std;

class TreeNode{

    public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val){
        this->val = val;
        left=right=NULL;
    }
};

void preOrder(TreeNode *root){
    if(root ==NULL){
        return ;
    }
    cout<<root->val << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(TreeNode *root){
    if(root==NULL){
        return;
    }
    inOrder(root->left);
    cout<<root->val<< " ";
    inOrder(root->right);
}

void postOrder(TreeNode *root){
    if(root==NULL){
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    cout<<root->val<< " ";
}

void levelOrder(TreeNode *root){
    if(root==NULL){
        return ;
    }
    queue<TreeNode *>q;
    q.push(root);
    while (!q.empty()){
        TreeNode *node = q.front();
        q.pop();
        cout<<node->val<<" ";
        if(node->left){
            q.push(node->left);
        }
        if(node->right){
            q.push(node->right);
        }
    }
}

int main(int argc, char const *argv[])
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
 
    cout << "PreOrder: "; preOrder(root); cout << endl;
    cout << "InOrder: "; inOrder(root); cout << endl;
    cout << "PostOrder: "; postOrder(root); cout << endl;
    cout << "LevelOrder: "; levelOrder(root); cout << endl;
  
    /*
           1
         /   \
        2     3 
       / \   / \
      4   5 6   7

    */
    return 0;
}
