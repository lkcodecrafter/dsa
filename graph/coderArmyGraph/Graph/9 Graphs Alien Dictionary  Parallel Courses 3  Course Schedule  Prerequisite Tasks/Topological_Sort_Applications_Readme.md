# Graph Problems - Topological Sort Applications

This README contains explanations and C++ implementations of problems based on **Topological Sort** and its applications.

---

## 📌 Problems Covered

1. **Prerequisite Tasks**  
   - Problem link: [GFG - Prerequisite Tasks](https://practice.geeksforgeeks.org/problems/prerequisite-tasks/1)  
   - Concept: Use **Kahn’s Algorithm (BFS)** to check if all tasks can be completed.

2. **Course Schedule**  
   - Problem link: [LeetCode - Course Schedule](https://leetcode.com/problems/course-schedule/)  
   - Concept: Detect cycles in a directed graph using BFS (Topological Sort).

3. **Alien Dictionary**  
   - Problem link: [GFG - Alien Dictionary](https://practice.geeksforgeeks.org/problems/alien-dictionary/1)  
   - Concept: Build graph from given words and perform Topological Sort to determine lexicographical order.

4. **Parallel Courses**  
   - Problem link: [LeetCode - Parallel Courses](https://leetcode.com/problems/parallel-courses/)  
   - Concept: Use BFS + levels to find the minimum number of semesters.

---

## 🧑‍💻 Problem 1: Prerequisite Tasks

### Approach
- Model tasks as nodes and prerequisites as edges.
- Use **Kahn’s Algorithm** for Topological Sort.
- If we can process all nodes → possible, else impossible.

### C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

bool isPossible(int N, vector<pair<int, int>> &prereq) {
    vector<int> indegree(N, 0);
    vector<vector<int>> adj(N);
    for (auto &p : prereq) {
        adj[p.first].push_back(p.second);
        indegree[p.second]++;
    }

    queue<int> q;
    for (int i = 0; i < N; i++) 
        if (indegree[i] == 0) q.push(i);

    int count = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        count++;
        for (auto v : adj[u]) {
            if (--indegree[v] == 0) q.push(v);
        }
    }
    return count == N;
}

int main() {
    int N = 4, P = 3;
    vector<pair<int,int>> prereq = {{0,1},{1,2},{2,3}};
    cout << (isPossible(N, prereq) ? "Yes" : "No") << endl;
}
```

### Complexity
- **Time**: `O(V + E)`  
- **Space**: `O(V + E)`  

---

## 🧑‍💻 Problem 2: Course Schedule

(Similar to above but direct LeetCode statement)  

```cpp
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> adj(numCourses);
        for (auto &p : prerequisites) {
            adj[p[1]].push_back(p[0]);
            indegree[p[0]]++;
        }
        queue<int> q;
        for (int i = 0; i < numCourses; i++) 
            if (indegree[i] == 0) q.push(i);
        
        int count = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            count++;
            for (auto v : adj[u]) {
                if (--indegree[v] == 0) q.push(v);
            }
        }
        return count == numCourses;
    }
};
```

---

## 🧑‍💻 Problem 3: Alien Dictionary

### Approach
- Compare adjacent words.
- First differing characters give directed edge.
- Perform Topological Sort.

```cpp
class Solution {
public:
    string findOrder(string dict[], int N, int K) {
        vector<vector<int>> adj(K);
        vector<int> indegree(K, 0);

        for (int i = 0; i < N-1; i++) {
            string w1 = dict[i], w2 = dict[i+1];
            int len = min(w1.size(), w2.size());
            for (int j = 0; j < len; j++) {
                if (w1[j] != w2[j]) {
                    adj[w1[j]-'a'].push_back(w2[j]-'a');
                    indegree[w2[j]-'a']++;
                    break;
                }
            }
        }

        queue<int> q;
        for (int i = 0; i < K; i++) if (indegree[i] == 0) q.push(i);

        string ans = "";
        while (!q.empty()) {
            int u = q.front(); q.pop();
            ans += char('a' + u);
            for (auto v : adj[u]) {
                if (--indegree[v] == 0) q.push(v);
            }
        }
        return ans;
    }
};
```

---

## 🧑‍💻 Problem 4: Parallel Courses

```cpp
class Solution {
public:
    int minimumSemesters(int N, vector<vector<int>>& relations) {
        vector<int> indegree(N+1, 0);
        vector<vector<int>> adj(N+1);
        for (auto &r : relations) {
            adj[r[0]].push_back(r[1]);
            indegree[r[1]]++;
        }

        queue<int> q;
        for (int i = 1; i <= N; i++) 
            if (indegree[i] == 0) q.push(i);

        int semester = 0, count = 0;
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                int u = q.front(); q.pop();
                count++;
                for (auto v : adj[u]) {
                    if (--indegree[v] == 0) q.push(v);
                }
            }
            semester++;
        }
        return count == N ? semester : -1;
    }
};
```

### Complexity
- **Time**: `O(V + E)`  
- **Space**: `O(V + E)`  

---

## 📚 Homework
1. [Parallel Courses II](https://leetcode.com/problems/parallel-courses-ii/)  
2. [Course Schedule IV](https://leetcode.com/problems/course-schedule-iv/)  

---

## 📝 Last Note
These problems are based on **Topological Sorting**.  
Mastering them builds strong intuition for solving **dependency-related graph problems**.

