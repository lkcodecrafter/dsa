#include<iostream>
using namespace std;

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
}; 

int ans = INT_MAX;

void inOrder(Node* root, int &prev, int &ans) {
    if (root == NULL) {
        return;
    }
    
    inOrder(root->left, prev, ans);
    
    if (prev != -1) {
        ans = min(ans, root->data - prev);
    }
    prev = root->data;
    
    inOrder(root->right, prev, ans);
}
// Minimum Distance Between BST Nodes

    int minDiffInBST(Node* root) {
        int prev = -1;

        inOrder(root, prev, ans);
        
        return ans;
    }
 


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

 
