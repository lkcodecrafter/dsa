/*
    QUESTION    : Clone Graph (Deep Copy of Connected Undirected Graph)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart
    LeetCode    : https://leetcode.com/problems/clone-graph/
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Definition for a Node
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() : val(0), neighbors() {}
    Node(int _val) : val(_val), neighbors() {}
    Node(int _val, vector<Node*> _neighbors) : val(_val), neighbors(_neighbors) {}
};

/************************************************************ C++ ************************************************************/
// T.C : O(V + E) - DFS with hash map tracking cloned nodes
// S.C : O(V)     - Visited hash map
class Solution {
private:
    unordered_map<Node*, Node*> clones;

public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        // If already cloned, return existing cloned instance
        if (clones.find(node) != clones.end()) {
            return clones[node];
        }

        Node* copy = new Node(node->val);
        clones[node] = copy;

        // Clone all neighbors recursively
        for (Node* neighbor : node->neighbors) {
            copy->neighbors.push_back(cloneGraph(neighbor));
        }

        return copy;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `unordered_map<Node*, Node*> clones`.
 * - If `clones.count(node)` return `clones[node]`.
 * - Create `copy = new Node(node->val); clones[node] = copy;`
 * - Recurse: `copy->neighbors.push_back(cloneGraph(neighbor));`
 * - Time: O(V + E), Space: O(V).
 */
