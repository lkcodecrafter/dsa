# Dynamic Programming (DP) - Fibonacci Example

## 📖 Introduction

This document explains **Dynamic Programming (DP)** using the
**Fibonacci Series** as an example.\
We will cover: - Recursion (Naive Approach) - Top-Down Approach
(Memoization) - Bottom-Up Approach (Tabulation) - Space Optimization

------------------------------------------------------------------------

## 🧩 00:52 Understanding Dynamic Programming

Dynamic Programming (DP) is a technique to solve problems by breaking
them into smaller overlapping subproblems and storing their results to
avoid redundant calculations.

Key ideas: 1. **Optimal Substructure** → Problem can be broken into
smaller subproblems. 2. **Overlapping Subproblems** → Same subproblems
are solved multiple times.

------------------------------------------------------------------------

## 🔢 4:23 Fibonacci Example with Recursion & Top-Down Approach

### Recursion (Naive)

``` cpp
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
```

⛔ Time Complexity: `O(2^n)` (Exponential)\
⛔ Space Complexity: `O(n)` (due to recursion stack)

------------------------------------------------------------------------

### Top-Down (Memoization)

``` cpp
int fibMemo(int n, vector<int> &dp) {
    if (n <= 1) return n;
    if (dp[n] != -1) return dp[n];
    return dp[n] = fibMemo(n-1, dp) + fibMemo(n-2, dp);
}

int main() {
    int n = 10;
    vector<int> dp(n+1, -1);
    cout << fibMemo(n, dp);
}
```

✅ Time Complexity: `O(n)`\
✅ Space Complexity: `O(n)`

------------------------------------------------------------------------

## 🧮 44:00 Bottom-Up Approach (Tabulation)

``` cpp
int fibBottomUp(int n) {
    vector<int> dp(n+1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}
```

✅ Time Complexity: `O(n)`\
✅ Space Complexity: `O(n)`

------------------------------------------------------------------------

## ⚡ 56:56 Space Optimization

Instead of storing all states, just store the last two values.

``` cpp
int fibSpaceOptimized(int n) {
    if (n <= 1) return n;
    int prev1 = 1, prev2 = 0;
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}
```

✅ Time Complexity: `O(n)`\
✅ Space Complexity: `O(1)`

------------------------------------------------------------------------

## 📝 1:04:25 Last Note

-   DP avoids recomputation by storing solutions.\
-   Fibonacci is the simplest DP example.\
-   Always look for **overlapping subproblems** + **optimal
    substructure**.

------------------------------------------------------------------------

🚀 Congratulations! You now understand **Recursion, Memoization,
Tabulation, and Space Optimization** using the Fibonacci problem.
