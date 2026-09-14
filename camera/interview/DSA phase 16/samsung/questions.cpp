#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  bool findprim(int n) {

    if (n < 2)
      return false;

    for (int i = 2; i <= n / 2; i++) {
      if (n % i == 0) {
        return false;
      }
    }
    return true;
  }

  int primeSum(int n) {
    // Code here
    int sum = 0;
    for (int i = 2; i <= n; i++) {
      if (findprim(i)) {
        sum += i;
      }
    }
    return sum;
  }

  // Minimum Bit Flips to convert A to B
  int minBitFlips(int A, int B) {
    int n = A ^ B;
    int count = 0;
    while (n != 0) {
      n &= (n - 1);
      count++;
    }
    return count;
  }

  // Heap sort
  void heapify(vector<int> &arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 1;
    if (l < n && arr[l] > arr[largest]) {
      l = largest;
    }
    if (r < n && arr[r] > arr[largest]) {
      r = largest;
    }

    while (largest != i) {
      int temp = arr[i];
      arr[i] = arr[largest];
      arr[largest] = temp;

      heapify(arr, n, largest);
    }
  }

  void buildHeap(vector<int> &arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i > 0; i--) {
      heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
      int temp = arr[0];
      arr[0] = arr[i];
      arr[i] = temp;
      heapify(arr, n, 0);
    }
  }

  /**
   *  front                  rear
   * ↓ [10] → [20] → [30] → [40] → NULL
   * ↑ add new node here
   */

  // Full Implementations of Queue Using Linked List
  class Node {
  public:
    int data;
    Node *next;

    Node(int val) {
      data = val;
      next = nullptr;
    }
  };

  class myQueue {

    Node *front;
    Node *rear;
    int qsize;

  public:
    myQueue() {
      // Initialize your data members
      front = rear = nullptr;
      qsize = 0;
    }

    bool isEmpty() {
      // check if the queue is empty
      return front == nullptr;
    }

    void enqueue(int x) {
      // Adds an element x at the rear of the queue
      Node *node = new Node(x);
      if (rear == nullptr || front == nullptr) {
        front = rear = node;
      } else {
        rear->next = node;
        rear = node;
      }
      qsize++;
    }

    void dequeue() {
      // Removes the front element of the queue
      Node *temp = front;
      int nodeDelet = temp->data;
      front = front->next;
      if (front == nullptr) {
        rear = nullptr;
      }
      delete temp;
      qsize--;
    }

    int getFront() {
      // Returns the front element of the queue
      // If queue is empty, return -1
      if (isEmpty()) {
        return -1;
      } else {
        return front->data;
      }
    }

    int size() {
      // Returns the current size of the queue.
      return qsize;
    }
  };

  // Full Implementation of Stack using Array
  class myStack {

    int *arr;
    int top;
    int capacity;

  public:
    myStack(int n) {
      capacity = n;
      arr = new int[capacity];
      top = -1;
    }

    bool isEmpty() { return top == -1; }

    bool isFull() { return top == capacity - 1; }

    void push(int x) {
      if (top == capacity - 1) {
        return;
      }
      arr[++top] = x;
    }

    void pop() {
      if (isEmpty()) {
        return;
      }
      arr[top--];
    }

    int peek() {
      if (isEmpty()) {
        return -1;
      }
      // Returns the top element of the stack
      return arr[top];
    }
  };

  // Merge two sorted arrays without extra space
};

int main() {
  int n;
  cin >> n;
  Solution sol;
  cout << sol.primeSum(n);
  return 0;
}