
# 📊 Print All Subarrays

## 🧩 Problem Statement

Given an array of integers, print **all possible subarrays** and compute the total number of subarrays.

---

## ✅ Example

Input:
```
arr = [2, 4, 6, 8, 10]
```

Output:
```
2 
2 4 
2 4 6 
2 4 6 8 
2 4 6 8 10 

4 
4 6 
4 6 8 
4 6 8 10 

6 
6 8 
6 8 10 

8 
8 10 

10 

Total subarrays = 15
```

---

## 🧠 Approach

We use **three nested loops**:

1. Outer loop to set the **start index** of the subarray.
2. Middle loop to set the **end index**.
3. Inner loop to print elements from `start` to `end`.

We calculate the total number of subarrays using the formula:

```
Total subarrays = n * (n + 1) / 2
```

---

## 🔁 Dry Run

Given:
```
arr = [2, 4, 6]
```

### Subarrays printed:

- [2]
- [2, 4]
- [2, 4, 6]
- [4]
- [4, 6]
- [6]

✅ Total = 6 = (3 × (3+1)) / 2

---

## 💻 Java Code

```java
import java.util.*;

public class SubarrayPrinter {

    public static void printAllSubarrays(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            int start = i;
            for (int j = i; j < arr.length; j++) {
                int end = j;
                for (int k = start; k <= end; k++) {
                    System.out.print(arr[k] + " ");
                }
                System.out.println();
            }
            System.out.println();
        }
    }

    public static void main(String args[]) {
        int[] numbers = {2, 4, 6, 8, 10};
        printAllSubarrays(numbers);

        int n = numbers.length;
        int totalSubarrays = (n * (n + 1)) / 2;
        System.out.println("Total subarrays = " + totalSubarrays);
    }
}
```

---

## 📌 Time & Space Complexity

- **Time Complexity:** O(n³) – because of the 3 nested loops.
- **Space Complexity:** O(1) – constant extra space used.
