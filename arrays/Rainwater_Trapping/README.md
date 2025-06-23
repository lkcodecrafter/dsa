
# 🌧️ Trapping Rain Water

## 🧩 Problem Statement

Given an array of non-negative integers representing the elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

---

## ✅ Example

Input:
```
bars = [4, 2, 0, 6, 3, 2, 5]
```

Output:
```
Output: 9
```

---

## 🧠 Approach

We calculate the **maximum bar height to the left and right** for each index. The trapped water at that index is:

```
waterLevel = min(leftMax[i], rightMax[i])
trapped = waterLevel - height[i]
```

### 🪜 Steps:

1. **Left max array**:
   - `leftMax[i] = max(bars[i], leftMax[i-1])`
2. **Right max array**:
   - `rightMax[i] = max(bars[i], rightMax[i+1])`
3. **Trapped water**:
   - For every index, compute:
     `waterLevel = min(leftMax[i], rightMax[i])`
     `trapped += (waterLevel - bars[i])`

---

## 🔁 Dry Run

Given:
```
bars = [4, 2, 0, 6, 3, 2, 5]
```

### Step 1: Compute `leftMax`
```
leftMax = [4, 4, 4, 6, 6, 6, 6]
```

### Step 2: Compute `rightMax`
```
rightMax = [6, 6, 6, 6, 5, 5, 5]
```

### Step 3: Calculate trapped water at each index:

| Index | bar | leftMax | rightMax | waterLevel | trapped |
|-------|-----|---------|----------|------------|---------|
|   0   |  4  |    4    |     6    |     4      |   0     |
|   1   |  2  |    4    |     6    |     4      |   2     |
|   2   |  0  |    4    |     6    |     4      |   4     |
|   3   |  6  |    6    |     6    |     6      |   0     |
|   4   |  3  |    6    |     5    |     5      |   2     |
|   5   |  2  |    6    |     5    |     5      |   3     |
|   6   |  5  |    6    |     5    |     5      |   0     |

✅ Total Trapped Water = 0 + 2 + 4 + 0 + 2 + 3 + 0 = **11**

---

## 💻 Java Code

```java
public class RainwaterTrapper {

    public static int calculateTrappedWater(int[] heightBars) {
        int n = heightBars.length;

        int[] leftMax = new int[n];
        leftMax[0] = heightBars[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = Math.max(heightBars[i], leftMax[i - 1]);
        }

        int[] rightMax = new int[n];
        rightMax[n - 1] = heightBars[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = Math.max(heightBars[i], rightMax[i + 1]);
        }

        int trappedWater = 0;
        for (int i = 0; i < n; i++) {
            int waterLevel = Math.min(leftMax[i], rightMax[i]);
            trappedWater += waterLevel - heightBars[i];
        }

        return trappedWater;
    }

    public static void main(String[] args) {
        int[] bars = {4, 2, 0, 6, 3, 2, 5};
        System.out.println(calculateTrappedWater(bars));
    }
}
```

---

## 📌 Time & Space Complexity

- **Time:** O(n) — 3 passes over the array
- **Space:** O(n) — for `leftMax` and `rightMax` arrays
