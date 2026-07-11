#include <iostream>
#include <set>
#include <vector>

using namespace std;

/*
What your code does correctly
✅ Compares adjacent elements.
✅ Swaps them when they are in the wrong order.
✅ After each pass, the largest unsorted element moves to its correct position.
✅ Uses the flag optimization to stop early if the array is already sorted.

Time Complexity
Best Case: O(n) (already sorted because flag remains false)
Average Case: O(n²)
Worst Case: O(n²)
Space Complexity
O(1) (in-place sorting)

*/

void bubbleSort(vector<int> &arr) {
  for (int i = 0; i < arr.size() - 1; i++) {
    bool flag = false;
    for (int j = 0; j < arr.size() - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
        flag = true;
      }
    }
    if (!flag) {
      break;
    }
  }
}

/*

How it works

For each element:

Store the current element as key.
Compare it with elements on its left.
Shift all larger elements one position to the right.
Insert key into its correct position.

Complexity
Best Case (already sorted): O(n)
Average Case: O(n²)
Worst Case (reverse sorted): O(n²)
Space Complexity: O(1) (in-place)

*/

void insertionSort(vector<int> &arr) {
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

/*
How it works

For each position i:

Assume arr[i] is the minimum element.
Search the remaining unsorted portion of the array for the actual minimum.
Swap the minimum element with arr[i].

Complexity
Best Case: O(n²)
Average Case: O(n²)
Worst Case: O(n²)
Space Complexity: O(1)

Unlike Bubble Sort and Insertion Sort, Selection Sort performs the same number
of comparisons even if the array is already sorted

Your code:


*/
void selectionSort(vector<int> &arr) {
  int n = arr.size();
  for (int i = 0; i < n; i++) {
    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }
    swap(arr[i], arr[minIndex]);
  }
}

// Leetcode 26. Remove Duplicates from Sorted Array
// [1,1,2]

int removeDuplicates(vector<int> &nums) {
  int k = 1;
  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] != nums[i - 1]) {
      nums[k] = nums[i];
      k++;
    }
  }
  return k;
}

/* 121. Best Time to Buy and Sell Stock
 You are given an array prices where prices[i] is the price of a given stock
 on the i-th day.
 You want to maximize your profit by choosing a single day to buy one stock
 and choosing a different day in the future to sell that stock.
 Return the maximum profit you can achieve from this transaction. If you
 cannot achieve any profit, return 0.

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit =
6-1 = 5.

*/
int maxProfit(vector<int> &prices) {
  int buy = prices[0];
  int profit = buy;
  int maxProfit = 0;
  for (int i = 1; i < prices.size(); i++) {
    if (buy > prices[i]) {
      buy = prices[i];
    } else {
      profit = prices[i] - buy;

      if (profit > maxProfit) {
        maxProfit = profit;
      }
    }
  }

  return maxProfit;
}

/*
122. Best Time to Buy and Sell Stock II
Yo  u are given an array prices where prices[i] is the price of a given stock
on the i-th day.
You want to maximize your profit by choosing any number of transactions and
selling the stock on different days. But you cannot engage in multiple
transactions at the same time (you must sell the stock before you buy again).
Return the maximum profit you can achieve.

Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 3.
Total profit = 4 + 3 = 7.

Example 2:
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 4.
*/
int maxProfit2(vector<int> &prices) {
  int profit = 0;
  for (int i = 1; i < prices.size(); i++) {
    if (prices[i] > prices[i - 1]) {
      profit += prices[i] - prices[i - 1];
    }
  }
  return profit;
}

/*
189. Rotate Array

means copy all the elements of result into nums.

Before the assignment

why

nums = res;

Suppose:

nums   = {1,2,3,4,5,6,7}
result = {5,6,7,1,2,3,4}

*/

void rotate(vector<int> &nums, int k) {
  int n = nums.size();
  k %= n;
  vector<int> res(n);
  for (int i = 0; i < n; i++) {
    res[(i + k) % n] = nums[i];
  }
  nums = res;
}

// 217. Contains Duplicate

bool containsDuplicate(vector<int> &nums) {
  int n = nums.size();
  /*bubbleSort(nums);
  for (int i = 0; i < n; i++) {
    if (nums[i] == nums[i + 1]) {
      return true;
    }
  }*/

  set<int> seen;
  for (int i = 0; i < n; i++) {
    if (seen.count(nums[i])) {
      return true;
    } else {
      seen.insert(nums[i]);
    }
  }
  return false;
}

/*
136. Single Number

*/
int singleNumber(vector<int> &nums) {
  int x = nums[0];
  int n = nums.size();
  for (int i = 1; i < n; i++) {
    x ^= nums[i];
  }

  return x;
}

// Array-7 | 349. Intersection of Two Arrays

int main() {

  vector<int> arr = {1, 23, 5, 6, 2};

  // selectionSort(arr);

  vector<int> nums = {1, 1, 2, 2, 3, 4};
  cout << containsDuplicate(arr);
}