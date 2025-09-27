# 🏠 Dynamic Programming - House Robber Problems

This README covers two classic **Dynamic Programming** problems:

1. **House Robber I** (Linear Street)  
2. **House Robber II** (Circular Street)  

We’ll solve them using **Top Down (Memoization)** and **Bottom Up (Tabulation)** approaches.

---

## 🟢 Problem 1: House Robber I

You are a robber planning to rob houses along a street.  
Each house has some money, represented by `nums[i]`.  

**Constraint:**  
- You cannot rob two adjacent houses (police alert 🚨).  

**Goal:** Maximize the total amount you can rob.

---

### 🔹 Approach 1: Top Down (Memoization)

We decide for each house: **rob it** or **skip it**.

Recurrence:  
f(i) = max(nums[i] + f(i-2), f(i-1))


### Code (C++):
```cpp
#include <bits/stdc++.h>
using namespace std;

int solve(int i, vector<int>& nums, vector<int>& dp) {
    if (i < 0) return 0;
    if (dp[i] != -1) return dp[i];

    int rob = nums[i] + solve(i-2, nums, dp);
    int skip = solve(i-1, nums, dp);

    return dp[i] = max(rob, skip);
}

int robTD(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, -1);
    return solve(n-1, nums, dp);
}

int main() {
    vector<int> nums = {2,7,9,3,1};
    cout << "Max Rob = " << robTD(nums) << endl;
    return 0;
}

⏱ Time: O(n)
💾 Space: O(n) (dp + recursion stack)


🔹 Approach 2: Bottom Up (Tabulation)

We fill dp iteratively.

#include <bits/stdc++.h>
using namespace std;

int robBU(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i-1], nums[i] + dp[i-2]);
    }
    return dp[n-1];
}

int main() {
    vector<int> nums = {2,7,9,3,1};
    cout << "Max Rob = " << robBU(nums) << endl;
    return 0;
}
 

⏱ Time: O(n)
💾 Space: O(n)

🔹 Space Optimized Version

We only need last two values.


#include <bits/stdc++.h>
using namespace std;

int robOpt(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];

    int prev2 = nums[0];
    int prev1 = max(nums[0], nums[1]);

    for (int i = 2; i < n; i++) {
        int curr = max(prev1, nums[i] + prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int main() {
    vector<int> nums = {2,7,9,3,1};
    cout << "Max Rob = " << robOpt(nums) << endl;
    return 0;
}


⏱ Time: O(n)
💾 Space: O(1)

🟢 Problem 2: House Robber II

Now the houses are arranged in a circle.
This means first and last houses are adjacent.

So, we cannot rob both first and last.

Idea:

Case 1: Rob houses from index 0 to n-2

Case 2: Rob houses from index 1 to n-1

Answer = max(case1, case2)

#include <bits/stdc++.h>
using namespace std;

int robLinear(vector<int>& nums, int start, int end) {
    int prev2 = 0, prev1 = 0;
    for (int i = start; i <= end; i++) {
        int curr = max(prev1, nums[i] + prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int robII(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];

    // Case 1: Exclude last
    int case1 = robLinear(nums, 0, n-2);
    // Case 2: Exclude first
    int case2 = robLinear(nums, 1, n-1);

    return max(case1, case2);
}

int main() {
    vector<int> nums = {2,3,2};
    cout << "Max Rob = " << robII(nums) << endl;
    return 0;
}


⏱ Time: O(n)
💾 Space: O(1)

📌 Final Note

House Robber I is a linear DP problem.

House Robber II adds the twist of a circular arrangement.

Both problems are excellent to practice choice-based DP (rob or skip).

Learn recursion ➝ memoization ➝ tabulation ➝ optimization flow.