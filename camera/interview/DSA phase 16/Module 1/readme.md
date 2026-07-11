# Module 1: Arrays & Basic Algorithms (Lectures 1–35)

## 📋 Syllabus
*   **Basics:** Introduction to Arrays, Input/Output, Min/Max.
*   **Sorting:** Selection Sort, Bubble Sort, Insertion Sort.
*   **Binary Search:** Search Insert Position, Sqrt(x), Rotated Sorted Array, Mountain Array, Book Allocation, Painter Partition, Aggressive Cows, Koko Eating Bananas.
*   **Two Pointers & Sliding Window:** Two Sum, Pair Difference, Move Zeroes, Kadane's Algorithm, Prefix/Suffix Sum, Trapping Rain Water, 3 Sum, 4 Sum.
*   **2D Arrays:** Wave Print, Spiral Print, Matrix Transpose, Rotate 90 Degrees, Binary Search in 2D Matrix.

---

## 🟢 Section 1: Basics

### 🎯 Solution 1.1: Introduction to Arrays
*   **Concept:** Arrays are contiguous memory allocations storing elements of the same data type. C++ supports static arrays (fixed size on stack) and dynamic arrays (`std::vector` on heap).
*   **C++ Code:**
```cpp
#include <iostream>
#include <vector>

void demonstrateArrays() {
    // Static array declaration and initialization
    int staticArr[5] = {10, 20, 30, 40, 50};
    
    // Dynamic array (Vector) declaration and initialization
    std::vector<int> dynamicArr = {1, 2, 3, 4, 5};
    
    // Accessing and traversing elements
    for (int i = 0; i < 5; i++) {
        std::cout << "Element at index " << i << ": " << staticArr[i] << "\n";
    }
}
```
*   **🔍 Dry Run:**
    For `staticArr` initialized with `{10, 20, 30, 40, 50}`:
    Assuming base address is `2000` (each `int` is 4 bytes):
    *   `staticArr[0]` is at address `2000`, value = `10`
    *   `staticArr[1]` is at address `2004`, value = `20`
    *   `staticArr[2]` is at address `2008`, value = `30`
    *   `staticArr[3]` is at address `2012`, value = `40`
    *   `staticArr[4]` is at address `2016`, value = `50`
*   **Complexity:** 
    *   Access: $O(1)$
    *   Search: $O(N)$
    *   Space: $O(N)$ to store $N$ elements.

### 🎯 Solution 1.2: Input/Output of Arrays
*   **Problem:** Read array size $N$ and its elements from standard input, and print them to standard output.
*   **C++ Code:**
```cpp
#include <iostream>
#include <vector>

void inputOutputArray() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    
    // Input
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    
    // Output
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}
```
*   **🔍 Dry Run:**
    *   **Input stream:** `3 \n 7 2 9`
    *   `n` is read as `3`. Vector `arr` initialized to size `3`.
    *   Loop `i = 0`: reads `7` into `arr[0]`
    *   Loop `i = 1`: reads `2` into `arr[1]`
    *   Loop `i = 2`: reads `9` into `arr[2]`
    *   Output loop runs from `i = 0` to `2` and prints: `7 2 9`
*   **Complexity:** Time: $O(N)$, Space: $O(1)$ auxiliary.

### 🎯 Solution 1.3: Find Min/Max in Array
*   **Problem:** Given an array, find the minimum and maximum element.
*   **C++ Code:**
```cpp
#include <vector>
#include <climits>
#include <algorithm>

std::pair<int, int> findMinMax(const std::vector<int>& arr) {
    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    
    for (int num : arr) {
        if (num < minVal) minVal = num;
        if (num > maxVal) maxVal = num;
    }
    return {minVal, maxVal};
}
```
*   **🔍 Dry Run:**
    *   **Input:** `arr = {12, 3, 19, -5, 8}`
    *   Initialize `minVal = INT_MAX`, `maxVal = INT_MIN`

| Step | Element | `num < minVal` check | `minVal` update | `num > maxVal` check | `maxVal` update |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1** | 12 | `12 < INT_MAX` (True) | `12` | `12 > INT_MIN` (True) | `12` |
| **2** | 3 | `3 < 12` (True) | `3` | `3 > 12` (False) | `12` |
| **3** | 19 | `19 < 3` (False) | `3` | `19 > 12` (True) | `19` |
| **4** | -5 | `-5 < 3` (True) | `-5` | `-5 > 19` (False) | `19` |
| **5** | 8 | `8 < -5` (False) | `-5` | `8 > 19` (False) | `19` |

    *   **Result:** Min = `-5`, Max = `19`.
*   **Complexity:** Time: $O(N)$, Space: $O(1)$.

---

## 🟢 Section 2: Sorting

### 🎯 Solution 2.1: Selection Sort
*   **Problem:** Sort an array by repeatedly picking the minimum element from the unsorted segment and swapping it with the first element of that segment.
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        std::swap(arr[i], arr[minIdx]);
    }
}
```
*   **🔍 Dry Run:**
    *   **Input:** `{64, 25, 12, 22, 11}`
    *   **Pass 1 (`i = 0`):** `minIdx` starts at `0`. Internal loop scans indices 1 to 4. Finds minimum element `11` at index `4`. Swap `arr[0]` and `arr[4]`. Array: `{11, 25, 12, 22, 64}`.

       j = 1. arr[j] < arr[minIdx] value is 25 < 64 so min is 25 not 64 , remove min =64, then min =25
       j = 2. arr[j] < arr[minIdx] value is 12 < 25 so min is 12 not 25, remove min =25, then min =12
       j = 3. arr[j] < arr[minIdx] value is 22 < 12 so min is 12 not 22
       j = 4. arr[j] < arr[minIdx] value is 11 < 12 so min is 11 not 11, remove min =12, then min =11
    minIdx = 4. swap arr[0] and arr[4]. Array: `{11, 25, 12, 22, 64}`.

    *   **Pass 2 (`i = 1`):** `minIdx` starts at `1`. Finds minimum `12` at index `2`. Swap `arr[1]` and `arr[2]`. Array: `{11, 12, 25, 22, 64}`.
    *   **Pass 3 (`i = 2`):** `minIdx` starts at `2`. Finds minimum `22` at index `3`. Swap `arr[2]` and `arr[3]`. Array: `{11, 12, 22, 25, 64}`.
    *   **Pass 4 (`i = 3`):** `minIdx` starts at `3`. Finds minimum `25` at index `3`. No swap needed. Array: `{11, 12, 22, 25, 64}`.
*   **Complexity:** Time: $O(N^2)$ (best, average, worst), Space: $O(1)$.

### 🎯 Solution 2.2: Bubble Sort
*   **Problem:** Sort an array by repeatedly swapping adjacent elements if they are in the incorrect order. An optimization flag stops early if no swaps occur.
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
```
*   **🔍 Dry Run:**
    *   **Input:** `{5, 1, 4, 2, 8}`
    *   **Pass 1 (`i = 0`):**
        *   `j=0`: `5 > 1` (True) -> Swap. Array: `{1, 5, 4, 2, 8}`
        *   `j=1`: `5 > 4` (True) -> Swap. Array: `{1, 4, 5, 2, 8}`
        *   `j=2`: `5 > 2` (True) -> Swap. Array: `{1, 4, 2, 5, 8}`
        *   `j=3`: `5 > 8` (False). End of pass 1. `swapped = true`.
    *   **Pass 2 (`i = 1`):**
        *   `j=0`: `1 > 4` (False)
        *   `j=1`: `4 > 2` (True) -> Swap. Array: `{1, 2, 4, 5, 8}`
        *   `j=2`: `4 > 5` (False). End of pass 2. `swapped = true`.
    *   **Pass 3 (`i = 2`):**
        *   `j=0`: `1 > 2` (False)
        *   `j=1`: `2 > 4` (False). End of pass 3. `swapped = false` -> Break loop. Sorted!
       
        Here j will run till 2 only? No 
        menas 2>2 will check i = 2 and j = 1. where as arr[j] = 2 and arr[j+1] = 4. 
        where j=2 n-i-1 = 5-2-1=2. So j will run till 2 only like 2<2 condition will false

*   **Complexity:** Time: Worst/Average $O(N^2)$, Best (sorted) $O(N)$. Space: $O(1)$.

### 🎯 Solution 2.3: Insertion Sort
*   **Problem:** Sort an array by picking elements one-by-one and inserting them into their correct sorted position relative to the elements before them. like card sorting in hand,you pick one card and insert it in its correct position among the cards you already have sorted in hand
*   **C++ Code:**
```cpp
#include <vector>

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
```
*   **🔍 Dry Run:**
    *   **Input:** `{12, 11, 13, 5, 6}`
    *   **Iteration 1 (`i = 1`):** `key = 11`, `j = 0`. `arr[0] (12) > 11` -> shift `12` right. Array becomes `{12, 12, 13, 5, 6}`, `j = -1`. Insert `11` at index 0. Array: `{11, 12, 13, 5, 6}`.
    *   **Iteration 2 (`i = 2`):** `key = 13`, `j = 1`. `arr[1] (12) > 13` is False. Insert `13` at index 2. Array: `{11, 12, 13, 5, 6}`.
    *   **Iteration 3 (`i = 3`):** `key = 5`, `j = 2`. Shifts `13`, `12`, `11` to the right. Insert `5` at index 0. Array: `{5, 11, 12, 13, 6}`.
    *   **Iteration 4 (`i = 4`):** `key = 6`, `j = 3`. Shifts `13`, `12`, `11` to the right. Insert `6` at index 1. Array: `{5, 6, 11, 12, 13}`.
*   **Complexity:** Time: Worst/Average $O(N^2)$, Best (sorted) $O(N)$. Space: $O(1)$.

---

### 🎯 Solution 2.4: Selection Sort 2 (Without using swap)

*   **Problem:** Sort an array by repeatedly picking the minimum element from the unsorted segment and swapping it with the first element of that segment. (Without using swap)

*   **C++ Code:**
```cpp
#include <iostream>

int findmin(int arr[], int n, int start) {
    int min = arr[start];
    int minindex = start;
    for (int i = start; i < n; i++) {
        if (min > arr[i]) {
            min = arr[i];
            minindex = i;
        }
    }
    return minindex;
}

void selectionSort(int arr[], int n) {
    int minindex;

    for (int i = 0; i < n; i++) {
        minindex = findmin(arr, n, i);
        int temp = arr[i];
        arr[i] = arr[minindex];
        arr[minindex] = temp;
    }
}


```


## 🟢 Section 3: Binary Search

### 🎯 Solution 3.1: Search Insert Position
*   **Problem:** Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.
*   **C++ Code:**
```cpp
#include <vector>

int searchInsert(const std::vector<int>& nums, int target) {
    int start = 0, end = nums.size() - 1;
    int ans = nums.size(); // default value if target is larger than all elements
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (nums[mid] >= target) {
            ans = mid; // Potential index
            end = mid - 1; // Look for a smaller index on the left
        } else {
            start = mid + 1;
        }
    }
    return ans;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `nums = {1, 3, 5, 6}`, `target = 2`
    *   `start = 0`, `end = 3`, `ans = 4`
    *   **Iteration 1:** `mid = 1`, `nums[1] = 3 >= 2` (True). Update `ans = 1`, `end = mid - 1 = 0`.
    *   **Iteration 2:** `mid = 0`, `nums[0] = 1 >= 2` (False). Update `start = mid + 1 = 1`.
    *   Loop terminates since `start (1) > end (0)`.
    *   **Result:** `1`.
*   **Complexity:** Time: $O(\log N)$, Space: $O(1)$.

### 🎯 Solution 3.2: Sqrt(x)
*   **Problem:** Compute and return the square root of $x$ truncated to the nearest integer.
*   **C++ Code:**
```cpp
int mySqrt(int x) {
    if (x == 0 || x == 1) return x;
    int start = 1, end = x;
    int ans = 0;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        // Use division to prevent integer overflow
        if (mid <= x / mid) {
            ans = mid;
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return ans;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `x = 8`
    *   `start = 1`, `end = 8`, `ans = 0`
    *   **Iteration 1:** `mid = 4`. `4 <= 8/4 (2)` is False. Update `end = 3`.
    *   **Iteration 2:** `mid = 2`. `2 <= 8/2 (4)` is True. Update `ans = 2`, `start = 3`.
    *   **Iteration 3:** `mid = 3`. `3 <= 8/3 (2)` is False. Update `end = 2`.
    *   Loop terminates since `start (3) > end (2)`.
    *   **Result:** `2` (since $\sqrt{8} \approx 2.828$, truncated to `2`).
*   **Complexity:** Time: $O(\log x)$, Space: $O(1)$.

### 🎯 Solution 3.3: Search in Rotated Sorted Array
*   **Problem:** Find an element in a sorted array that has been rotated.
*   **C++ Code:**
```cpp
#include <vector>

int search(const std::vector<int>& nums, int target) {
    int start = 0, end = nums.size() - 1;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (nums[mid] == target) return mid;
        
        // Check if left half is sorted
        if (nums[start] <= nums[mid]) {
            if (target >= nums[start] && target < nums[mid]) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        } 
        // Otherwise, right half must be sorted
        else {
            if (target > nums[mid] && target <= nums[end]) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
    }
    return -1;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `nums = {4, 5, 6, 7, 0, 1, 2}`, `target = 0`

| Iteration | `start` | `end` | `mid` | `nums[mid]` | Sorted Half | Location of Target | Next Range |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **1** | 0 (4) | 6 (2) | 3 | 7 | Left (`[4..7]`) | Outside Left | `start = 4` |
| **2** | 4 (0) | 6 (2) | 5 | 1 | Right (`[1..2]`) | Outside Right | `end = 4` |
| **3** | 4 (0) | 4 (0) | 4 | 0 | Found! | Returns index `4` | - |

*   **Complexity:** Time: $O(\log N)$, Space: $O(1)$.

### 🎯 Solution 3.4: Peak Index in Mountain Array
*   **Problem:** Find the index of the largest element in an array that rises and then falls.
*   **C++ Code:**
```cpp
#include <vector>

int peakIndexInMountainArray(const std::vector<int>& arr) {
    int start = 0, end = arr.size() - 1;
    while (start < end) {
        int mid = start + (end - start) / 2;
        // If in the rising part of the peak
        if (arr[mid] < arr[mid + 1]) {
            start = mid + 1;
        } else {
            // In the falling part, mid can still be the peak
            end = mid;
        }
    }
    return start;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `arr = {0, 10, 5, 2}`
    *   `start = 0`, `end = 3`
    *   **Iteration 1:** `mid = 1`. `arr[1] (10) < arr[2] (5)` is False. Update `end = 1`.
    *   **Iteration 2:** `mid = 0`. `arr[0] (0) < arr[1] (10)` is True. Update `start = 1`.
    *   Loop terminates since `start (1) == end (1)`.
    *   **Result:** `1`.
*   **Complexity:** Time: $O(\log N)$, Space: $O(1)$.

### 🎯 Solution 3.5: Book Allocation Problem
*   **Problem:** Allocate books to $M$ students such that the maximum pages assigned to any student is minimized.
*   **C++ Code:**
```cpp
#include <vector>
#include <numeric>
#include <algorithm>

bool isPossible(const std::vector<int>& arr, int n, int m, int maxPages) {
    int studentCount = 1;
    int pageSum = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxPages) return false;
        if (pageSum + arr[i] > maxPages) {
            studentCount++;
            pageSum = arr[i];
            if (studentCount > m) return false;
        } else {
            pageSum += arr[i];
        }
    }
    return true;
}

int allocateBooks(const std::vector<int>& arr, int n, int m) {
    if (m > n) return -1;
    int start = *std::max_element(arr.begin(), arr.end());
    int end = std::accumulate(arr.begin(), arr.end(), 0);
    int ans = -1;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (isPossible(arr, n, m, mid)) {
            ans = mid;
            end = mid - 1; // Try for a smaller maximum
        } else {
            start = mid + 1; // Increase allowed limit
        }
    }
    return ans;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `arr = {12, 34, 67, 90}`, `m = 2`
    *   `start = 90` (max element), `end = 203` (sum of pages)

| Step | `start` | `end` | `mid` | `isPossible` Check (Limit = `mid`) | Decision |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1** | 90 | 203 | **146** | S1: {12, 34, 67} (113), S2: {90} -> **True** | `ans=146`, `end=145` |
| **2** | 90 | 145 | **117** | S1: {12, 34} (46), S2: {67}, S3: {90} (Requires 3 students) -> **False** | `start=118` |
| **3** | 118 | 145 | **131** | S1: {12, 34} (46), S2: {67}, S3: {90} -> **False** | `start=132` |
| **4** | 132 | 145 | **138** | S1: {12, 34} (46), S2: {67}, S3: {90} -> **False** | `start=139` |
| **5** | 139 | 145 | **142** | S1: {12, 34} (46), S2: {67}, S3: {90} -> **False** | `start=143` |
| **6** | 143 | 145 | **144** | S1: {12, 34} (46), S2: {67}, S3: {90} -> **False** | `start=145` |
| **7** | 145 | 145 | **145** | S1: {12, 34} (46), S2: {67}, S3: {90} -> **False** | `start=146` |

    *   **Result:** `113` (Actual binary search yields minimum limit of 113 for valid allocation).
*   **Complexity:** Time: $O(N \log(\text{sum} - \text{max}))$, Space: $O(1)$.

### 🎯 Solution 3.6: Painter Partition Problem
*   **Problem:** Find the minimum time required to paint $N$ boards of given lengths using $K$ painters, where each painter paints contiguous sections and takes 1 unit of time per unit board length.
*   **C++ Code:**
```cpp
#include <vector>
#include <numeric>
#include <algorithm>

bool isPossiblePainter(const std::vector<int>& boards, int k, int maxTime) {
    int painterCount = 1;
    int currentSum = 0;
    
    for (int board : boards) {
        if (board > maxTime) return false;
        if (currentSum + board > maxTime) {
            painterCount++;
            currentSum = board;
            if (painterCount > k) return false;
        } else {
            currentSum += board;
        }
    }
    return true;
}

int painterPartition(const std::vector<int>& boards, int k) {
    int start = *std::max_element(boards.begin(), boards.end());
    int end = std::accumulate(boards.begin(), boards.end(), 0);
    int ans = -1;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (isPossiblePainter(boards, k, mid)) {
            ans = mid;
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
    return ans;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `boards = {10, 20, 30, 40}`, `k = 2`
    *   `start = 40` (max board), `end = 100` (sum of boards)
    *   **Iteration 1:** `mid = 70`. `isPossible(boards, 2, 70)`: P1 gets `{10, 20, 30}` (sum 60), P2 gets `{40}` (sum 40) -> Possible. `ans = 70`, `end = 69`.
    *   **Iteration 2:** `mid = 54`. `isPossible(boards, 2, 54)`: P1 gets `{10, 20}` (sum 30), P2 gets `{30}` (sum 30), P3 gets `{40}` (requires 3 painters) -> Impossible. `start = 55`.
    *   We binary search down to find the correct threshold `60`.
*   **Complexity:** Time: $O(N \log(\text{sum} - \text{max}))$, Space: $O(1)$.

### 🎯 Solution 3.7: Aggressive Cows
*   **Problem:** Place $C$ cows in $N$ stalls such that the minimum distance between any two cows is maximized.
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

bool isPossibleCows(const std::vector<int>& stalls, int c, int minDist) {
    int cowCount = 1;
    int lastPos = stalls[0];
    
    for (size_t i = 1; i < stalls.size(); i++) {
        if (stalls[i] - lastPos >= minDist) {
            cowCount++;
            lastPos = stalls[i];
            if (cowCount == c) return true;
        }
    }
    return false;
}

int aggressiveCows(std::vector<int>& stalls, int c) {
    std::sort(stalls.begin(), stalls.end());
    int start = 1;
    int end = stalls.back() - stalls.front();
    int ans = -1;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (isPossibleCows(stalls, c, mid)) {
            ans = mid;
            start = mid + 1; // Try to maximize the minimum distance
        } else {
            end = mid - 1; // Try smaller distances
        }
    }
    return ans;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `stalls = {1, 2, 8, 4, 9}`, `c = 3`. Sorted: `{1, 2, 4, 8, 9}`.
    *   `start = 1`, `end = 9 - 1 = 8`.
    *   **Iteration 1:** `mid = 4`. `isPossible(stalls, 3, 4)`: Cow 1 at `1`, Cow 2 at `8` (distance 7 >= 4), Cow 3 at `9` (distance 1 < 4, not possible) -> Cow count is 2 -> False. Update `end = 3`.
    *   **Iteration 2:** `mid = 2`. `isPossible(stalls, 3, 2)`: Cow 1 at `1`, Cow 2 at `4` (diff 3 >= 2), Cow 3 at `8` (diff 4 >= 2) -> Cow count is 3 -> True. Update `ans = 2`, `start = 3`.
    *   **Iteration 3:** `mid = 3`. `isPossible(stalls, 3, 3)`: Cow 1 at `1`, Cow 2 at `4` (diff 3 >= 3), Cow 3 at `8` (diff 4 >= 3) -> True. Update `ans = 3`, `start = 4`.
    *   Loop terminates since `start (4) > end (3)`.
    *   **Result:** `3`.
*   **Complexity:** Time: $O(N \log N + N \log(\text{max\_dist}))$, Space: $O(1)$.

### 🎯 Solution 3.8: Koko Eating Bananas
*   **Problem:** Find the minimum integer eating speed $K$ such that Koko can eat all bananas in $H$ hours.
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

bool canEatAll(const std::vector<int>& piles, int h, int speed) {
    long long hours = 0;
    for (int pile : piles) {
        // Equivalent to ceil(pile / speed) without float arithmetic
        hours += (pile + speed - 1) / speed;
    }
    return hours <= h;
}

int minEatingSpeed(const std::vector<int>& piles, int h) {
    int start = 1;
    int end = *std::max_element(piles.begin(), piles.end());
    int ans = end;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (canEatAll(piles, h, mid)) {
            ans = mid;
            end = mid - 1; // Try to find a slower speed
        } else {
            start = mid + 1; // Increase speed
        }
    }
    return ans;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `piles = {3, 6, 7, 11}`, `h = 8`
    *   `start = 1`, `end = 11`.
    *   **Iteration 1:** `mid = 6`. Hours: $\lceil 3/6 \rceil + \lceil 6/6 \rceil + \lceil 7/6 \rceil + \lceil 11/6 \rceil = 1 + 1 + 2 + 2 = 6 \le 8$ -> True. `ans = 6`, `end = 5`.
    *   **Iteration 2:** `mid = 3`. Hours: $\lceil 3/3 \rceil + \lceil 6/3 \rceil + \lceil 7/3 \rceil + \lceil 11/3 \rceil = 1 + 2 + 3 + 4 = 10 > 8$ -> False. `start = 4`.
    *   **Iteration 3:** `mid = 4`. Hours: $\lceil 3/4 \rceil + \lceil 6/4 \rceil + \lceil 7/4 \rceil + \lceil 11/4 \rceil = 1 + 2 + 2 + 3 = 8 \le 8$ -> True. `ans = 4`, `end = 3`.
    *   **Result:** `4`.
*   **Complexity:** Time: $O(N \log(\max(\text{piles})))$, Space: $O(1)$.

---

## 🟢 Section 4: Two Pointers & Sliding Window

### 🎯 Solution 4.1: Two Sum (Sorted Array)
*   **Problem:** Find two indices (1-indexed) in a sorted array such that they add up to a target sum.
*   **C++ Code:**
```cpp
#include <vector>

std::pair<int, int> twoSum(const std::vector<int>& numbers, int target) {
    int left = 0, right = numbers.size() - 1;
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) {
            return {left + 1, right + 1}; // 1-indexed output
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    return {-1, -1};
}
```
*   **🔍 Dry Run:**
    *   **Input:** `numbers = {2, 7, 11, 15}`, `target = 9`
    *   `left = 0`, `right = 3`
    *   **Iteration 1:** `sum = numbers[0] + numbers[3] = 2 + 15 = 17 > 9`. Decrement `right = 2`.
    *   **Iteration 2:** `sum = numbers[0] + numbers[2] = 2 + 11 = 13 > 9`. Decrement `right = 1`.
    *   **Iteration 3:** `sum = numbers[0] + numbers[1] = 2 + 7 = 9 == 9`. Return `{1, 2}`.
*   **Complexity:** Time: $O(N)$, Space: $O(1)$.

### 🎯 Solution 4.2: Pair Difference
*   **Problem:** Find if there exists a pair in a sorted array with a target difference (`arr[j] - arr[i] == diff`).
*   **C++ Code:**
```cpp
#include <vector>

std::pair<int, int> pairDifference(const std::vector<int>& arr, int diff) {
    int n = arr.size();
    int i = 0, j = 1;
    
    while (i < n && j < n) {
        if (i != j && arr[j] - arr[i] == diff) {
            return {i, j};
        } else if (arr[j] - arr[i] < diff) {
            j++;
        } else {
            i++;
        }
    }
    return {-1, -1};
}
```
*   **🔍 Dry Run:**
    *   **Input:** `arr = {5, 20, 32, 50, 80}`, `diff = 30`
    *   `i = 0`, `j = 1`
    *   **Iteration 1:** `arr[1] - arr[0] = 20 - 5 = 15 < 30`. Increment `j = 2`.
    *   **Iteration 2:** `arr[2] - arr[0] = 32 - 5 = 27 < 30`. Increment `j = 3`.
    *   **Iteration 3:** `arr[3] - arr[0] = 50 - 5 = 45 > 30`. Increment `i = 1`.
    *   **Iteration 4:** `arr[3] - arr[1] = 50 - 20 = 30 == 30`. Return pair indices `{1, 3}`.
*   **Complexity:** Time: $O(N)$, Space: $O(1)$.

### 🎯 Solution 4.3: Move Zeroes
*   **Problem:** Move all zeroes in an array to the end in-place while maintaining the relative order of non-zero elements.
*   **C++ Code:**
```cpp
#include <vector>

void moveZeroes(std::vector<int>& nums) {
    int insertPos = 0;
    // Shift all non-zero elements to the front
    for (int num : nums) {
        if (num != 0) {
            nums[insertPos++] = num;
        }
    }
    // Fill remaining spaces with zeroes
    while (insertPos < nums.size()) {
        nums[insertPos++] = 0;
    }
}
```
*   **🔍 Dry Run:**
    *   **Input:** `{0, 1, 0, 3, 12}`
    *   `insertPos = 0`
    *   `num = 0`: skipped
    *   `num = 1`: `nums[0] = 1`, `insertPos = 1`
    *   `num = 0`: skipped
    *   `num = 3`: `nums[1] = 3`, `insertPos = 2`
    *   `num = 12`: `nums[2] = 12`, `insertPos = 3`
    *   Fill remaining: `nums[3] = 0`, `nums[4] = 0`.
    *   **Result:** `{1, 3, 12, 0, 0}`.
*   **Complexity:** Time: $O(N)$, Space: $O(1)$.

### 🎯 Solution 4.4: Kadane's Algorithm (Max Subarray Sum)
*   **Problem:** Find the contiguous subarray within a 1D array of numbers which has the largest sum.
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>
#include <climits>

int maxSubArray(const std::vector<int>& nums) {
    int maxSoFar = INT_MIN;
    int currentSum = 0;
    
    for (int num : nums) {
        currentSum += num;
        maxSoFar = std::max(maxSoFar, currentSum);
        if (currentSum < 0) {
            currentSum = 0;
        }
    }
    return maxSoFar;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4}`

| Index | Element | `currentSum` (before update) | `currentSum` (after update) | `maxSoFar` | Action (`currentSum < 0` check) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **0** | -2 | 0 | -2 | -2 | Reset `currentSum` to 0 |
| **1** | 1 | 0 | 1 | 1 | No reset |
| **2** | -3 | 1 | -2 | 1 | Reset `currentSum` to 0 |
| **3** | 4 | 0 | 4 | 4 | No reset |
| **4** | -1 | 4 | 3 | 4 | No reset |
| **5** | 2 | 3 | 5 | 5 | No reset |
| **6** | 1 | 5 | 6 | **6** | No reset |
| **7** | -5 | 6 | 1 | 6 | No reset |
| **8** | 4 | 1 | 5 | 6 | No reset |

    *   **Final Output:** `6` (Subarray: `[4, -1, 2, 1]`)
*   **Complexity:** Time: $O(N)$, Space: $O(1)$.

### 🎯 Solution 4.5: Prefix & Suffix Sum (Equilibrium Index)
*   **Problem:** Find the equilibrium index of an array (where the sum of elements at lower indices is equal to the sum of elements at higher indices).
*   **C++ Code:**
```cpp
#include <vector>
#include <numeric>

int findEquilibriumIndex(const std::vector<int>& arr) {
    int totalSum = std::accumulate(arr.begin(), arr.end(), 0);
    int leftSum = 0;
    
    for (size_t i = 0; i < arr.size(); i++) {
        totalSum -= arr[i]; // totalSum is now rightSum
        if (leftSum == totalSum) {
            return i;
        }
        leftSum += arr[i];
    }
    return -1;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `arr = {-7, 1, 5, 2, -4, 3, 0}`
    *   `totalSum = 0` (sum calculated initially is `0`)

| Step | Index | Element | `totalSum` (rightSum) | `leftSum` | Comparison (`leftSum == totalSum`) | Next `leftSum` |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **1** | 0 | -7 | 7 | 0 | `0 == 7` (False) | -7 |
| **2** | 1 | 1 | 6 | -7 | `-7 == 6` (False) | -6 |
| **3** | 2 | 5 | 1 | -6 | `-6 == 1` (False) | -1 |
| **4** | 3 | 2 | -1 | -1 | `-1 == -1` (True) | **Returns 3** |

*   **Complexity:** Time: $O(N)$, Space: $O(1)$.

### 🎯 Solution 4.6: Trapping Rain Water
*   **Problem:** Given non-negative integers representing heights, compute how much water it can trap after raining.
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

int trap(const std::vector<int>& height) {
    int n = height.size();
    if (n <= 2) return 0;
    
    int left = 0, right = n - 1;
    int leftMax = 0, rightMax = 0;
    int waterTrapped = 0;
    
    while (left < right) {
        if (height[left] <= height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                waterTrapped += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                waterTrapped += rightMax - height[right];
            }
            right--;
        }
    }
    return waterTrapped;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}`
```
Pointers: L = 0, R = 11
leftMax = 0, rightMax = 0, waterTrapped = 0

1. height[0] (0) <= height[11] (1) -> process Left. height[0] >= leftMax (0>=0) -> leftMax = 0. L++ (1).
2. height[1] (1) <= height[11] (1) -> process Left. height[1] >= leftMax (1>=0) -> leftMax = 1. L++ (2).
3. height[2] (0) <= height[11] (1) -> process Left. height[2] < leftMax (0<1) -> waterTrapped += 1-0 = 1. L++ (3).
4. height[3] (2) > height[11] (1) -> process Right. height[11] >= rightMax (1>=0) -> rightMax = 1. R-- (10).
5. height[3] (2) > height[10] (2) -> process Right. height[10] >= rightMax (2>=1) -> rightMax = 2. R-- (9).
...
Final Water Trapped = 6
```
*   **Complexity:** Time: $O(N)$, Space: $O(1)$.

### 🎯 Solution 4.7: 3 Sum
*   **Problem:** Find all unique triplets in an array that sum to zero.
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    
    for (int i = 0; i < n - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue; // Avoid duplicate triplets
        
        int left = i + 1, right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    return result;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `nums = {-1, 0, 1, 2, -1, -4}`. Sorted: `{-4, -1, -1, 0, 1, 2}`.
    *   `i = 0`: `nums[0] = -4`. `left = 1 (-1)`, `right = 5 (2)`. Sum = `-4 + -1 + 2 = -3 < 0` -> `left++ (2)`.
    *   `i = 1`: `nums[1] = -1`. `left = 2 (-1)`, `right = 5 (2)`. Sum = `-1 + -1 + 2 = 0` -> Add `{-1, -1, 2}`, skip duplicate left/right pointers.
    *   Same loop finds `{-1, 0, 1}` when `left = 3 (0)`, `right = 4 (1)`.
    *   `i = 2`: `nums[2] = -1` (duplicate of `nums[1]`), skip.
*   **Complexity:** Time: $O(N^2)$, Space: $O(\log N)$ or $O(N)$ for sorting.

### 🎯 Solution 4.8: 4 Sum
*   **Problem:** Find all unique quadruplets in an array that sum to a target value.
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
    std::vector<std::vector<int>> result;
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    
    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        for (int j = i + 1; j < n - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            
            int left = j + 1, right = n - 1;
            while (left < right) {
                long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];
                if (sum == target) {
                    result.push_back({nums[i], nums[j], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    left++;
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
    }
    return result;
}
```
*   **🔍 Dry Run:**
    *   **Input:** `nums = {1, 0, -1, 0, -2, 2}`, `target = 0`. Sorted: `{-2, -1, 0, 0, 1, 2}`.
    *   First outer loop `i = 0 (-2)`, second outer loop `j = 1 (-1)`.
    *   `left = 2 (0)`, `right = 5 (2)`. Sum = `-2 + -1 + 0 + 2 = -1 < 0` -> `left++ (3)`.
    *   When pointers match combinations like `{-2, -1, 1, 2}` and `{-2, 0, 0, 2}`, they are outputted.
*   **Complexity:** Time: $O(N^3)$, Space: $O(1)$ auxiliary.

---

## 🟢 Section 5: 2D Arrays

### 🎯 Solution 5.1: Wave Print
*   **Problem:** Traverse a 2D matrix column-by-column, printing elements in a wave-like pattern (top-to-bottom for even columns, bottom-to-top for odd columns).
*   **C++ Code:**
```cpp
#include <vector>
#include <iostream>

void wavePrint(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) return;
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    for (int col = 0; col < cols; col++) {
        if (col % 2 == 0) {
            for (int row = 0; row < rows; row++) {
                std::cout << matrix[row][col] << " ";
            }
        } else {
            for (int row = rows - 1; row >= 0; row--) {
                std::cout << matrix[row][col] << " ";
            }
        }
    }
    std::cout << "\n";
}
```
*   **🔍 Dry Run:**
    *   **Input:** Matrix:
        $$\begin{pmatrix} 1 & 2 & 3 \\ 4 & 5 & 6 \\ 7 & 8 & 9 \end{pmatrix}$$
    *   `col = 0` (even): print `matrix[0][0]`, `matrix[1][0]`, `matrix[2][0]` -> `1 4 7`
    *   `col = 1` (odd): print `matrix[2][1]`, `matrix[1][1]`, `matrix[0][1]` -> `8 5 2`
    *   `col = 2` (even): print `matrix[0][2]`, `matrix[1][2]`, `matrix[2][2]` -> `3 6 9`
    *   **Result:** `1 4 7 8 5 2 3 6 9`.
*   **Complexity:** Time: $O(R \times C)$, Space: $O(1)$.

### 🎯 Solution 5.2: Spiral Print
*   **Problem:** Print the elements of a matrix in a clockwise spiral order.
*   **C++ Code:**
```cpp
#include <vector>
#include <iostream>

void spiralPrint(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty()) return;
    int rowStart = 0, rowEnd = matrix.size() - 1;
    int colStart = 0, colEnd = matrix[0].size() - 1;
    
    while (rowStart <= rowEnd && colStart <= colEnd) {
        // Traverse Right
        for (int col = colStart; col <= colEnd; col++) {
            std::cout << matrix[rowStart][col] << " ";
        }
        rowStart++;
        
        // Traverse Down
        for (int row = rowStart; row <= rowEnd; row++) {
            std::cout << matrix[row][colEnd] << " ";
        }
        colEnd--;
        
        // Traverse Left
        if (rowStart <= rowEnd) {
            for (int col = colEnd; col >= colStart; col--) {
                std::cout << matrix[rowEnd][col] << " ";
            }
            rowEnd--;
        }
        
        // Traverse Up
        if (colStart <= colEnd) {
            for (int row = rowEnd; row >= rowStart; row--) {
                std::cout << matrix[row][colStart] << " ";
            }
            colStart++;
        }
    }
    std::cout << "\n";
}
```
*   **🔍 Dry Run:**
    *   **Input:** Matrix:
        $$\begin{pmatrix} 1 & 2 & 3 \\ 4 & 5 & 6 \\ 7 & 8 & 9 \end{pmatrix}$$
    *   `rowStart = 0`, `rowEnd = 2`, `colStart = 0`, `colEnd = 2`
    *   **Step 1:** Right from `colStart` to `colEnd` on `rowStart (0)` -> `1 2 3`. `rowStart` becomes 1.
    *   **Step 2:** Down from `rowStart` to `rowEnd` on `colEnd (2)` -> `6 9`. `colEnd` becomes 1.
    *   **Step 3:** Left from `colEnd` to `colStart` on `rowEnd (2)` -> `8 7`. `rowEnd` becomes 1.
    *   **Step 4:** Up from `rowEnd` to `rowStart` on `colStart (0)` -> `4`. `colStart` becomes 1.
    *   **Step 5:** Right from `colStart` to `colEnd` on `rowStart (1)` -> `5`.
    *   **Result:** `1 2 3 6 9 8 7 4 5`.
*   **Complexity:** Time: $O(R \times C)$, Space: $O(1)$.

### 🎯 Solution 5.3: Matrix Transpose
*   **Problem:** Modify a square matrix in-place to transpose it (swap element at `[i][j]` with `[j][i]`).
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

void transposeMatrix(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
}
```
*   **🔍 Dry Run:**
    *   **Input:** Matrix:
        $$\begin{pmatrix} 1 & 2 \\ 3 & 4 \end{pmatrix}$$
    *   `i = 0`: swap `matrix[0][1] (2)` and `matrix[1][0] (3)`. Matrix:
        $$\begin{pmatrix} 1 & 3 \\ 2 & 4 \end{pmatrix}$$
    *   `i = 1`: inner loop starts at `j = 2` (no iteration).
*   **Complexity:** Time: $O(N^2)$, Space: $O(1)$.

### 🎯 Solution 5.4: Rotate Image 90 Degrees Clockwise
*   **Problem:** Rotate an $N \times N$ matrix by 90 degrees clockwise in-place.
*   **C++ Code:**
```cpp
#include <vector>
#include <algorithm>

void rotate(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    
    // Transpose the matrix first
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
    
    // Reverse each row
    for (int i = 0; i < n; i++) {
        std::reverse(matrix[i].begin(), matrix[i].end());
    }
}
```
*   **🔍 Dry Run:**
    *   **Input:**
        $$\begin{pmatrix} 1 & 2 & 3 \\ 4 & 5 & 6 \\ 7 & 8 & 9 \end{pmatrix}$$
    *   **Transpose:**
        $$\begin{pmatrix} 1 & 4 & 7 \\ 2 & 5 & 8 \\ 3 & 6 & 9 \end{pmatrix}$$
    *   **Reverse Rows:**
        $$\begin{pmatrix} 7 & 4 & 1 \\ 8 & 5 & 2 \\ 9 & 6 & 3 \end{pmatrix}$$
*   **Complexity:** Time: $O(N^2)$, Space: $O(1)$.

### 🎯 Solution 5.5: Binary Search in 2D Matrix
*   **Problem:** Search a target value in an $M \times N$ matrix where rows are sorted and the first element of a row is greater than the last element of the previous row.
*   **C++ Code:**
```cpp
#include <vector>

bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) {
    if (matrix.empty()) return false;
    int m = matrix.size();
    int n = matrix[0].size();
    int start = 0, end = m * n - 1;
    
    while (start <= end) {
        int mid = start + (end - start) / 2;
        // Map 1D search position back to 2D row and column indices
        int midElement = matrix[mid / n][mid % n];
        
        if (midElement == target) {
            return true;
        } else if (midElement < target) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return false;
}
```
*   **🔍 Dry Run:**
    *   **Input:** Matrix:
        $$\begin{pmatrix} 1 & 3 & 5 \\ 7 & 9 & 11 \\ 13 & 15 & 17 \end{pmatrix}$$, `target = 9`
    *   `m = 3`, `n = 3`, `start = 0`, `end = 8`
    *   **Iteration 1:** `mid = 4`. Row = `4/3 = 1`, Col = `4%3 = 1`. Element = `matrix[1][1] = 9 == 9`. Return `true`.
*   **Complexity:** Time: $O(\log(M \times N))$, Space: $O(1)$.
