/*
    QUESTION    : Huffman Decoding-2 (Huffman Encoding)
    Company Tags: Amazon, Microsoft
    GfG Link    : https://practice.geeksforgeeks.org/problems/huffman-encoding3345/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// Huffman Tree Node
struct Node {
    char data;
    int freq;
    Node *left, *right;
    Node(char d, int f) : data(d), freq(f), left(nullptr), right(nullptr) {}
};

// Custom Comparator for Min-Heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

/************************************************************ C++ ************************************************************/
// T.C : O(N log N) - Min-Heap tree construction + preorder code generation
// S.C : O(N)       - Huffman Tree storage
class Solution {
private:
    void getCodes(Node* root, string code, vector<string>& result) {
        if (!root) return;

        // Leaf node
        if (!root->left && !root->right) {
            result.push_back(code);
            return;
        }

        getCodes(root->left, code + "0", result);
        getCodes(root->right, code + "1", result);
    }

public:
    vector<string> huffmanCodes(string S, vector<int> f, int N) {
        priority_queue<Node*, vector<Node*>, Compare> minHeap;

        for (int i = 0; i < N; i++) {
            minHeap.push(new Node(S[i], f[i]));
        }

        while (minHeap.size() > 1) {
            Node* left = minHeap.top(); minHeap.pop();
            Node* right = minHeap.top(); minHeap.pop();

            Node* parent = new Node('$', left->freq + right->freq);
            parent->left = left;
            parent->right = right;

            minHeap.push(parent);
        }

        vector<string> result;
        getCodes(minHeap.top(), "", result);
        return result;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Min-Heap builds binary tree merging two lowest frequency nodes repeatedly.
 * - Left child $\rightarrow$ '0', Right child $\rightarrow$ '1'.
 * - Time: O(N log N), Space: O(N).
 */
