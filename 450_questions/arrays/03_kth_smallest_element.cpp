/*
 * QUESTION: Find the "Kth" min and max element of an array
 * Link: https://practice.geeksforgeeks.org/problems/kth-smallest-element/0
 * 
 * Input: arr[] = {7, 10, 4, 3, 20, 15}, k = 3
 * Output: 3rd Smallest = 7
 */

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

// Custom comparator functor to demonstrate STL priority_queue mechanics.
// For Kth smallest, we use a Max-Heap.
// For Kth largest, we can use a Min-Heap.
struct GreaterThan {
    // If operator() returns true, 'left' has lower priority than 'right'
    // in std::priority_queue, which creates a Min-Heap.
    bool operator()(int left, int right) const {
        return left > right;
    }
};

/*
 * DETAILED FUNCTOR & STL MECHANICS:
 * - Functor Instantiation: `std::priority_queue<int, std::vector<int>, GreaterThan> min_heap;`
 *   Here, `GreaterThan` is passed as the comparator class. The queue instantiates this struct
 *   internally and calls its `operator()` to maintain heap properties.
 * - Internal Call: Whenever a new element is pushed, the container compares it with its parent using
 *   `comp(element, parent)`. If it returns `true` (i.e. element > parent), the child is bubbled down
 *   (or parent is bubbled up) to ensure the smallest element stays at the top.
 * - Boolean Return Value: Returning `true` means the first argument has less priority. 
 *   In a min-heap, larger values have lower priority (stay deeper in the tree), hence we return `left > right`.
 */

// Returns the Kth smallest element using a Max-Heap (std::priority_queue<int>)
int kthSmallest(const std::vector<int>& arr, int k) {
    // Max-heap stores the k smallest elements seen so far.
    // The largest of these k elements is at the top.
    std::priority_queue<int> max_heap;
    
    for (int num : arr) {
        max_heap.push(num);
        // If heap size exceeds k, pop the maximum element.
        if (max_heap.size() > static_cast<size_t>(k)) {
            max_heap.pop();
        }
    }
    return max_heap.top();
}

// Returns the Kth largest element using a Min-Heap with custom comparator GreaterThan
int kthLargest(const std::vector<int>& arr, int k) {
    std::priority_queue<int, std::vector<int>, GreaterThan> min_heap;
    
    for (int num : arr) {
        min_heap.push(num);
        // If heap size exceeds k, pop the minimum element.
        if (min_heap.size() > static_cast<size_t>(k)) {
            min_heap.pop();
        }
    }
    return min_heap.top();
}

/*
 * DRY RUN (kthSmallest with arr = {7, 10, 4, 3, 20, 15}, k = 3):
 * 
 * | Step | Element | Heap Content (Size <= 3) | Action/Popped element |
 * | :--- | :------ | :----------------------- | :-------------------- |
 * | 1    | 7       | {7}                      | Push                  |
 * | 2    | 10      | {10, 7}                  | Push                  |
 * | 3    | 4       | {10, 7, 4}               | Push                  |
 * | 4    | 3       | {10, 7, 4, 3} -> {7,4,3} | Push 3, Pop 10 (Max)  |
 * | 5    | 20      | {20, 7, 4, 3} -> {7,4,3} | Push 20, Pop 20 (Max) |
 * | 6    | 15      | {15, 7, 4, 3} -> {7,4,3} | Push 15, Pop 15 (Max) |
 * 
 * Top of heap: 7 (3rd smallest element)
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * To find the Kth smallest, build a ceiling (max-heap) of size K. 
 * Any incoming candidate pushes down on the ceiling; if it is smaller than the ceiling's maximum, 
 * the ceiling's maximum gets kicked out.
 * 
 * 1-MINUTE QUICK REVISION:
 * - For Kth smallest: maintain a Max-Heap of size K. If heap size > K, `pop()`. Top is the answer.
 * - For Kth largest: maintain a Min-Heap of size K. If heap size > K, `pop()`. Top is the answer.
 * - Time Complexity: O(N log K)
 * - Space Complexity: O(K)
 */
