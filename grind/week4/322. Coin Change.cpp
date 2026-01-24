#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:

    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        return dp[amount] == amount + 1 ? -1 : dp[amount];
    }

};


/*


User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily.

GitHub Copilot: I'll read the code and provide a detailed explanation with a visual dry run. 

Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week4/322.%20Coin%20Change.cpp)

Perfect! Let me explain this code and walk you through a dry run.

## Code Explanation

This is a **Coin Change Problem** using **Dynamic Programming**. It finds the **minimum number of coins** 
needed to make a given amount.

**Algorithm Breakdown:**

1. **DP Array**: `dp[i]` = minimum coins needed to make amount `i`
2. **Base Case**: `dp[0] = 0` (0 coins for amount 0)
3. **Initialization**: Fill with `amount + 1` (represents infinity)
4. **Transition**: For each amount, try all coins and pick the minimum

---

## Dry Run with Visualization

**Example**: `coins = [1, 2, 5]`, `amount = 5`

### Initial State:
```
dp array initialized with (amount + 1 = 6) as "infinity"
Index:  0  1  2  3  4  5
dp:    [0, 6, 6, 6, 6, 6]
         ↑
      base case (0 coins for 0 amount)
```

### Processing Each Amount:

```
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
i = 1 (Making amount 1):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Coins available: [1, 2, 5]
├─ coin=1: 1-1=0 ✓ → dp[1] = min(6, dp[0]+1) = min(6, 1) = 1
├─ coin=2: 1-2=-1 ✗ (negative, skip)
└─ coin=5: 1-5=-4 ✗ (negative, skip)

Result: dp[1] = 1  (use 1 coin: [1])
Index:  0  1  2  3  4  5
dp:    [0, 1, 6, 6, 6, 6]

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
i = 2 (Making amount 2):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
├─ coin=1: dp[2] = min(6, dp[1]+1) = min(6, 2) = 2
├─ coin=2: dp[2] = min(2, dp[0]+1) = min(2, 1) = 1  ✓✓✓
└─ coin=5: 2-5 ✗

Result: dp[2] = 1  (use 1 coin: [2])
Index:  0  1  2  3  4  5
dp:    [0, 1, 1, 6, 6, 6]

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
i = 3 (Making amount 3):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
├─ coin=1: dp[3] = min(6, dp[2]+1) = min(6, 2) = 2
├─ coin=2: dp[3] = min(2, dp[1]+1) = min(2, 2) = 2
└─ coin=5: 3-5 ✗

Result: dp[3] = 2  (use 2 coins: [1,2] or [2,1])
Index:  0  1  2  3  4  5
dp:    [0, 1, 1, 2, 6, 6]

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
i = 4 (Making amount 4):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
├─ coin=1: dp[4] = min(6, dp[3]+1) = min(6, 3) = 3
├─ coin=2: dp[4] = min(3, dp[2]+1) = min(3, 2) = 2  ✓✓✓
└─ coin=5: 4-5 ✗

Result: dp[4] = 2  (use 2 coins: [2,2])
Index:  0  1  2  3  4  5
dp:    [0, 1, 1, 2, 2, 6]

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
i = 5 (Making amount 5):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
├─ coin=1: dp[5] = min(6, dp[4]+1) = min(6, 3) = 3
├─ coin=2: dp[5] = min(3, dp[3]+1) = min(3, 3) = 3
└─ coin=5: dp[5] = min(3, dp[0]+1) = min(3, 1) = 1  ✓✓✓

Result: dp[5] = 1  (use 1 coin: [5])
Index:  0  1  2  3  4  5
dp:    [0, 1, 1, 2, 2, 1]
```

### Final Answer:
```
dp[5] = 1
Therefore, minimum coins needed = 1
(Use coin [5])
```

---

## Visual Summary Table

| Amount | Best Coins | Count |
|--------|----------- |-------|
| 0 |           -     |   0   |
| 1 |          [1]    |   1   |
| 2 |          [2]    |   1   |
| 3 |          [1, 2] |   2   |
| 4 |          [2, 2] |   2   |
| 5 |           [5]   | **1** ✓ |

---

## Complexity Analysis

- **Time Complexity**: O(amount * n) where n is the number of coins
- **Space Complexity**: O(amount) for the DP array

This is an optimal bottom-up DP approach that builds solutions from smaller subproblems!

*/