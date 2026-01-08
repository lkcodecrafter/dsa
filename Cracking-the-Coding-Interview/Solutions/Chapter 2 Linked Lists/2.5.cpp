/*
Q2.5 Sum Lists: You have two numbers represented by a linked list, where each node contains a single 
digit. The digits are stored in reverse order, such that the 1's digit is at the head of the iist. Write a 
function that adds the two numbers and returns the sum as a linked list. 
EXAMPLE 
input; (7-> 1 -> 6) + (S -> 9 -> 2). That is, 617 + 295. 
Output; 2 -> 1 -> 9.That is, 912. 
FOLLOW UP 
Suppose the digits are stored in forward order. Repeat the above problem. 
Input (6 -> 1 -> 7) + (2 -> 9 -> S). That is, 617 + 295. 
Output: 9 -> 1 -> 2.That is, 912. 
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

    void sumLists(LinkedList& l1, LinkedList& l2) {
        Node* n1 = l1.head;
        Node* n2 = l2.head;
        int carry = 0;

        while (n1 || n2 || carry) {
            int val1 = n1 ? n1->data : 0;
            int val2 = n2 ? n2->data : 0;
            int sum = val1 + val2 + carry;
            carry = sum / 10;
            this->append(sum % 10); // what happens when this->append is called here? 
            // It appends a new node with the value of sum % 10 to the current linked list (the one on which sumLists is called).
            // This effectively builds the resulting sum linked list as we iterate through the digits of the two input lists.
            // For example, if the sum of the digits (including carry) is 15,
            // we append a node with value 5 and set carry to 1 for the next iteration.
            // This continues until all digits from both lists have been processed and any remaining carry is added.
            // example : if we have two linked lists representing the numbers 617 (7 -> 1 -> 6) and 295 (5 -> 9 -> 2),
            // the resulting linked list will represent the number 912 (2 -> 1 -> 9) after processing all digits and carry.
            // This method ensures that the sum is correctly represented in reverse order as required.
            // The final linked list will contain the digits of the sum in reverse order, just like the input lists.
            // This is crucial for correctly representing the sum of the two numbers as specified in the problem statement.
            // Dry run with example input to understand better.
            // For input (7 -> 1 -> 6) + (5 -> 9 -> 2):
            // Iteration 1: sum = 7 + 5 + 0 = 12, append 2, carry 1
            // Iteration 2: sum = 1 + 9 + 1 = 11, append 1, carry 1
            // Iteration 3: sum = 6 + 2 + 1 = 9, append 9, carry 0  
            // Resulting list: 2 -> 1 -> 9
            
            if (n1) n1 = n1->next;
            if (n2) n2 = n2->next;
        }
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
    LinkedList l1;
    l1.append(7);
    l1.append(1);
    l1.append(6); // represents the number 617

    LinkedList l2;
    l2.append(5);
    l2.append(9);
    l2.append(2); // represents the number 295

    cout << "List 1:" << endl;
    l1.printList();
    cout << "List 2:" << endl;
    l2.printList();

    LinkedList result;
    result.sumLists(l1, l2);

    cout << "Sum List:" << endl;
    result.printList(); // should represent the number 912 (2 -> 1 -> 9)

    //it's should be 1219?
    // No, the sum of 617 and 295 is 912, not 1219.
    return 0;
}