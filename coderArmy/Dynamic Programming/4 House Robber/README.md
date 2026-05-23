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
    /* why i-2? Because we cannot rob adjacent houses example: if we rob house i, we cannot rob house i-1, so we move to i-2 input {
     "i": 4,
     "nums": [2,7,9,3,1],
     "dp": [-1, -1, -1, -1, -1]
    }
    output: 10
    How we get 10?
    - If we rob house 4 (1), we cannot rob house 3 (3), so we move to house 2 (9) and rob it. Total = 1 + 9 = 10
    but index 1 (7) is greater than index 2 (9) so we skip house 4 and rob house 3 (3) and then we can rob house 1 (7) Total = 3 + 7 = 10
    }
    what is nums[i] + solve(i-2, nums, dp) means?
    - nums[i] is the amount of money in the current house we are considering to rob
    */
    int skip = solve(i-1, nums, dp); // skip current house and move to previous house/ what is the value of i-1?
    /* why i-1? Because if we skip current house, we can consider robbing the previous house. So we move to i-1 input {
     "i": 4,
     "nums": [2,7,9,3,1],
     "dp": [-1, -1, -1, -1, -1]
    }
    */
    return dp[i] = max(rob, skip);
}

int robTD(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, -1);
    return solve(n-1, nums, dp); // why n-1? Because we start from the last house and move backwards to the first house. So we call solve with index n-1 which is the last house. Can we start from index 0? No, because we need to consider the option of robbing the last house and skipping the first house. If we start from index 0, we will not be able to consider that option. So we start from index n-1 and move backwards to index 0.
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