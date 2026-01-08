/*
 *Q2.2 Implement an algorithm to find thr Nth to last element of a singly linked list.
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


    // what is nth to last element - the element that is n nodes from the end of the list
    // Approach:
    // two pointer approach
    // move refPtr n nodes ahead, then move both pointers until refPtr hits the end
    // mainPtr will be at the nth to last node
    // Time Complexity: O(L) where L is the length of the list
    Node* nthToLast(int k) {
        Node* p1 = head;
        Node* p2 = head;

        for(int i=0;i<k;i++){
            if(p1==nullptr) return nullptr; // if k is greater than the length of the list
            p1 = p1->next;
        }
        // what is value of p1 and p2 here?
        // p1 is k nodes ahead of p2
        // p2 is at head
        // now move both pointers until p1 hits the end
        // at that point p2 will be at the nth to last node
        // eg: list = 3->4->3->2->4->1, k=2
        // p1 will be at 3rd node (value 3), p2 at head (value 3)
        // move both pointers:
        // p1=2nd node (value 2), p2=2nd node (value 4)
        // p1=4th node (value 4), p2=3rd node/(value 3)
        // p1=5th node (value 1), p2=4th node(value 2)
        // p1=nullptr, p2=5th node(value 4)
        // return p2

        while(p1!=nullptr){
            p1 = p1->next;
            p2 = p2->next;
        }

        return p2;
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
    list.append(3);
    list.append(4);
    list.append(3);
    list.append(2);
    list.append(4);
    list.append(1);

    cout << "Original List:" << endl;
    list.printList();

    Node* nthNode = list.nthToLast(2);
    if (nthNode) {
        cout << "2nd to last element is: " << nthNode->data << endl;
    } else {
        cout << "The list is shorter than 2 elements." << endl;
    }
    cout << "List after operation (should remain unchanged):" << endl;
    list.printList();

    return 0;
}