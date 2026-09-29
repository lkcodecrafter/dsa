/*
QUESTION:-
Write a program to search for a given element in an array and return its index
if found, otherwise return -1.

APPROACH:-
-> The idea is to traverse the array using loop and when the element
is equal to k return the same
*/

// CODE:-
int linear_search(int arr[], int n, int k) {
  for (int i = 0; i < n; i++) {
    if (arr[i] == k)
      return i;
  }
  return -1;
}

// TIME COMPLEXITY = O(N)
// SPACE COMPLEXITY = O(0)