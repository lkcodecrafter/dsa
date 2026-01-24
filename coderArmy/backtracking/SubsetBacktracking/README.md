
# 🔁 Backtracking in Java – Subset Generation (Power Set)

## 📌 What is Backtracking?

Backtracking is a **recursive algorithm** that tries all possible solutions and **backtracks** (undoes steps) if the current solution doesn’t lead to the correct answer.

Used in:
- Subsets / Combinations
- Sudoku
- Maze Solving
- N-Queens
- String generation (permutations)

---

## 🧩 Problem Statement

Given an array of integers, print **all possible subsets** of it.

Input:
```
nums = [1, 2, 3]
```

Output:
```
[]
[1]
[1, 2]
[1, 2, 3]
[1, 3]
[2]
[2, 3]
[3]
```

---

## 💡 Approach

- Start from index 0.
- At each step, decide:
  - ✅ Include current element
  - ❌ Skip it
- Backtrack after recursive call to explore other paths.

---

## 🔁 Dry Run (nums = [1, 2])

```
Start: []

Choose 1 → [1]
  Choose 2 → [1, 2]
  Backtrack → [1]
Backtrack → []

Choose 2 → [2]
Backtrack → []

Result:
[]
[1]
[1, 2]
[2]
```

---

## 💻 Java Code

```java
import java.util.*;

public class SubsetBacktracking {

    public static void generateSubsets(int index, List<Integer> current, int[] nums) {
        System.out.println(current);

        for (int i = index; i < nums.length; i++) {
            current.add(nums[i]);                     // Choose
            generateSubsets(i + 1, current, nums);    // Explore
            current.remove(current.size() - 1);       // Un-choose
        }
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3};
        generateSubsets(0, new ArrayList<>(), nums);
    }
}
```

---

## 🧠 Time & Space Complexity

- **Time:** O(2^n) – total subsets for n elements
- **Space:** O(n) – recursion stack + current list

---

This is a base to understand backtracking. You can apply the same pattern to permutations, Sudoku, and N-Queens.
