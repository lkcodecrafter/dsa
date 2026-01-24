#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Trie {
public:

    Trie* children[26];
    bool eow; // end of word
    Trie() {
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
        eow = false;   
        
    }
    
    void insert(string word) {
        Trie* node = this;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new Trie(); // create a new node if it doesn't exist means
                // this character is not present in the trie
                // so we create a new node for this character
                // and link it to the current node
                // move to the child node
                // and continue for the next character example character 'a' - 'a' = 0, 'b' - 'a' = 1
                // so we can use this index to access the children array
                // of the current node
            }
            node = node->children[index]; // move to the child node
        }
        node->eow = true; 
    }
    
    bool search(string word) {
        Trie* node = this;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return node->eow;
    }
    
    // Returns if there is any word in the trie that starts with the given prefix.
    // example: prefix = "app" -> "apple", "appetite"
    // so we need to check if there is any word in the trie that starts with "app"
    // we don't care if "app" is a word or not
    // we just need to check if there is any word that starts with "app"
    // so we just need to traverse the trie for the prefix
    // if we can traverse the trie for the entire prefix
    bool startsWith(string prefix) {
        Trie* node = this;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */