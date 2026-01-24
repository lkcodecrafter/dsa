# Fibonacci Series - Dynamic Programming Approaches

This README explains **different approaches** to solve the Fibonacci
problem using **Dynamic Programming (DP)**.\
We will go step by step from naive recursion to optimized DP solutions.

------------------------------------------------------------------------

## 🟢 1. Recursion (Naive Approach)

The Fibonacci sequence is defined as: - F(0) = 0 - F(1) = 1 - F(n) =
F(n-1) + F(n-2), for n \> 1

### Code (C++):

``` cpp
#include <bits/stdc++.h>
using namespace std;

int fib(int n) {
    if (n <= 1) return n; // base case
    return fib(n-1) + fib(n-2);
}

int main() {
    int n = 10;
    cout << "Fibonacci(" << n << ") = " << fib(n) << endl;
    return 0;
}
```

### ⏱️ Time Complexity:

-   **O(2\^n)** (because it recomputes many values).\
    \### 💾 Space Complexity:
-   **O(n)** (due to recursion stack).

------------------------------------------------------------------------

## 🟢 2. Top Down (Memoization)

We use a **dp\[\] array** to remember already computed results.\
This avoids recalculating the same Fibonacci numbers.

### Code (C++):

``` cpp
#include <bits/stdc++.h>
using namespace std;

int fibMemo(int n, vector<int>& dp) {
    if (n <= 1) return n;
    if (dp[n] != -1) return dp[n]; // return if already computed

    return dp[n] = fibMemo(n-1, dp) + fibMemo(n-2, dp);
}

int main() {
    int n = 10;
    vector<int> dp(n+1, -1);
    cout << "Fibonacci(" << n << ") = " << fibMemo(n, dp) << endl;
    return 0;
}
```

### ⏱️ Time Complexity:

-   **O(n)** (each value computed once).\
    \### 💾 Space Complexity:
-   **O(n)** (dp array + recursion stack).

------------------------------------------------------------------------

## 🟢 3. Bottom Up (Tabulation)

Instead of recursion, we build the solution iteratively from the base
cases.

### Code (C++):

``` cpp
#include <bits/stdc++.h>
using namespace std;

int fibTab(int n) {
    vector<int> dp(n+1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

int main() {
    int n = 10;
    cout << "Fibonacci(" << n << ") = " << fibTab(n) << endl;
    return 0;
}
```

### ⏱️ Time Complexity:

-   **O(n)** (single loop).\
    \### 💾 Space Complexity:
-   **O(n)** (dp array).

------------------------------------------------------------------------

## 🟢 4. Space Optimization

We don't need the entire dp\[\] array, just the last two values.

### Code (C++):

``` cpp
#include <bits/stdc++.h>
using namespace std;

int fibSpaceOpt(int n) {
    if (n <= 1) return n;

    int prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main() {
    int n = 10;
    cout << "Fibonacci(" << n << ") = " << fibSpaceOpt(n) << endl;
    return 0;
}
```

### ⏱️ Time Complexity:

-   **O(n)** (single loop).\
    \### 💾 Space Complexity:
-   **O(1)** (only 2 variables).

------------------------------------------------------------------------

## 📌 Final Note

-   **Recursion** is simple but inefficient.\
-   **Memoization (Top Down)** improves recursion by storing results.\
-   **Tabulation (Bottom Up)** is iterative and avoids recursion.\
-   **Space Optimization** is the most efficient version, reducing
    memory use.

👉 Always start learning DP with **Fibonacci**, as it's the foundation
for harder problems!