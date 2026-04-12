# 📘 Pattern 10: Monotonic Stack (Complete Guide with C++ + Dry Runs + Visualizations)

---

## 📌 What is Monotonic Stack?

A Monotonic Stack maintains elements in increasing or decreasing order.

---

## 🧠 When to Use?
- Next Greater / Smaller Element
- Subarray Min / Max
- Greedy removals

---

# 1️⃣ Remove Nodes From Linked List

Input:
5 → 2 → 13 → 3 → 8

Dry Run:
Push 5
Push 2
13 > 2 → pop
13 > 5 → pop
Push 13
Push 3
8 > 3 → pop
Push 8

Output:
13 → 8

---

# 2️⃣ Remove Adjacent Duplicates

Input: "abbaca"

[a]
[a,b]
[a]
[]
[c]
[c,a]

Output: "ca"

---

# 3️⃣ Next Greater Element

Input: [2,1,2,4,3]

Output:
[4,2,4,-1,-1]

---

# 4️⃣ Daily Temperatures

Input:
[73,74,75,71,69,72,76,73]

Output:
[1,1,4,2,1,1,0,0]

---

# 5️⃣ Remove Duplicates II

Input:
"deeedbbcccbdaa", k=3

Output:
"aa"

---

# 6️⃣ Sum of Subarray Minimums

Input:
[3,1,2,4]

Output:
17

---

# 7️⃣ Remove K Digits

Input:
"1432219", k=3

Output:
1219

---

# 📊 Visualization

[3,1,2,4]

Push 3
1 < 3 → pop
Push 1
Push 2
Push 4

---

# ✅ Summary

✔ O(N)
✔ Stack based
✔ Widely used in interviews
