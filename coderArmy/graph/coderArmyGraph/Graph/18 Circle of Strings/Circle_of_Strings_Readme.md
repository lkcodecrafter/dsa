# Circle of Strings Problem

## 📌 Problem Link
- [Circle of Strings - GFG](https://www.geeksforgeeks.org/problem...)

---

## 📖 Problem Statement
Given an array of strings, determine whether all strings can be chained together to form a circle.  
- A string `A` can be chained to string `B` if the **last character of A = first character of B**.  
- The task is to check if all strings can be arranged in such a way that they form a **circle**.

---

## 🧠 Key Idea
This problem is equivalent to finding whether an **Eulerian Circuit** exists in a **directed graph**:
1. Each **character (a–z)** is a vertex.  
2. Each **string** represents a directed edge from its **first character → last character**.  
3. The graph should have:
   - **In-degree = Out-degree** for every vertex.  
   - The graph must be **strongly connected** (ignoring isolated vertices).  

---

## 💻 C++ Code Implementation

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // DFS for checking connectivity
    void dfs(int node, vector<vector<int>>& adj, vector<bool>& vis) {
        vis[node] = true;
        for (int neigh : adj[node]) {
            if (!vis[neigh]) dfs(neigh, adj, vis);
        }
    }

    bool isCircle(vector<string>& arr) {
        vector<int> in(26, 0), out(26, 0);
        vector<vector<int>> adj(26);

        // Build graph
        for (string s : arr) {
            int u = s.front() - 'a';
            int v = s.back() - 'a';
            out[u]++;
            in[v]++;
            adj[u].push_back(v);
        }

        // Step 1: Check in-degree == out-degree
        for (int i = 0; i < 26; i++) {
            if (in[i] != out[i]) return false;
        }

        // Step 2: Check Strong Connectivity
        vector<bool> vis(26, false);
        int start = -1;
        for (int i = 0; i < 26; i++) {
            if (out[i] > 0) { start = i; break; }
        }
        if (start == -1) return true; // No edges

        dfs(start, adj, vis);

        for (int i = 0; i < 26; i++) {
            if ((in[i] > 0 || out[i] > 0) && !vis[i]) return false;
        }

        return true;
    }
};

int main() {
    int n;
    cin >> n;
    vector<string> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    Solution sol;
    if (sol.isCircle(arr)) cout << "Yes" << endl;
    else cout << "No" << endl;

    return 0;
}

⏱️ Time & Space Complexity

Time Complexity: O(N + 26) ≈ O(N) (where N = number of strings)

Space Complexity: O(26 + N) for adjacency list and degree arrays

🌍 Real-Life Applications

Word games (like forming circular chains).

DNA sequencing problems where overlapping fragments must form a cycle.

String chaining puzzles.

📌 Last Note

This problem is directly linked to Eulerian Circuit in directed graphs.

Always check in-degree = out-degree and strong connectivity to confirm circle existence.