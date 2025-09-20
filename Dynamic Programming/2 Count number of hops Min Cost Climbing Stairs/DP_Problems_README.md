# Dynamic Programming Problems - README

This document explains two important **Dynamic Programming problems**
step by step with **Top Down (Memoization)** and **Bottom Up
(Tabulation)** approaches.\
We also discuss **time and space complexity**.

------------------------------------------------------------------------

# 🟢 Problem 1: Number of Hops

You are at the bottom of a staircase with `n` steps. You can hop **1, 2,
or 3 steps** at a time.\
Find the number of ways to reach the `n`th step.

------------------------------------------------------------------------

## 🔹 Approach 1: Top Down (Memoization)

We solve recursively but use **dp\[\]** to remember results.

### Code (C++):

``` cpp
#include <bits/stdc++.h>
using namespace std;

int countWays(int n, vector<int>& dp) {
    if (n == 0) return 1;  // 1 way (stay at ground)
    if (n < 0) return 0;   // no way for negative steps

    if (dp[n] != -1) return dp[n];

    return dp[n] = countWays(n-1, dp) + countWays(n-2, dp) + countWays(n-3, dp);
}

int main() {
    int n = 5;
    vector<int> dp(n+1, -1);
    cout << "Number of ways = " << countWays(n, dp) << endl;
    return 0;
}
```

### Complexity:

-   **Time:** O(n)\
-   **Space:** O(n) (dp array + recursion stack)

------------------------------------------------------------------------

## 🔹 Approach 2: Bottom Up (Tabulation)

We iteratively compute the number of ways.

### Code (C++):

``` cpp
#include <bits/stdc++.h>
using namespace std;

int countWaysBU(int n) {
    vector<int> dp(n+1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        dp[i] += dp[i-1];
        if (i-2 >= 0) dp[i] += dp[i-2];
        if (i-3 >= 0) dp[i] += dp[i-3];
    }
    return dp[n];
}

int main() {
    int n = 5;
    cout << "Number of ways = " << countWaysBU(n) << endl;
    return 0;
}
```

### Complexity:

-   **Time:** O(n)\
-   **Space:** O(n)

------------------------------------------------------------------------

## 🔹 Approach 3: Space Optimization

We only need last 3 values.

### Code (C++):

``` cpp
#include <bits/stdc++.h>
using namespace std;

int countWaysOpt(int n) {
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;

    int a = 1, b = 1, c = 2; // dp[0], dp[1], dp[2]
    int curr;

    for (int i = 3; i <= n; i++) {
        curr = a + b + c;
        a = b;
        b = c;
        c = curr;
    }
    return c;
}

int main() {
    int n = 5;
    cout << "Number of ways = " << countWaysOpt(n) << endl;
    return 0;
}
```

### Complexity:

-   **Time:** O(n)\
-   **Space:** O(1)

------------------------------------------------------------------------

# 🟢 Problem 2: Min Cost Climbing Stairs

You are given an array `cost[]`, where `cost[i]` is the cost of step
`i`.\
From step `i`, you can climb **either 1 step or 2 steps**.\
Find the minimum cost to reach the top.

------------------------------------------------------------------------

## 🔹 Approach 1: Top Down (Memoization)

### Code (C++):

``` cpp
#include <bits/stdc++.h>
using namespace std;

int solve(int n, vector<int>& cost, vector<int>& dp) {
    if (n == 0) return cost[0];
    if (n == 1) return cost[1];

    if (dp[n] != -1) return dp[n];

    return dp[n] = cost[n] + min(solve(n-1, cost, dp), solve(n-2, cost, dp));
}

int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    vector<int> dp(n+1, -1);
    return min(solve(n-1, cost, dp), solve(n-2, cost, dp));
}

int main() {
    vector<int> cost = {10, 15, 20};
    cout << "Min Cost = " << minCostClimbingStairs(cost) << endl;
    return 0;
}
```

### Complexity:

-   **Time:** O(n)\
-   **Space:** O(n) (dp + recursion stack)

------------------------------------------------------------------------

## 🔹 Approach 2: Bottom Up (Tabulation)

### Code (C++):

``` cpp
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
```

### Complexity:

-   **Time:** O(n)\
-   **Space:** O(n)

------------------------------------------------------------------------

## 🔹 Approach 3: Space Optimization

### Code (C++):

``` cpp
#include <bits/stdc++.h>
using namespace std;

int minCostClimbingStairsOpt(vector<int>& cost) {
    int n = cost.size();
    int prev2 = cost[0];
    int prev1 = cost[1];

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
```

### Complexity:

-   **Time:** O(n)\
-   **Space:** O(1)

------------------------------------------------------------------------

# 📌 Final Note

-   **Number of Hops** → Variations of Fibonacci (1, 2, or 3 steps).\
-   **Min Cost Climbing Stairs** → Uses DP to minimize path cost.\
-   Learn **Top Down first**, then **Bottom Up**, then **Space
    Optimization**.\
-   Both problems are **classic DP building blocks**.
