/*
 * QUESTION: Implement Stack from Scratch
 * Link: https://www.tutorialspoint.com/javaexamples/data_stack.htm
 * 
 * Description: Implement a LIFO (Last In First Out) stack data structure with standard methods:
 * push(), pop(), top(), isEmpty(), and size().
 */

#include <iostream>
#include <vector>
#include <stdexcept>

// Template-based Stack class implementation using std::vector internally
template <typename T>
class Stack {
private:
    std::vector<T> elements; // Dynamic container to hold stack elements

public:
    // Pushes an element onto the top of the stack
    void push(const T& val) {
        elements.push_back(val);
    }
    
    // Removes the element at the top of the stack
    void pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack Underflow: Cannot pop from an empty stack.");
        }
        elements.pop_back();
    }
    
    // Returns the element at the top of the stack without removing it
    T top() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty: No top element.");
        }
        return elements.back();
    }
    
    // Checks if the stack is empty
    bool isEmpty() const {
        return elements.empty();
    }
    
    // Returns the number of elements in the stack
    size_t size() const {
        return elements.size();
    }
};

/*
 * DRY RUN:
 * Stack<int> s;
 * 
 * | Operation | Elements vector after operation | top() returned | isEmpty() | size() | Note                                      |
 * | :-------- | :------------------------------ | :------------- | :-------- | :----- | :---------------------------------------- |
 * | isEmpty() | {}                              | (Error)        | True      | 0      | Initial state                             |
 * | push(5)   | {5}                             | 5              | False     | 1      | 5 is top                                  |
 * | push(10)  | {5, 10}                         | 10             | False     | 2      | 10 is top                                 |
 * | pop()     | {5}                             | 5              | False     | 1      | 10 is popped                              |
 * | top()     | {5}                             | 5              | False     | 1      | Returns 5                                 |
 * | pop()     | {}                              | (Error)        | True      | 0      | 5 is popped                               |
 * 
 * MEMORIZATION / RECALL SCENARIO:
 * Think of a stack of plates on a table. 
 * You can only place a new plate on the very top of the pile (`push`). 
 * You can only remove the plate currently sitting on the very top (`pop`). 
 * If there are no plates, the pile is empty (`isEmpty`), and you cannot take a plate off (`underflow`).
 * 
 * 1-MINUTE QUICK REVISION:
 * - Stack is a LIFO (Last In First Out) data structure.
 * - Standard operations:
 *   - `push(x)`: inserts element at the end of the vector. (Time: O(1) amortized)
 *   - `pop()`: removes element from the end of the vector. Throws error if empty. (Time: O(1))
 *   - `top()`: returns the last element of the vector. Throws error if empty. (Time: O(1))
 *   - `isEmpty()`: returns true if size is 0. (Time: O(1))
 *   - `size()`: returns vector size. (Time: O(1))
 * - Space Complexity: O(N) where N is the number of elements in the stack.
 */
