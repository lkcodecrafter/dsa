# Climbing Stairs - Dynamic Programming

This README explains the **Climbing Stairs problem** using different approaches:  
1. **Method 1: Count Ways to Climb Stairs**  
2. **Method 2: Min Cost Climbing Stairs (variation)**  

Each method is explained with **Top Down (Memoization)** and **Bottom Up (Tabulation)** approaches, along with **time/space complexities**.

---

# 🟢 Method 1: Count Ways to Climb Stairs

You are climbing a staircase with `n` steps. Each time, you can climb **1 or 2 steps**.  
Find the total number of distinct ways to climb to the top.

---

## 🔹 Approach 1: Top Down (Memoization)

We use recursion and memoization.

### Code (C++):
```cpp
#include <bits/stdc++.h>
using namespace std;

int climbStairsTD(int n, vector<int>& dp) {
    if (n <= 2) return n; // base cases
    if (dp[n] != -1) return dp[n];

    return dp[n] = climbStairsTD(n-1, dp) + climbStairsTD(n-2, dp);
}

int main() {
    int n = 5;
    vector<int> dp(n+1, -1);
    cout << "Ways = " << climbStairsTD(n, dp) << endl;
    return 0;
}
Complexity:
Time: O(n)

Space: O(n) (dp + recursion stack)

🔹 Approach 2: Bottom Up (Tabulation)
We build iteratively.

Code (C++):
cpp
Copy code
#include <bits/stdc++.h>
using namespace std;

int climbStairsBU(int n) {
    if (n <= 2) return n;

    vector<int> dp(n+1);
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

int main() {
    int n = 5;
    cout << "Ways = " << climbStairsBU(n) << endl;
    return 0;
}
Complexity:
Time: O(n)

Space: O(n)

🔹 Space Optimized
We only need last 2 values.

Code (C++):
cpp
Copy code
#include <bits/stdc++.h>
using namespace std;

int climbStairsOpt(int n) {
    if (n <= 2) return n;

    int prev1 = 2, prev2 = 1;
    for (int i = 3; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main() {
    int n = 5;
    cout << "Ways = " << climbStairsOpt(n) << endl;
    return 0;
}
Complexity:
Time: O(n)

Space: O(1)

🟢 Method 2: Min Cost Climbing Stairs (Variation)
Each step has a cost. You can climb 1 or 2 steps at a time.
Find the minimum cost to reach the top.

🔹 Approach 1: Top Down (Memoization)
Code (C++):
cpp
Copy code
#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int>& cost, vector<int>& dp) {
    if (n == 0) return cost[0];
    if (n == 1) return cost[1];
    if (dp[n] != -1) return dp[n];

    return dp[n] = cost[n] + min(solve(n-1, cost, dp), solve(n-2, cost, dp));
}

int minCostClimbingStairsTD(vector<int>& cost) {
    int n = cost.size();
    vector<int> dp(n+1, -1);
    return min(solve(n-1, cost, dp), solve(n-2, cost, dp));
}

int main() {
    vector<int> cost = {10, 15, 20};
    cout << "Min Cost = " << minCostClimbingStairsTD(cost) << endl;
    return 0;
}
Complexity:
Time: O(n)

Space: O(n)

🔹 Approach 2: Bottom Up (Tabulation)
Code (C++):
cpp
Copy code
#include <bits/stdc++.h>
using namespace std;

int minCostClimbingStairsBU(vector<int>& cost) {
    int n = cost.size();
    vector<int> dp(n);
    dp[0] = cost[0];
    dp[1] = cost[1];

    for (int i = 2; i < n; i++) {
        dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
    }
    return min(dp[n-1], dp[n-2]);
}

int main() {
    vector<int> cost = {10, 15, 20};
    cout << "Min Cost = " << minCostClimbingStairsBU(cost) << endl;
    return 0;
}
Complexity:
Time: O(n)

Space: O(n)

🔹 Space Optimized
Code (C++):
cpp
Copy code
#include <bits/stdc++.h>
using namespace std;

int minCostClimbingStairsOpt(vector<int>& cost) {
    int n = cost.size();
    int prev2 = cost[0], prev1 = cost[1];

    for (int i = 2; i < n; i++) {
        int curr = cost[i] + min(prev1, prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return min(prev1, prev2);
}

int main() {
    vector<int> cost = {10, 15, 20};
    cout << "Min Cost = " << minCostClimbingStairsOpt(cost) << endl;
    return 0;
}
Complexity:
Time: O(n)

Space: O(1)

📌 Final Note
Method 1: Count number of ways (like Fibonacci).

Method 2: Minimize total cost (classic DP).

Start with recursion, move to memoization, then tabulation, and finally optimize space.

These problems build a strong foundation for Dynamic Programming.