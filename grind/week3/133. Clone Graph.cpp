#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;

// https://www.youtube.com/shorts/mZR0ZR5DLhQ

struct Node
{
    int val;
    vector<Node*>neighbour;
    Node(){
        val = 0;
        neighbour = vector<Node*>();
    };
    Node(int data){
        val = data;
        neighbour = vector<Node*>();
    }

    Node(int data, vector<Node*>n){
        val = data;
        neighbour = n;
    }

};


class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(node == nullptr){
            return nullptr;
        }

        unordered_map<Node*, Node*> mp;
        queue<Node*> q;
        q.push(node);
        mp[node] = new Node(node->val);

        while(!q.empty()){
            Node* curr = q.front();
            q.pop();

            for(auto neighbor : curr->neighbour){
                if(mp.find(neighbor) == mp.end()){ // if neighbor is not visited means not cloned
                    mp[neighbor] = new Node(neighbor->val); // clone the neighbor
                    q.push(neighbor);
                }
                mp[curr]->neighbour.push_back(mp[neighbor]); // create the edge like curr->neighbor to neighbor
                // mp[neighbor] is the cloned neighbor
                // mp[curr] is the cloned curr
                // so we are adding edge from cloned curr to cloned neighbor
                // means mp[curr]->neighbour.push_back(mp[neighbor]);
                // this is how we are building the cloned graph
                // by adding edges between cloned nodes
                // dry run short example : 
                // if curr = 1 and neighbor = 2
                // then mp[1] is cloned node of 1
                // and mp[2] is cloned node of 2
                // so we are adding edge from cloned 1 to cloned 2
                // mp[1]->neighbour.push_back(mp[2]);
                // this way we are building the cloned graph
            }
        }

        return mp[node]; // return the cloned node of the original input node
        // Example : if input node is 1
        // then we return mp[1] which is the cloned node of 1
        // this will be the entry point to the cloned graph
        // if input 2, 3, 4 then we return mp[2], mp[3], mp[4] respectively
        // one by one we can return the cloned node of the input node
    }
};

/*

User: Can you help me to understans this code and dry run the same with diagram

GitHub Copilot: I'll help you understand the code and provide a dry run with a diagram. Let me first read the file. 

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week3/133.%20Clone%20Graph.cpp)

Perfect! Now I'll explain this code and provide a dry run with a visual diagram.

## Code Explanation

This is a **Clone Graph** problem solution using **BFS (Breadth-First Search)**. The goal is to create a deep copy of a graph.

**Key Components:**

1. **Node Structure**: Represents a graph node with:
   - `val`: Integer value
   - `neighbour`: Vector of pointers to adjacent nodes

2. **cloneGraph() Function**: Creates a deep copy using BFS
   - **HashMap (`mp`)**: Maps original nodes → cloned nodes
   - **Queue (`q`)**: Stores nodes to be processed
   - **Algorithm**: 
     - Mark original node as visited by creating a clone
     - Process each node's neighbors
     - Create clones for unvisited neighbors
     - Build edges in the cloned graph

---

## Dry Run with Diagram

Let's trace through an example graph:

```
Original Graph:
    1 ←→ 2
    ↕   ↕
    4 ←→ 3
```

**Step-by-step execution:**

```
Initial State:
┌─────────────────────────────────────┐
│ Queue: [1]                          │
│ HashMap: {1 → Clone(1)}             │
└─────────────────────────────────────┘

Step 1: Process Node 1
┌──────────────────────────────────────┐
│ Current: 1, Neighbors: [2, 4]        │
│ - Visit 2: Create Clone(2), push to Q │
│ - Visit 4: Create Clone(4), push to Q │
│ Queue: [2, 4]                        │
│ Map: {1→Clone(1), 2→Clone(2),        │
│       4→Clone(4)}                    │
│ Clone(1).neighbours: [Clone(2),      │
│                       Clone(4)]       │
└──────────────────────────────────────┘

Step 2: Process Node 2
┌──────────────────────────────────────┐
│ Current: 2, Neighbors: [1, 3]        │
│ - 1: Already visited, just connect   │
│ - 3: Create Clone(3), push to Q      │
│ Queue: [4, 3]                        │
│ Map: {1→C1, 2→C2, 4→C4, 3→C3}       │
│ Clone(2).neighbours: [Clone(1),      │
│                       Clone(3)]       │
└──────────────────────────────────────┘

Step 3: Process Node 4
┌──────────────────────────────────────┐
│ Current: 4, Neighbors: [1, 3]        │
│ - Both already visited, just connect │
│ Queue: [3]                           │
│ Clone(4).neighbours: [Clone(1),      │
│                       Clone(3)]       │
└──────────────────────────────────────┘

Step 4: Process Node 3
┌──────────────────────────────────────┐
│ Current: 3, Neighbors: [2, 4]        │
│ - Both already visited, just connect │
│ Queue: []                            │
│ Clone(3).neighbours: [Clone(2),      │
│                       Clone(4)]       │
└──────────────────────────────────────┘

Final Cloned Graph:
    C1 ←→ C2
    ↕   ↕
    C4 ←→ C3
```

**Time Complexity**: $O(V + E)$ - Visit each node and edge once  
**Space Complexity**: $O(V)$ - HashMap and Queue storage

The algorithm ensures that each node is cloned exactly once and all edges are properly recreated in the cloned graph!

*/