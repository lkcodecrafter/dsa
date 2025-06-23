
# ➕ Subarray Sum Printer (Optimized)

## 🧩 Problem Statement

Given an array, print all **subarrays** along with their **sum**, and also print the **total number of subarrays**.

---

## ✅ Example

Input:
```
arr = [1, 2, 3]
```

Output:
```
1 → Sum: 1
1 2 → Sum: 3
1 2 3 → Sum: 6

2 → Sum: 2
2 3 → Sum: 5

3 → Sum: 3

Total number of subarrays = 6
```

---

## 🧠 Approach

Instead of recalculating the sum from scratch each time, maintain a `currentSum`:

1. Outer loop fixes the `start` index.
2. Inner loop expands the subarray from `start` to `end`, adding to the `currentSum`.
3. Print the subarray and its sum.
4. Use formula `n*(n+1)/2` to calculate total number of subarrays.

---

## 🔁 Dry Run

Array = [1, 2, 3]

**Step-by-step:**

- start = 0 → currentSum = 0  
  - end = 0 → add 1 → print [1] → sum = 1  
  - end = 1 → add 2 → print [1, 2] → sum = 3  
  - end = 2 → add 3 → print [1, 2, 3] → sum = 6  

- start = 1 → currentSum = 0  
  - end = 1 → add 2 → print [2] → sum = 2  
  - end = 2 → add 3 → print [2, 3] → sum = 5  

- start = 2 → currentSum = 0  
  - end = 2 → add 3 → print [3] → sum = 3  

✅ Total subarrays = 6

---

## 💻 Java Code

```java
public class SubarraySum {

    public static void printSubarraysWithSum(int[] arr) {
        int n = arr.length;

        for (int start = 0; start < n; start++) {
            int currentSum = 0;

            for (int end = start; end < n; end++) {
                currentSum += arr[end];

                // Print subarray
                for (int k = start; k <= end; k++) {
                    System.out.print(arr[k] + " ");
                }

                System.out.println("→ Sum: " + currentSum);
            }

            System.out.println(); // blank line between subarrays
        }
    }

    public static void main(String[] args) {
        int[] numbers = {1, 2, 3, 4, 5};
        printSubarraysWithSum(numbers);

        int n = numbers.length;
        System.out.println("Total number of subarrays = " + (n * (n + 1)) / 2);
    }
}
```

---

## 📌 Complexity

- **Time Complexity:** O(n²)
- **Space Complexity:** O(1)

Optimized by avoiding redundant sum calculations.
