
# 🔍 Binary Search in Java

## 🧩 Problem Statement

Given a **sorted array** of integers, find the index of a given key using the **binary search algorithm**. If the key is not present, return -1.

---

## ✅ Example

Input:
```
Array: [2, 4, 6, 8, 10, 12, 14, 16]
Key: 4
```

Output:
```
Your key is at index: 1
```

---

## 🧠 Approach

Binary Search is an efficient algorithm that works only on **sorted arrays**. It works by repeatedly dividing the search interval in half:

1. Find the middle index.
2. If the middle element is the key, return the index.
3. If the key is smaller, search the left half.
4. If the key is larger, search the right half.

---

## 🔁 Dry Run

Given:
```
Array = [2, 4, 6, 8, 10, 12, 14, 16]
Key = 4
```

### Steps:

1. start = 0, end = 7 → mid = 3 → arr[3] = 8  
   → 4 < 8 → search left half  
2. end = 2 → mid = 1 → arr[1] = 4 → match found ✅

Return index `1`.

### 🔹 Case 1: Key = 4 (Present)

| Step | start | end | mid | numbers[mid] | Action                     |
|------|-------|-----|-----|--------------|----------------------------|
| 1    | 0     | 7   | 3   | 8            | 4 < 8 → search left side   |
| 2    | 0     | 2   | 1   | 4            | ✅ Found at index 1        |

---

### 🔹 Case 2: Key = 10 (Present)

| Step | start | end | mid | numbers[mid] | Action                     |
|------|-------|-----|-----|--------------|----------------------------|
| 1    | 0     | 7   | 3   | 8            | 10 > 8 → search right side |
| 2    | 4     | 7   | 5   | 12           | 10 < 12 → left side        |
| 3    | 4     | 4   | 4   | 10           | ✅ Found at index 4        |

---

### 🔹 Case 3: Key = 13 (Not Present)

| Step | start | end | mid | numbers[mid] | Action                     |
|------|-------|-----|-----|--------------|----------------------------|
| 1    | 0     | 7   | 3   | 8            | 13 > 8 → right side        |
| 2    | 4     | 7   | 5   | 12           | 13 > 12 → right side       |
| 3    | 6     | 7   | 6   | 14           | 13 < 14 → left side        |
| 4    | 6     | 5   |     |              | ❌ start > end → not found |

---

### 🔹 Case 4: Key = 2 (First element)

| Step | start | end | mid | numbers[mid] | Action                     |
|------|-------|-----|-----|--------------|----------------------------|
| 1    | 0     | 7   | 3   | 8            | 2 < 8 → left side          |
| 2    | 0     | 2   | 1   | 4            | 2 < 4 → left side          |
| 3    | 0     | 0   | 0   | 2            | ✅ Found at index 0        |

---

### 🔹 Case 5: Key = 16 (Last element)

| Step | start | end | mid | numbers[mid] | Action                     |
|------|-------|-----|-----|--------------|----------------------------|
| 1    | 0     | 7   | 3   | 8            | 16 > 8 → right side        |
| 2    | 4     | 7   | 5   | 12           | 16 > 12 → right side       |
| 3    | 6     | 7   | 6   | 14           | 16 > 14 → right side       |
| 4    | 7     | 7   | 7   | 16           | ✅ Found at index 7        |

---
---

## 💻 Java Code

```java
import java.util.*;

public class BinarySearch {

    public static int performBinarySearch(int[] numbers, int key) {
        int start = 0;
        int end = numbers.length - 1;

        while (start <= end) {
            int mid = (start + end) / 2;

            if (numbers[mid] == key) {
                return mid;
            }

            if (numbers[mid] < key) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }

        return -1; // key not found
    }

    public static void main(String[] args) {
        int[] numbers = {2, 4, 6, 8, 10, 12, 14, 16};
        int key = 4;
        int resultIndex = performBinarySearch(numbers, key);

        if (resultIndex != -1) {
            System.out.println("Your key is at index: " + resultIndex);
        } else {
            System.out.println("Key not found.");
        }
    }
}
```

---

## 📌 Time & Space Complexity

- **Time Complexity:** O(log n)
- **Space Complexity:** O(1)

Binary Search is one of the most optimal searching techniques for sorted arrays.
