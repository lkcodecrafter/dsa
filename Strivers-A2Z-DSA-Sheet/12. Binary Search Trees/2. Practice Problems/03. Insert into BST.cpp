/*
Question:
You are given the root node of a binary search tree (BST) and a value to insert
into the tree. Return the root node of the BST after the insertion. It is
guaranteed that the new value does not exist in the original BST.

Notice that there may exist multiple valid ways for the insertion, as long as
the tree remains a BST after insertion. You can return any of them.

Example 1:
Input: root = [4,2,7,1,3], val = 5
Output: [4,2,7,1,3,5]


Example 2:
Input: root = [40,20,70,10,30,50,80], val = 25
Output: [40,20,70,10,30,50,80,25]

Binary tree

          40
       /       \
      20         70
    /    \      /    \
   10    30    50    80



    20
    /\
   10  40
      / \
     30  70
    /    /  \
    25   50 80




Example 3:
Input: root = [], val = 5
Output: [5]
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

/*
Approach:
1. To insert a value 'val' into the BST, we start from the root node and
traverse down the tree to find the appropriate position for insertion.
2. If the BST is empty (i.e., root is null), we create a new node with value
'val' and make it the root of the BST.
3. If the value of the current node is less than 'val', we move to the right
subtree, as the value to be inserted will be greater than the current node.
4. If the value of the current node is greater than or equal to 'val', we move
to the left subtree, as the value to be inserted will be less than or equal to
the current node.
5. We continue this process of traversing down the tree until we reach a leaf
node where we can insert the new value 'val'.

Complexity Analysis
Time complexity: O(h), where h is the height of the BST. In the worst case, the
function needs to traverse the entire height of the BST to find the appropriate
position for insertion. Space complexity: O(h), where h is the height of the
BST. In the worst case, the function may have to traverse the entire height of
the BST, leading to h recursive calls in the call stack.

CODE:-

*/

TreeNode *insertIntoBST(TreeNode *root, int val) {
  if (!root)
    return new TreeNode(val);
  if (root->val < val)
    root->right = insertIntoBST(root->right, val);
  else
    root->left = insertIntoBST(root->left, val);
  return root;
}

/*
Step 1: The Rule

For every new value:

If it is less than the current node → go left.
If it is greater than the current node → go right.
Keep moving until you find an empty spot.

Think of it like walking through the tree.

Example 1: 4, 2, 7, 1, 3
Insert 4

It's the first value, so it becomes the root.

4
Insert 2

Start at 4.

2 < 4 ?
Yes.

Go left. Left is empty, so insert there.

  4
 /
2
Insert 7

Start at 4.

7 > 4 ?
Yes.

Go right. Right is empty.

  4
 / \
2   7
Insert 1

Start at 4.

1 < 4 ?
Yes → go left to 2.

Now compare with 2.

1 < 2 ?
Yes → go left.

Left is empty.

    4
   / \
  2   7
 /
1
Insert 3

Start at 4.

3 < 4 ?
Yes → go left to 2.

Compare with 2.

3 > 2 ?
Yes → go right.

Right is empty.

    4
   / \
  2   7
 / \
1   3

Done!

Example 2: 8, 3, 10, 1, 6
Insert 8
8
Insert 3
3 < 8
  8
 /
3
Insert 10
10 > 8
  8
 / \
3  10
Insert 1
1 < 8
1 < 3
    8
   / \
  3  10
 /
1
Insert 6
6 < 8
6 > 3
    8
   / \
  3  10
 / \
1   6
How to check if a tree is a valid BST

Whenever you're unsure, check every node:

Everything in the left subtree must be smaller than the node.
Everything in the right subtree must be greater than the node.

For example:

    2
   / \
  1   4
     / \
    3   7

Check:

1 < 2 ✅
4 > 2 ✅
3 is left of 4, so 3 < 4 ✅ and it's also in the right subtree of 2, so 3 > 2 ✅
7 > 4 ✅

So it is a valid BST.

A trick that helps beginners

When inserting a value, say the comparisons out loud.

For example, inserting 5 into this tree:

    4
   / \
  2   7
 / \
1   3

Say:

5 > 4 → go right.
5 < 7 → go left.
Left is empty → insert.

Result:

    4
   / \
  2   7
 / \ /
1  3 5

If you practice this "compare and move" method, you'll rarely place a node
incorrectly.

Let's practice

I'll give you a set of values:

10, 5, 15, 3, 7, 12, 18

Try drawing the BST yourself and send it here (even if it's just typed using
text). I'll check it and explain any mistakes step by step.

*/