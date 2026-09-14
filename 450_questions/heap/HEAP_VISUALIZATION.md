# 📊 Complete Heap & Priority Queue Visualizations Guide

Welcome to the comprehensive visual reference for all 18 Heap & Priority Queue problems in the **450 DSA Cracker Sheet**. 

> [!TIP]
> **Interactive Visualizer Available!**
> Open [`heap_visualizer.html`](file:///c:/Users/lalit.k/lalit/d/dsa/450_questions/heap/heap_visualizer.html) in your browser for dynamic step-by-step animations, dual-heap streaming balancing, and custom input testing.

---

## 📑 Table of Contents

1. [Fundamental Tree-to-Array Mechanics](#1-fundamental-tree-to-array-mechanics)
2. [Problem 01: Build Heap from Array (O(N) Sift-Down)](#problem-01-build-heap-from-array)
3. [Problem 02: Heap Sort (In-Place O(N log N))](#problem-02-heap-sort)
4. [Problem 03: Sliding Window Maximum](#problem-03-sliding-window-maximum)
5. [Problem 04: K Largest Elements](#problem-04-k-largest-elements)
6. [Problem 05: Kth Smallest and Largest Element](#problem-05-kth-smallest-and-largest-element)
7. [Problem 06: Merge K Sorted Arrays](#problem-06-merge-k-sorted-arrays)
8. [Problem 07: Merge Two Binary Max Heaps](#problem-07-merge-two-binary-max-heaps)
9. [Problem 08: K-th Largest Sum Contiguous Subarray](#problem-08-k-th-largest-sum-contiguous-subarray)
10. [Problem 09: Reorganize String (No Adjacent Same)](#problem-09-reorganize-string)
11. [Problem 10: Merge K Sorted Linked Lists](#problem-10-merge-k-sorted-linked-lists)
12. [Problem 11: Smallest Range in K Lists](#problem-11-smallest-range-in-k-lists)
13. [Problem 12: Find Median in a Data Stream (Two Heaps)](#problem-12-find-median-in-a-data-stream)
14. [Problem 13: Check if Binary Tree is Heap](#problem-13-check-if-binary-tree-is-heap)
15. [Problem 14: Connect N Ropes with Minimum Cost](#problem-14-connect-n-ropes-with-minimum-cost)
16. [Problem 15: Convert BST to Min Heap](#problem-15-convert-bst-to-min-heap)
17. [Problem 16: Convert Min Heap to Max Heap](#problem-16-convert-min-heap-to-max-heap)
18. [Problem 17: Rearrange Characters (Frequency Heap)](#problem-17-rearrange-characters)
19. [Problem 18: Minimum Sum of Two Numbers from Digits](#problem-18-minimum-sum-of-two-numbers-from-digits)

---

## 1. Fundamental Tree-to-Array Mechanics

A **Binary Heap** is a complete binary tree stored compactly in a contiguous array without explicit pointer overhead.

```
                  Index 0 (Root)
                 /              \
         Index 1                 Index 2
        /       \               /       \
    Index 3   Index 4       Index 5   Index 6
    /     \
Index 7 Index 8
```

### 🧮 Mathematical Index Relationships (0-Indexed)

| Relationship | Formula | Example for node at `i = 2` |
| :----------- | :------ | :-------------------------- |
| Parent       | `floor((i - 1) / 2)` | `(2 - 1) / 2 = 0` (Root)   |
| Left Child   | `2 * i + 1`          | `2 * 2 + 1 = 5`            |
| Right Child  | `2 * i + 2`          | `2 * 2 + 2 = 6`            |
| Last Non-Leaf| `(n / 2) - 1`        | For `n = 7`: `(7/2) - 1 = 2` |

---

## Problem 01: Build Heap from Array

- **File**: [`01_build_heap_from_array.cpp`](file:///c:/Users/lalit.k/lalit/d/dsa/450_questions/heap/01_build_heap_from_array.cpp)
- **Time Complexity**: $O(N)$ (Sum of $\sum \frac{h}{2^h} = O(N)$)
- **Space Complexity**: $O(\log N)$ recursion stack

### 🌲 Visual Topology & Sift-Down Walkthrough

Given input array: `[4, 10, 3, 5, 1]` ($n = 5$)

```
    [Initial Array as Tree]                   [After Heapify(i = 1)]                  [Final Max Heap after Heapify(0)]
             4 (i=0)                                 4 (i=0)                                    10 (i=0)
           /   \                                   /   \                                      /    \
     (i=1)10    3 (i=2)                      (i=1)10    3 (i=2)                         (i=1)5      3 (i=2)
         /  \                                    /  \                                       / \
   (i=3)5    1 (i=4)                       (i=3)5    1 (i=4)                          (i=3)4   1 (i=4)
   (Last non-leaf = (5/2)-1 = 1)           (10 > 5, 1 -> Valid)                       (4 swapped with 10, then 5)
```

### 📋 Dry Run Table

| Step | Index `i` | Value `arr[i]` | Left Child `arr[2i+1]` | Right Child `arr[2i+2]` | Largest Found | Action Taken | Array State |
| :--- | :-------- | :------------- | :--------------------- | :---------------------- | :------------ | :----------- | :---------- |
| 1    | `i = 1`   | 10             | `arr[3] = 5`           | `arr[4] = 1`            | `arr[1] = 10` | No swap      | `[4, 10, 3, 5, 1]` |
| 2    | `i = 0`   | 4              | `arr[1] = 10`          | `arr[2] = 3`            | `arr[1] = 10` | Swap 4 & 10  | `[10, 4, 3, 5, 1]` |
| 2b   | `i = 1`   | 4              | `arr[3] = 5`           | `arr[4] = 1`            | `arr[3] = 5`  | Swap 4 & 5   | `[10, 5, 3, 4, 1]` |

---

## Problem 02: Heap Sort

- **File**: [`02_heap_sort.cpp`](file:///c:/Users/lalit.k/lalit/d/dsa/450_questions/heap/02_heap_sort.cpp)
- **Time Complexity**: $O(N \log N)$
- **Space Complexity**: $O(1)$ Auxiliary (In-place)

```
Phase 1: Build Max-Heap             Phase 2: Repeatedly Extract Max & Swap to End
 [ 10 |  5   3   4   1 ]             [  1 |  5   3   4 ] || [ 10 ]  -> Sift Down(0)
   ^                                   ^                  Sorted
 Root is Max                         Swap root with end
```

---

## Problem 06 & 10: Merge K Sorted Arrays / Linked Lists

- **Files**: [`06_merge_k_sorted_arrays.cpp`](file:///c:/Users/lalit.k/lalit/d/dsa/450_questions/heap/06_merge_k_sorted_arrays.cpp), [`10_merge_k_sorted_linked_lists.cpp`](file:///c:/Users/lalit.k/lalit/d/dsa/450_questions/heap/10_merge_k_sorted_linked_lists.cpp)
- **Pattern**: Min-Heap of size $K$ storing `{value, array_index, element_index}`.

### 🔄 Multi-way Merge Priority Queue Workflow

```
 Array 0: [ 1,  4,  7 ] ----> Push (1, 0, 0)
 Array 1: [ 2,  5,  8 ] ----> Push (2, 1, 0)   ===> Min-Heap Size K: [ (1,0,0), (2,1,0), (3,2,0) ]
 Array 2: [ 3,  6,  9 ] ----> Push (3, 2, 0)                             |
                                                                        v Pop min (1) -> Output: [1]
                                                          Push next from Array 0: (4, 0, 1)
```

---

## Problem 11: Smallest Range in K Lists

- **File**: [`11_smallest_range_in_k_lists.cpp`](file:///c:/Users/lalit.k/lalit/d/dsa/450_questions/heap/11_smallest_range_in_k_lists.cpp)
- **Idea**: Maintain Min-Heap of size $K$ + `currMax` variable. At each step, range is `[minHeap.top(), currMax]`. Pop min, advance its list pointer, and update `currMax`.

```
List 1: [ 4, 10, 15, 24 ]
List 2: [ 0,  9, 12, 20 ]   ===> Min-Heap: { (0, L2), (4, L1), (5, L3) }, currMax = 5
List 3: [ 5, 18, 22, 30 ]        Current Range: [0, 5] (Span: 5)
```

---

## Problem 12: Find Median in a Data Stream

- **File**: [`12_median_in_a_stream.cpp`](file:///c:/Users/lalit.k/lalit/d/dsa/450_questions/heap/12_median_in_a_stream.cpp)
- **Pattern**: Dual Heap (Two Heaps Partitioning)

```
        Smaller Half Numbers                   Larger Half Numbers
     +-------------------------+            +-------------------------+
     |     LEFT: MAX-HEAP      |            |     RIGHT: MIN-HEAP     |
     |                         |            |                         |
     |          [ 3 ] <--- Max |            | Min ---> [ 5 ]          |
     |         /     \         |            |         /     \         |
     |       [2]     [1]       |            |       [8]     [9]       |
     +-------------------------+            +-------------------------+
             Size: k or k+1                           Size: k

                                Median Formula:
  - If Left.size() > Right.size()       ===> Median = Left.top()
  - If Left.size() == Right.size()      ===> Median = (Left.top() + Right.top()) / 2.0
```

### 📋 Dual-Heap Balancing Dry Run

| Incoming Number | Target Heap | Pre-Balance State (L / R) | Rebalance Action | Post-Balance State | Calculated Median |
| :-------------- | :---------- | :------------------------ | :--------------- | :----------------- | :---------------- |
| 5               | Left        | `[5]` / `[]`              | None             | `[5]` / `[]`       | **5.0**           |
| 15              | Right       | `[5]` / `[15]`            | None             | `[5]` / `[15]`     | `(5+15)/2 = 10.0` |
| 1               | Left        | `[5, 1]` / `[15]`         | None             | `[5, 1]` / `[15]`  | **5.0**           |
| 3               | Left        | `[5, 3, 1]` / `[15]`      | Move 5 to Right  | `[3, 1]` / `[5, 15]` | `(3+5)/2 = 4.0` |

---

## Problem 14: Connect N Ropes with Minimum Cost

- **File**: [`14_connect_n_ropes_min_cost.cpp`](file:///c:/Users/lalit.k/lalit/d/dsa/450_questions/heap/14_connect_n_ropes_min_cost.cpp)
- **Pattern**: Greedy Huffman-style Min-Heap combining

```
Initial Ropes: [ 4, 3, 2, 6 ]

Step 1: Pop 2 and 3  ---> Combine: 2 + 3 = 5  (Cost = 5, Heap = [4, 5, 6])
Step 2: Pop 4 and 5  ---> Combine: 4 + 5 = 9  (Cost = 5 + 9 = 14, Heap = [6, 9])
Step 3: Pop 6 and 9  ---> Combine: 6 + 9 = 15 (Cost = 14 + 15 = 29, Heap = [15])

Total Minimum Cost = 29
```

---

## Problem 15: Convert BST to Min Heap

- **File**: [`15_convert_bst_to_min_heap.cpp`](file:///c:/Users/lalit.k/lalit/d/dsa/450_questions/heap/15_convert_bst_to_min_heap.cpp)
- **Constraint**: Binary Tree must satisfy Min-Heap property (`parent < children`) and BST Left < Right property (`left < right`).

```
       [Input BST]                         [1. Inorder Traversal]                [2. Preorder Fill to Min-Heap]
            4                                    Sorted Array:                                1
          /   \                                [ 1, 2, 3, 4, 5, 6, 7 ]                      /   \
         2     6                                                                           2     5
        / \   / \                                                                         / \   / \
       1   3 5   7                                                                       3   4 6   7
```

---

## ⚡ 1-Minute Quick Recall Cheatsheet

1. **Top K / Kth Element**:
   - For **Kth Smallest** $\rightarrow$ Use **Max-Heap** of size $K$ (prunes large elements).
   - For **Kth Largest** $\rightarrow$ Use **Min-Heap** of size $K$ (prunes small elements).
2. **Median in Stream**: Two Heaps (Left Max-Heap $\le$ Right Min-Heap, size difference $\le 1$).
3. **K-Way Merge**: Min-Heap of size $K$ containing first elements of active streams.
4. **Greedy Minimum Combinations**: Repeatedly extract 2 smallest elements from Min-Heap (e.g. Connect Ropes).
5. **Array Representation**: Left child = `2i + 1`, Right child = `2i + 2`, Parent = `(i - 1) / 2`.
