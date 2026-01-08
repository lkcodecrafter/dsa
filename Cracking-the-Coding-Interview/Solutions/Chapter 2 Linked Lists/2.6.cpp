/*
Q2.6 Palindrome: Implement a function to check if a linked list is a palindrome.
    EXAMPLE 
    input: 1 -> 2 -> 3 -> 2 -> 1 
    Output: true
*/

#include <iostream>
#include <unordered_set>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;
    LinkedList() : head(nullptr) {}

    void append(int val) {
        if (!head) {
            head = new Node(val);
            return;
        }
        Node* curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = new Node(val);
    }

    bool isPalindrome() {
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node* secondHalf = slow;
        Node* prev = nullptr;
        while (secondHalf) {
            Node* nextNode = secondHalf->next;
            secondHalf->next = prev;
            prev = secondHalf;
            secondHalf = nextNode;
        }
        Node* firstHalf = head;
        while (prev) {
            if (firstHalf->data != prev->data) {
                return false;
            }
            firstHalf = firstHalf->next;
            prev = prev->next;
        }
        return true;
    }

    void printList() {
        Node* curr = head;
        while (curr) {
            cout << curr->data << " -> ";
            curr = curr->next;
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    LinkedList list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(2);
    list.append(1);

    cout << "Original List:" << endl;
    list.printList();

    if (list.isPalindrome()) {
        cout << "The linked list is a palindrome." << endl;
    } else {
        cout << "The linked list is not a palindrome." << endl;
    }

    return 0;
}

//  Time Complexity: O(n)
// Space Complexity: O(1)


// Alternate solution - O(n) time, O(n) space
//
// 1. Save 1st half of list in stack
// 2. Compare 2nd half of list to 1st half of list


// Alternate solution - O(n) time, O(n) space
//
// 1. Deep copy list.
// 2. Reverse it.
// 3. Compare it to original.