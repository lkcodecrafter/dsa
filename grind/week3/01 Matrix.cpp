#include<iostream>
#include<vector>
#include<queue>
using namespace std;


// https://www.youtube.com/watch?v=XXaVIDIbUn4


class Solution {
public:

   vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        queue<pair<int, int>> q;
        vector<vector<int>>result(m,vector<int>(n, INT_MAX - 100000));
        for(int i =0;i<m;i++){
            for(int j=0;j<n;j++){
                if(mat[i][j]==0){
                    result[i][j]=0;
                    q.push({i,j});
                }
            }
        }
        vector<vector<int>>dir = {{0,1}, {0,-1},{1,0},{-1,0}};
        while(!q.empty()){
            auto[i,j]=q.front();
            q.pop();

            for(auto d : dir){
                int ni = i+ d[0];
                int nj = j+ d[1];

                if(ni >= 0 &&  ni < m &&  nj >=0 &&  nj < n && result[ni][nj] > result[i][j]+1){
                    result[ni][nj]=result[i][j]+1;
                    q.push({ni,nj});
                }
            }

        }
        return result;
    }
};

/*
Your thinking

1. We will use BFS to solve this problem since it is well-suited for finding the shortest path in an unweighted grid.
2. First, we will initialize a distance matrix with maximum integer values to represent unvisited cells.
3. We will then enqueue all the positions of 0s in the input matrix and set their corresponding distances to 0 in the distance matrix.
4. Next, we will perform BFS by dequeuing a cell, checking its four neighbors (up, down, left, right), and updating their distances if we find a shorter path through the current cell.
5. Finally, we will return the updated distance matrix.


# 01 Matrix — Multi-Source BFS (Explanation + Dry Run)

This README explains **how the code works** and walks through a **dry run** step by step.

---

## 🧠 Problem Summary

Given a matrix `mat` containing only `0`s and `1`s, return a matrix where each cell contains the **distance to the nearest `0`**.

Distance is measured using **4-directional moves** (up, down, left, right).

---

## 💡 Key Idea: Multi-Source BFS

- Every `0` is a **source**
- Start BFS from **all zeros at once**
- Expand outward level by level
- The first time a cell is reached → **shortest distance**

This works because all edges have equal weight (1 step).

---

## 📌 Data Structures Used

| Structure | Purpose |
|---------|---------|
| `queue<pair<int,int>>` | BFS traversal |
| `result[m][n]` | Stores minimum distance to nearest `0` |
| `dir` | Direction vectors for neighbors |

---

## 🧩 Code Breakdown

### 1️⃣ Initialization

```cpp
vector<vector<int>> result(m, vector<int>(n, INT_MAX - 100000));


Initialize all distances to a very large number

Prevents overflow when adding +1

2️⃣ Push All 0s into Queue
if (mat[i][j] == 0) {
    result[i][j] = 0;
    q.push({i, j});
}


Every 0 starts with distance 0

All are added to the BFS queue (multi-source)

3️⃣ BFS Traversal
while (!q.empty()) {
    auto [i, j] = q.front();
    q.pop();


Standard BFS loop

Process cells in increasing distance order

4️⃣ Explore Neighbors
if (result[ni][nj] > result[i][j] + 1) {
    result[ni][nj] = result[i][j] + 1;
    q.push({ni, nj});
}


If a shorter distance is found

Update and push neighbor into queue

🔍 Why This Condition Works
result[ni][nj] > result[i][j] + 1


Ensures we only update when a shorter path is found

Guarantees minimum distance

🧪 Dry Run Example
Input Matrix
mat =
[
  [0, 0, 0],
  [0, 1, 0],
  [1, 1, 1]
]

Step 1: Initial State
result =
[
  [0, 0, 0],
  [0, ∞, 0],
  [∞, ∞, ∞]
]

how ∞ is represented: INT_MAX - 100000 (for example 2147483647 - 100000 = 2147383647 means ∞)

queue = {(0,0), (0,1), (0,2), (1,0), (1,2)}

Why started from (1,0) and (1,2) → because they are 0s in the input matrix
but (0,0), (0,1), (0,2) are also 0s in the input matrix so they are also in the queue initially.

Step 2: BFS Expansion

From (1,0) → update (2,0) → distance 1

From (1,2) → update (2,2) → distance 1

From (0,1) → update (1,1) → distance 1

result =
[
  [0, 0, 0],
  [0, 1, 0],
  [1, ∞, 1]
]

Step 3: Next Level

From (1,1) → update (2,1) → distance 2

result =
[
  [0, 0, 0],
  [0, 1, 0],
  [1, 2, 1]
]

Step 4: BFS Ends

Queue is empty → all distances found

✅ Final Output
[
  [0, 0, 0],
  [0, 1, 0],
  [1, 2, 1]
]

⏱️ Complexity Analysis
Metric	Value
Time	O(m × n)
Space	O(m × n)

Each cell is processed at most once.


Help me to understand this condition better:
if (dist[ni][nj] > dist[i][j] + 1) 
    dist[ni][nj] = dist[i][j] + 1;
    q.push({ni, nj});
}
This condition checks if the current known distance to the 
neighbor cell (ni, nj) is greater than the distance to the current cell (i, j) 
plus one step. If it is, we have found a shorter path to (ni, nj) through (i, j), 
so we update its distance and add it to the queue for further exploration. 
This ensures that we always maintain the shortest distance to each cell as we perform BFS.

for example:if (dist[ni][nj] > dist[i][j] + 1) 
    dist[ni][nj] = dist[i][j] + 1;
    Dry run example:
Consider the following matrix:
[
  [0, 0, 0],
  [0, 1, 0],
  [1, 1, 1]
]
From (1,0) → update (2,0) → distance 1
From (1,2) → update (2,2) → distance 1
From (0,1) → update (1,1) → distance 1


*/