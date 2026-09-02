/*
 * QUESTION: Find the Union and Intersection of two sorted arrays
 * Link: https://practice.geeksforgeeks.org/problems/union-of-two-arrays/0
 *
 * Input: arr1[] = {1, 2, 4, 5, 6}, arr2[] = {2, 3, 5, 7}
 * Output: Union = {1, 2, 3, 4, 5, 6, 7}, Intersection = {2, 5}
 */

#include <iostream>
#include <vector>

// Finds the union of two sorted vectors (with duplicates removed).
std::vector<int> findUnion(const std::vector<int> &arr1,
                           const std::vector<int> &arr2) {
  std::vector<int> union_res;
  size_t i = 0, j = 0;

  while (i < arr1.size() && j < arr2.size()) {
    // Skip duplicate elements in arr1
    if (i > 0 && arr1[i] == arr1[i - 1]) {
      i++;
      continue;
    }
    // Skip duplicate elements in arr2
    if (j > 0 && arr2[j] == arr2[j - 1]) {
      j++;
      continue;
    }

    if (arr1[i] < arr2[j]) {
      if (union_res.empty() || union_res.back() != arr1[i]) {
        union_res.push_back(arr1[i]);
      }
      i++;
    } else if (arr2[j] < arr1[i]) {
      if (union_res.empty() || union_res.back() != arr2[j]) {
        union_res.push_back(arr2[j]);
      }
      j++;
    } else {
      if (union_res.empty() || union_res.back() != arr1[i]) {
        union_res.push_back(arr1[i]);
      }
      i++;
      j++;
    }
  }

  // Append remaining elements of arr1
  while (i < arr1.size()) {
    if (i == 0 || arr1[i] != arr1[i - 1]) {
      if (union_res.empty() || union_res.back() != arr1[i]) {
        union_res.push_back(arr1[i]);
      }
    }
    i++;
  }

  // Append remaining elements of arr2
  while (j < arr2.size()) {
    if (j == 0 || arr2[j] != arr2[j - 1]) {
      if (union_res.empty() || union_res.back() != arr2[j]) {
        union_res.push_back(arr2[j]);
      }
    }
    j++;
  }

  return union_res;
}

// Finds the intersection of two sorted vectors.
std::vector<int> findIntersection(const std::vector<int> &arr1,
                                  const std::vector<int> &arr2) {
  std::vector<int> intersection_res;
  size_t i = 0, j = 0;

  while (i < arr1.size() && j < arr2.size()) {
    // Skip duplicate elements in arr1
    if (i > 0 && arr1[i] == arr1[i - 1]) {
      i++;
      continue;
    }

    if (arr1[i] < arr2[j]) {
      i++;
    } else if (arr2[j] < arr1[i]) {
      j++;
    } else {
      // Equal elements found
      if (intersection_res.empty() || intersection_res.back() != arr1[i]) {
        intersection_res.push_back(arr1[i]);
      }
      i++;
      j++;
    }
  }

  return intersection_res;
}

/*
 * DRY RUN (for findIntersection with arr1={1,2,4,5,6}, arr2={2,3,5,7}):
 *
 * | Step | i | j | arr1[i] | arr2[j] | Comparison | Action               |
 * Intersection state | | :--- | :-| :-| :------ | :------ | :--------- |
 * :------------------ | :----------------- | | Init | 0 | 0 | 1       | 2 | 1 <
 * 2      | i++                 | {}                 | | 1    | 1 | 0 | 2 | 2 |
 * 2 == 2     | push, i++, j++      | {2}                | | 2    | 2 | 1 | 4 |
 * 3       | 4 > 3      | j++                 | {2}                | | 3    | 2
 * | 2 | 4       | 5       | 4 < 5      | i++                 | {2} | | 4    | 3
 * | 2 | 5       | 5       | 5 == 5     | push, i++, j++      | {2, 5} | | 5 | 4
 * | 3 | 6       | 7       | 6 < 7      | i++                 | {2, 5} | | 6 | 5
 * | 3 | -       | -       | Loop ends  | i == arr1.size()    | {2, 5} |
 *
 * MEMORIZATION / RECALL SCENARIO:
 * Imagine two tracks running parallelly.
 * Two runners start at the beginning.
 * The runner on the lower value track takes a step forward.
 * If they are standing at the same value, they note it down (intersection), and
 * both step forward.
 *
 * 1-MINUTE QUICK REVISION:
 * - Two pointers `i = 0` and `j = 0`.
 * - For Union: Add the smaller element and increment its pointer (handling
 * duplicates). If equal, add once and increment both.
 * - For Intersection: If equal, add to result and increment both. Otherwise,
 * increment the pointer of the smaller element.
 * - Time Complexity: O(N + M) where N and M are the sizes of the arrays.
 * - Space Complexity: O(1) auxiliary space (excluding result storage).
 */
