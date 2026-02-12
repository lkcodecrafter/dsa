#include <bits/stdc++.h>
using namespace std;


class LRUCache {
public:
    class Node {
    public:
        int val;
        int key;
        Node* next;
        Node* prev;

        Node(int k, int v) {
            key = k;
            val = v;
        }
    };

    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);
    int cap;
    unordered_map<int, Node*> mp;
    LRUCache(int capacity) {
        cap = capacity;
        head->next = tail;
        tail->prev = head;
    }

    void addNode(Node* node) {
        Node* temp = head->next;
        node->next = temp;
        node->prev = head;
        head->next = node;
        temp->prev = node;
    }

    void delNode(Node* node) {
        Node* delprev = node->prev;
        Node* delnext = node->next;
        delprev->next = delnext;
        delnext->prev = delprev;
    }

    int get(int key) {
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            int res = node->val;
            mp.erase(key);
            delNode(node);
            addNode(node);
            mp[key] = head->next;
            return res;
        }

        return -1;
    }

    void put(int key, int value) {
        if (mp.find(key) != mp.end()) {
            Node* node = mp[key];
            mp.erase(key);
            delNode(node);
            delete node;
        }
        if (mp.size() == cap) {
            Node* node = tail->prev;
            mp.erase(node->key);
            delNode(node);
            delete node;
        }
        addNode(new Node(key, value));
        mp[key] = head->next;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// Driver code
int main() {
    // Create cache with capacity 2
    LRUCache cache(2);

    // Put values in cache
    cache.put(1, 1);
    cache.put(2, 2);

    // Get value for key 1
    cout << cache.get(1) << endl; 

    // Insert another key (evicts key 2)
    cache.put(3, 3);

    // Key 2 should be evicted
    cout << cache.get(2) << endl; 

    // Insert another key (evicts key 1)
    cache.put(4, 4);

    // Key 1 should be evicted
    cout << cache.get(1) << endl; 

    // Key 3 should be present
    cout << cache.get(3) << endl; 

    // Key 4 should be present
    cout << cache.get(4) << endl; 

    return 0;
}


/*

User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily?

GitHub Copilot: I'll create a short plan (todo list) for this task, then ask two quick questions about the diagram type and which example sequence to dry-run.

Created 5 todos

Planned tasks created. Next I'll ask two quick questions about diagram style and example input.

Asked 2 questions (Diagram, Example)

Great — using a Mermaid diagram and the default example sequence. 

Please paste the contents of `146. LRU Cache.cpp` (or confirm I should use a typical LRU Cache C++ implementation) so I can annotate, dry-run with the sequence, and produce the Mermaid visualization.

User: @workspace /explain 

Workspace: This class implements an LRU (least-recently-used) cache using a doubly linked list for recency ordering and an unordered_map for O(1) key lookup. The inner Node class stores key, value and next/prev pointers. The LRUCache holds two dummy nodes (head and tail) so that the most-recently-used node is always right after head and the least-recently-used node is always right before tail. The constructor links those sentinels and stores the capacity.

addNode inserts a node immediately after head (making it most-recently-used). deleteNode unlinks a node by patching its neighbors’ next/prev pointers. get checks the map; if the key exists it reads the value, unlinks the node and re-inserts it at the front (to mark it recently used), updates the map entry, and returns the value; otherwise it returns -1. put first removes an existing entry for the same key (unlinking and erasing the map entry), then if the cache is full it evicts the tail->prev node (the least-recently-used) by erasing it from the map and unlinking it. Finally it creates a new Node, inserts it at the front, and records it in the map.

Complexity: both get and put are O(1) on average because map operations and the constant-time linked-list pointer updates are used to maintain order and lookups.

Gotchas and improvements: node objects are allocated with new but never deleted, so evicted or replaced nodes cause memory leaks; call delete on unlinked nodes (or use smart pointers) to fix that. The Node constructor doesn’t initialize next/prev to nullptr, which can make uninitialized-pointer bugs harder to diagnose. Erasing and re-inserting the map entry in get is unnecessary—simply move the node and update its mapping in place. Also handle edge cases such as capacity == 0.

User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily?

GitHub Copilot: I'll open the file to read its contents, then update the todo list.

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week7/146.%20LRU%20Cache.cpp)

Starting: *Annotate and explain the code* (2/5)

Progress update — file loaded and TODOs updated; next I'll annotate the code, run a dry-run (capacity=2) and render a Mermaid diagram. 

Below is a concise annotated walkthrough, a step-by-step dry run for the sequence you asked for, and a Mermaid diagram (rendered below) illustrating cache snapshots.

**File:** `146. LRU Cache.cpp`

- **Overview**: `LRUCache` uses a doubly-linked list (with dummy `head` and `tail`) to
 track recency and an `unordered_map<int, Node*>` for O(1) lookup. Most-recently-used (MRU) nodes are placed right after `head`. 
 Least-recently-used (LRU) node is right before `tail`.

- **Key methods**:
  - `addNode(Node* newNode)`: insert `newNode` immediately after `head` (makes it MRU).
  - `deleteNode(Node* delNode)`: unlink `delNode` by patching neighbors.
  - `get(int key_)`: if present, remove node, re-insert at front, return value; otherwise return -1.
  - `put(int key_, int value)`: if key exists erase old node; if capacity reached evict `tail->prev`; 
  insert new node at front and update map.

- **Memory note**: nodes are created with `new` but never `delete` (evicted nodes are unlinked but not deallocated) — 
this leaks memory. Fix by `delete`-ing nodes when evicted or use smart pointers.

Step-by-step dry run (capacity = 2) — operations: put(1,1), put(2,2), get(1), put(3,3), get(2), put(4,4), get(1), get(3), get(4)

- Initial state:
  - List: Head <-> Tail
  - Map: {}

1) put(1,1)
  - Insert node (1,1) after Head.
  - List: Head <-> 1 <-> Tail
  - Map: {1 -> node(1)}

2) put(2,2)
  - Insert node (2,2) after Head.
  - List: Head <-> 2 <-> 1 <-> Tail  (2 is MRU, 1 is LRU)
  - Map: {1,2}

3) get(1)  -> returns 1
  - Node(1) exists. Remove it from its place and add after Head (becomes MRU).
  - List becomes: Head <-> 1 <-> 2 <-> Tail
  - Map unchanged keys; mapping updated to new node position.
  - Output: 1

4) put(3,3)
  - Capacity full (size==2). Evict LRU: node before Tail => node(2).
  - Remove node(2) from list and erase key 2 from map.
  - Insert node(3,3) after Head.
  - List: Head <-> 3 <-> 1 <-> Tail
  - Map: {1,3}

5) get(2) -> returns -1
  - Key 2 not found (evicted).
  - List unchanged: Head <-> 3 <-> 1 <-> Tail
  - Output: -1

6) put(4,4)
  - Capacity full. Evict LRU => node(1); erase key 1.
  - Insert node(4,4) at front.
  - List: Head <-> 4 <-> 3 <-> Tail
  - Map: {3,4}

7) get(1) -> returns -1
  - Key 1 not present.
  - Output: -1

8) get(3) -> returns 3
  - Node(3) exists; move it to front (MRU).
  - List: Head <-> 3 <-> 4 <-> Tail
  - Output: 3

9) get(4) -> returns 4
  - Node(4) exists; move it to front.
  - List: Head <-> 4 <-> 3 <-> Tail
  - Output: 4

Summary of printed outputs (in order):
- 1
- -1
- -1
- 3
- 4

Mermaid diagram (snapshot chain). Below is the Mermaid markup I used and the rendered diagram:

Mermaid markup:
```mermaid
flowchart LR
  s0["Start: Head → Tail"]
  s1["put(1,1)\nHead → 1 → Tail"]
  s2["put(2,2)\nHead → 2 → 1 → Tail"]
  s3["get(1)=1\nHead → 1 → 2 → Tail"]
  s4["put(3,3)\n(evict 2)\nHead → 3 → 1 → Tail"]
  s5["get(2)=-1\nHead → 3 → 1 → Tail"]
  s6["put(4,4)\n(evict 1)\nHead → 4 → 3 → Tail"]
  s7["get(1)=-1\nHead → 4 → 3 → Tail"]
  s8["get(3)=3\nHead → 3 → 4 → Tail"]
  s9["get(4)=4\nHead → 4 → 3 → Tail"]
  s0 --> s1 --> s2 --> s3 --> s4 --> s5 --> s6 --> s7 --> s8 --> s9
```

Rendered diagram:
I've generated the diagram for you to inspect visually.

Next steps
- I can (pick one):
  - Show an annotated copy of the source with inline comments inserted into `146. LRU Cache.cpp`.
  - Fix the memory leak (add `delete` for evicted nodes) and provide a safe C++ variant.
  - Produce a step-by-step ASCII table if you prefer plain text.
Which would you like me to do next?


*/