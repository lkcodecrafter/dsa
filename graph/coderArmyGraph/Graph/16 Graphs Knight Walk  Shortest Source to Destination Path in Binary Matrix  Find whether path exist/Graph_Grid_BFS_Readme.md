# Graph Problems on Grids (BFS Applications)

## 📌 Introduction
In this lecture, we solve graph problems that are modeled on **grids or matrices** using **Breadth-First Search (BFS)**.  
These problems are based on finding **shortest paths** or **checking path existence**.

---

## 🧩 Problems Covered

### 🔹 Problem 1: Shortest Source to Destination Path
**Link:** [Shortest Source to Destination Path](https://www.geeksforgeeks.org/problem...)  

- **Statement:** Given a binary matrix (0 = blocked, 1 = open cell), find the shortest path from the **source (0,0)** to a given **destination (X,Y)**.  
- **Approach:**  
  - Use **BFS** because it explores level by level.  
  - Maintain a `visited[][]` array.  
  - Explore **4 possible directions** (up, down, left, right).  

#### 💻 C++ Code
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Cell {
    int x, y, dist;
};

bool isValid(int x, int y, int n, int m, vector<vector<int>>& grid, vector<vector<bool>>& vis) {
    return (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 1 && !vis[x][y]);
}

int shortestPath(vector<vector<int>>& grid, pair<int,int> src, pair<int,int> dest) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    queue<Cell> q;
    q.push({src.first, src.second, 0});
    vis[src.first][src.second] = true;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    while (!q.empty()) {
        Cell cur = q.front(); q.pop();
        if (cur.x == dest.first && cur.y == dest.second)
            return cur.dist;

        for (int k = 0; k < 4; k++) {
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];
            if (isValid(nx, ny, n, m, grid, vis)) {
                vis[nx][ny] = true;
                q.push({nx, ny, cur.dist + 1});
            }
        }
    }
    return -1; // No path exists
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];

    int x, y;
    cin >> x >> y;
    cout << shortestPath(grid, {0,0}, {x,y}) << endl;
    return 0;
}

🔹 Problem 2: Knight Walk

Link: Knight Walk

Statement: Given a chessboard of size N x N, find the minimum number of steps required for a knight to move from source (sx, sy) to destination (dx, dy).

Approach:

Use BFS.

Knight has 8 possible moves.

Stop BFS once destination is reached.

#include <bits/stdc++.h>
using namespace std;

struct Cell {
    int x, y, dist;
};

bool isInside(int x, int y, int N) {
    return (x >= 1 && x <= N && y >= 1 && y <= N);
}

int knightWalk(int N, pair<int,int> src, pair<int,int> dest) {
    vector<vector<bool>> vis(N+1, vector<bool>(N+1, false));
    queue<Cell> q;
    q.push({src.first, src.second, 0});
    vis[src.first][src.second] = true;

    int dx[] = {2, 2, -2, -2, 1, -1, 1, -1};
    int dy[] = {1, -1, 1, -1, 2, 2, -2, -2};

    while (!q.empty()) {
        Cell cur = q.front(); q.pop();
        if (cur.x == dest.first && cur.y == dest.second)
            return cur.dist;

        for (int i = 0; i < 8; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (isInside(nx, ny, N) && !vis[nx][ny]) {
                vis[nx][ny] = true;
                q.push({nx, ny, cur.dist + 1});
            }
        }
    }
    return -1;
}

int main() {
    int N;
    cin >> N;
    int sx, sy, dx, dy;
    cin >> sx >> sy >> dx >> dy;
    cout << knightWalk(N, {sx, sy}, {dx, dy}) << endl;
    return 0;
}

Problem 3: Find Whether Path Exists (Homework)

Link: Find Whether Path Exist

Statement: Given a matrix with source (1) and destination (2), check whether a path exists.

Approach:

Use BFS/DFS.

Treat 3 (valid path) as traversable, 0 as blocked.

Return true if BFS reaches destination.

⏱️ Time & Space Complexity

BFS Traversal: O(N*M) for grid problems.

Space Complexity: O(N*M) due to visited[][] and queue.

🌍 Real-World Applications

Pathfinding in maps and games.

Robotics navigation in grid-based environments.

AI search algorithms.

📌 Last Note

BFS is best for shortest path problems in unweighted grids.

Knight Walk is a classic BFS problem with unique moves.

Path existence problems are a direct application of BFS/DFS.