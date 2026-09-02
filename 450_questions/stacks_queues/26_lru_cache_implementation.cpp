/*
    QUESTION    : LRU Cache Implementation (Least Recently Used)
    Company Tags: Amazon, Microsoft, Google, Adobe, Flipkart, Morgan Stanley
    GfG Link    : https://practice.geeksforgeeks.org/problems/lru-cache/1
    LeetCode    : https://leetcode.com/problems/lru-cache/
*/

#include <iostream>
#include <unordered_map>

using namespace std;

/************************************************************ C++ ************************************************************/
// T.C : Get: O(1), Put: O(1)
// S.C : O(Capacity) - Hash map + Doubly Linked List
class LRUCache {
private:
    struct Node {
        int key;
        int val;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };

    int cap;
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    void addNode(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }

    Node* popTail() {
        Node* res = tail->prev;
        removeNode(res);
        return res;
    }

public:
    LRUCache(int capacity) {
        cap = capacity;
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int GET(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        Node* node = cache[key];
        moveToHead(node); // Accessed -> Move to front (Most Recently Used)
        return node->val;
    }

    void SET(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->val = value;
            moveToHead(node);
        } else {
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addNode(newNode);

            // If capacity exceeded, evict least recently used (node before dummy tail)
            if (cache.size() > cap) {
                Node* lru = popTail();
                cache.erase(lru->key);
                delete lru;
            }
        }
    }
};

/*
 * ============================================================================
 * VISUALIZATION OF HASHMAP + DOUBLY LINKED LIST
 * ============================================================================
 *
 * Head (MRU) <===> Node(k1, v1) <===> Node(k2, v2) <===> Tail (LRU)
 *       ^                                                    ^
 *       |--- Most Recently Used             Least Recently Used (Evicted)
 *
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - `unordered_map<int, Node*>` + DLL with dummy `head` and `tail`.
 * - `GET(key)`: if found, `moveToHead(node)` and return `val`.
 * - `SET(key, val)`: update / insert at head; if `size > cap`, `popTail()` and delete from map.
 * - Time: O(1) all ops, Space: O(Capacity).
 */
