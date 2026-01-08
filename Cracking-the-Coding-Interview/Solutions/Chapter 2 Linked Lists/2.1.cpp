/*
 *Q2.1 Write code to remove duplicates from an unsorted linked list.
 *FOOLOW UP
 *How would you solve this problem if a temporary buffer is not allowed?
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

    void removeDuplicatesWithBuffer() {
        unordered_set<int> seen;
        Node* curr = head;
        Node* prev = nullptr;

        while (curr) {
            if (seen.find(curr->data) != seen.end()) {
                prev->next = curr->next;
                delete curr;
            } else {
                seen.insert(curr->data);
                prev = curr;
            }
            curr = prev->next;
        }
    }

    void removeDuplicatesWithoutBuffer() {
        Node* curr = head;

        while (curr) {
            Node* runner = curr;
            while (runner->next) {
                if (runner->next->data == curr->data) {
                    Node* temp = runner->next;
                    runner->next = runner->next->next;
                    delete temp;
                } else {
                    runner = runner->next;
                }
            }
            curr = curr->next;
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
    LinkedList list;
    list.append(3);
    list.append(4);
    list.append(3);
    list.append(2);
    list.append(4);
    list.append(1);

    cout << "Original List:" << endl;
    list.printList();

    list.removeDuplicatesWithBuffer();
    cout << "After removing duplicates with buffer:" << endl;
    list.printList();

    // Recreate the list for the next test
    list = LinkedList();
    list.append(3);
    list.append(4);
    list.append(3);
    list.append(2);
    list.append(4);
    list.append(1);

    list.removeDuplicatesWithoutBuffer();
    cout << "After removing duplicates without buffer:" << endl;
    list.printList();

    return 0;
}