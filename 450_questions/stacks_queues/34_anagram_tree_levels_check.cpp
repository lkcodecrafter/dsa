/*
    QUESTION    : Check if all levels of two trees are anagrams or not
    Company Tags: Amazon
    GfG Link    : https://www.geeksforgeeks.org/check-if-all-levels-of-two-trees-are-anagrams-or-not/
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(N) - Simultaneous level-by-level BFS comparing node value frequencies
// S.C : O(W) - Queues and hash map for level anagram validation
class Solution {
public:
    bool areAnagrams(Node *root1, Node *root2) {
        if (root1 == nullptr && root2 == nullptr) return true;
        if (root1 == nullptr || root2 == nullptr) return false;

        queue<Node*> q1, q2;
        q1.push(root1);
        q2.push(root2);

        while (!q1.empty() && !q2.empty()) {
            int n1 = q1.size();
            int n2 = q2.size();

            // Levels must have identical number of nodes
            if (n1 != n2) return false;

            unordered_map<int, int> freq;

            for (int i = 0; i < n1; i++) {
                Node* node1 = q1.front(); q1.pop();
                Node* node2 = q2.front(); q2.pop();

                freq[node1->data]++;
                freq[node2->data]--;

                if (node1->left) q1.push(node1->left);
                if (node1->right) q1.push(node1->right);

                if (node2->left) q2.push(node2->left);
                if (node2->right) q2.push(node2->right);
            }

            // Verify all character frequencies at this level cancelled to 0
            for (auto &entry : freq) {
                if (entry.second != 0) {
                    return false; // Levels are not anagrams
                }
            }
        }

        return q1.empty() && q2.empty();
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Simultaneous BFS on `q1` and `q2`.
 * - For each level: track `freq[n1->data]++` and `freq[n2->data]--`.
 * - If any frequency is non-zero, return `false`.
 * - Time: O(N), Space: O(W).
 */
