#include<iostream>
#include<unordered_map>
#include<vector>
#include<unordered_set>
#include<string>
#include<algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, vector<int>> emailToIndices;
        for(int i = 0; i < accounts.size(); i++) {
            for(int j = 1; j < accounts[i].size(); j++) {
                emailToIndices[accounts[i][j]].push_back(i); // Map email to account indices, like {email: [index1, index2, ...]}
                // This helps in finding all accounts that share the same email
                // For example, if "lalit@example.com" appears in accounts 0 and 2, 
                // then emailToIndices["lalit@example.com"] = [0, 2]
            }
        }

        vector<vector<string>> mergedAccounts;
        vector<bool> visited(accounts.size(), false);

        for(int i = 0; i < accounts.size(); i++) {
            if(visited[i]) continue;
            vector<string> mergedAccount;
            mergedAccount.push_back(accounts[i][0]); // Add the account name
            unordered_set<string> emails;
            dfs(accounts, emailToIndices, emails, visited, i);
            for(const string& email : emails) {
                mergedAccount.push_back(email); // Add all unique emails collected from DFS. Example: ["John", "johnsmith@mail.com", "john_newyork@mail.com"]
                // LIke with pushback, we add account name first, then all unique emails found
                // how push_back works here:
                // mergedAccount = ["John"]
                // after loop, mergedAccount = ["John", "johnsmith@mail.com", "john_newyork@mail.com"]
                // account[i][0] is the name, emails are added next
                // we dont' need account[1][1], account[1][2] etc separately because emails set has all unique emails
                // Example: if account 0 has emails A, B and account 1 has emails B, C, after DFS we get {A, B, C} in emails set
                // So we just add all from emails set to mergedAccount
                // This ensures no duplicates and all connected emails are included
            }
            sort(mergedAccount.begin() + 1, mergedAccount.end()); // Sort emails lexicographically, skipping the name at index 0
            // Example: ["John", "john_newyork@mail.com", "johnsmith@mail.com"]
            // Sorting helps in consistent output format
            // why begin()+1? because we want to sort only emails, not the name at index 0
            // ok every 0 index we have name, from index 1 to end we have emails
            mergedAccounts.push_back(mergedAccount);
        }

        return mergedAccounts;
    }

private:
    void dfs(vector<vector<string>>& accounts, unordered_map<string, vector<int>>& emailToIndices,
             unordered_set<string>& emails, vector<bool>& visited, int index) {
        visited[index] = true;
        for(int j = 1; j < accounts[index].size(); j++) {
            string email = accounts[index][j];
            emails.insert(email);
            for(int neighbor : emailToIndices[email]) {
                if(!visited[neighbor]) {
                    dfs(accounts, emailToIndices, emails, visited, neighbor);
                }
            }
        }
    }
};


/*

User: Can you help me to understand this code and dry run please add diagram or visualization so i can understand easily?

GitHub Copilot: Read [](file:///c%3A/Users/lalit.k/lalit/d/dsa/grind/week5/721.%20Accounts%20Merge.cpp)

Perfect! This is the **Accounts Merge** problem (LeetCode #721). Let me explain it with a clear visualization and dry run.

## Code Overview

This solution uses **DFS (Depth-First Search)** to merge accounts that share common emails.

**Key Ideas:**
1. **Email-to-Indices Map**: Track which account indices contain each email
2. **DFS Traversal**: Visit all connected accounts (those sharing emails)
3. **Visited Array**: Prevent processing the same account twice

---

## Visual Explanation

```
EXAMPLE: accounts = [
  ["John", "johnsmith@mail.com", "john_newyork@mail.com"],
  ["John", "johnsmith@mail.com", "john00@mail.com"],
  ["Mary", "mary@mail.com"],
  ["John", "johnnewyork@mail.com", "johnsmith@mail.com"]
]

STEP 1: Build emailToIndices Map
================================
{
  "johnsmith@mail.com": [0, 1, 3],
  "john_newyork@mail.com": [0],
  "john00@mail.com": [1],
  "mary@mail.com": [2],
  "johnnewyork@mail.com": [3]
}

STEP 2: DFS Graph Visualization
================================
                  Email Connections
    
    Account 0  ──"johnsmith@mail.com"──  Account 1
       |                                     |
       └─"john_newyork@mail.com"───┐        └─"john00@mail.com"
                                    |
                                    |
    Account 3 ──"johnsmith@mail.com"┘
       |
       └─"johnnewyork@mail.com"  (same email as Account 0)

    Account 2  (isolated)
       |
       └─"mary@mail.com"

MERGING PROCESS:
- Accounts 0, 1, 3 are ALL CONNECTED → Merge into ONE
- Account 2 stands alone
```

---

## Dry Run

```
Starting DFS from Account 0 (John):
══════════════════════════════════════

Index 0:  visited[0] = true
├─ Email: "johnsmith@mail.com"
│  └─ Found in accounts: [0, 1, 3]
│     ├─ Account 0: Already visited ✓
│     ├─ Account 1: NOT visited → DFS(1)
│     │  visited[1] = true
│     │  ├─ Email: "johnsmith@mail.com" (in connected set)
│     │  ├─ Email: "john00@mail.com"
│     │  │  └─ Found only in [1] → No new accounts
│     │  └─ Return to DFS(0)
│     │
│     └─ Account 3: NOT visited → DFS(3)
│        visited[3] = true
│        ├─ Email: "johnnewyork@mail.com"
│        └─ Email: "johnsmith@mail.com" (in connected set)
│           └─ All neighbors already visited
│
└─ Return: All emails = {
   "johnsmith@mail.com",
   "john_newyork@mail.com", 
   "john00@mail.com",
   "johnnewyork@mail.com"
  }

Merged Account: ["John", "john00@mail.com", "john_newyork@mail.com",
                         "johnnewyork@mail.com", "johnsmith@mail.com"]

Index 1: visited[1] = true → SKIP

Index 2: NOT visited → DFS(2)
└─ Returns: ["mary@mail.com"]
   Merged Account: ["Mary", "mary@mail.com"]

Index 3: visited[3] = true → SKIP

FINAL OUTPUT:
═════════════
[
  ["John", "john00@mail.com", "john_newyork@mail.com", 
           "johnnewyork@mail.com", "johnsmith@mail.com"],
  ["Mary", "mary@mail.com"]
]
```

---

## Complexity Analysis

| Aspect | Complexity |
|--------|-----------|
| **Time** | O(N·K·logK) - N: accounts, K: emails per account; sorting dominates |
| **Space** | O(N·K) - Hash map + DFS stack |

The key insight is that **if two accounts share any email, they belong to the same person** and should be merged together!

*/