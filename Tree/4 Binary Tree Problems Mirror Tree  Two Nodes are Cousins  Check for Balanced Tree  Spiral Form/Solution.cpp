#include <iostream>
using namespace std;

class Node{
    public:
    int val;
    Node *left;
    Node *right;
    Node(int val){
        this->val = val;
        left=right=NULL;
    }
};

// Problem 1: Determine if Two Trees are Identical
bool isIdentical(Node* a, Node* b) {
    if(a == NULL && b == NULL){
        return true;
    }
    if(a==NULL || b==NULL){
        return false;
    }
    return (a->val == b->val) && isIdentical(a->left, b->left) && isIdentical(a->right,b->right);
}
int main(int argc, char const *argv[])
{
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);

    Node* root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);

    cout << "Identical Trees: " << (isIdentical(root1, root2) ? "Yes" : "No") << endl;

    return 0;
}
