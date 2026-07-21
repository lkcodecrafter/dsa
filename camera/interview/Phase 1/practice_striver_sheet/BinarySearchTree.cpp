#include <iostream>
using namespace std;

struct TreeNode {
  int data;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int d) {
    data = d;
    left = right = nullptr;
  }
};

TreeNode *searchInBinaryTree(TreeNode *root, int target) {

  while (root != nullptr && root->data != target) {
    if (target < root->data) {
      root = root->left;
    } else {
      root = root->right;
    }
  }
  return root;
}
int main() {

  TreeNode *root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(3);

  TreeNode *res = searchInBinaryTree(root, 2);
  if (res) {
    cout << "found";
  } else {
    cout << "not found";
  }
};