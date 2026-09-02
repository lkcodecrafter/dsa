/*
 * QUESTION: Implement Queue from Scratch
 * Link: https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
 * 
 * Description: Implement a FIFO (First In First Out) queue data structure using a circular array representation.
 */

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Queue {
private:
    std::vector<T> arr; // Array to hold queue elements
    int front;          // Pointer to front element
    int rear;           // Pointer to rear element
    int capacity;       // Maximum capacity of the queue
    int curr_size;      // Current size of the queue

public:
    // Constructor to initialize queue with capacity
    Queue(int cap) {
        capacity = cap;
        arr.resize(capacity);
        front = 0;
        rear = capacity - 1;
        curr_size = 0;
    }
    
    // Adds an item to the queue (circular insertion)
    void enqueue(const T& item) {
        if (isFull()) {
            throw std::overflow_error("Queue Overflow: Cannot enqueue to a full queue.");
        }
        rear = (rear + 1) % capacity; // Advance rear circularly
        arr[rear] = item;
        curr_size++;
    }
    
    // Removes an item from the queue (circular deletion)
    void dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue Underflow: Cannot dequeue from an empty queue.");
        }
        front = (front + 1) % capacity; // Advance front circularly
        curr_size--;
    }
    
    // Returns the front item
    T getFront() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty: No front element.");
        }
        return arr[front];
    }
    
    // Returns the rear item
    T getRear() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty: No rear element.");
        }
        return arr[rear];
    }
    
    // Checks if the queue is empty
    bool isEmpty() const {
        return curr_size == 0;
    }
    
    // Checks if the queue is full
    bool isFull() const {
        return curr_size == capacity;
    }
    
    // Returns the current number of elements
    int size() const {
        return curr_size;
    }
};

/*
 * DRY RUN (Queue of capacity = 3):
 * Queue<int> q(3);
 * Initial: front = 0, rear = 2, curr_size = 0
 * 
 * | Operation  | Front ptr | Rear ptr | curr_size | arr State     | getFront() | getRear() | Note                                      |
 * | :--------- | :-------- | :------- | :-------- | :------------ | :--------- | :-------- | :---------------------------------------- |
 * | enqueue(5) | 0         | 0        | 1         | {5, -, -}     | 5          | 5         | rear = (2+1)%3 = 0                        |
 * | enqueue(10)| 0         | 1        | 2         | {5, 10, -}    | 5          | 10        | rear = (0+1)%3 = 1                        |
 * | dequeue()  | 1         | 1        | 1         | {5, 10, -}    | 10         | 10        | front = (0+1)%3 = 1                       |
 * | enqueue(15)| 1         | 2        | 2         | {5, 10, 15}   | 10         | 15        | rear = (1+1)%3 = 2                        |
 * | enqueue(20)| 1         | 0        | 3         | {20, 10, 15}  | 10         | 20        | rear = (2+1)%3 = 0 (circular loop)        |
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Think of people standing in a line at a ticket booth. 
 * People join the line at the back (`rear` / `enqueue`) and leave at the front (`front` / `dequeue`). 
 * To make optimal use of seat capacity without sliding everyone forward, 
 * when the line reaches the end of the benches, the next person sits on the first bench at the front (`circular array`).
 * 
 * 1-MINUTE QUICK REVISION:
 * - Queue is a FIFO (First In First Out) data structure.
 * - Circular queue uses modulo arithmetic: index is updated as `(index + 1) % capacity`.
 * - State variables: `front` (deletions), `rear` (insertions), `capacity`, and `curr_size`.
 * - Operations:
 *   - `enqueue(x)`: `rear = (rear + 1) % capacity`, `arr[rear] = x`, `curr_size++`. (Time: O(1))
 *   - `dequeue()`: `front = (front + 1) % capacity`, `curr_size--`. (Time: O(1))
 *   - `getFront()`: returns `arr[front]`. (Time: O(1))
 *   - `getRear()`: returns `arr[rear]`. (Time: O(1))
 * - Space Complexity: O(Capacity)
 */
