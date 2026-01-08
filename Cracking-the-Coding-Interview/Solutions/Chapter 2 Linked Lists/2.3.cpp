 /*
 *Q2.3 Implement an algorithm to delete a node in the midddle of a single linked list,given only access to that node.
 *Example:
 *Input:the node 'c' from the linked list a->b->c->d->e Result:nothing is returned,but the new linked list lokks like a->b->d->e
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


    void deleteNode(Node* nodeToDelete) {
        if (nodeToDelete == nullptr || nodeToDelete->next == nullptr) {
            cerr << "Cannot delete the given node." << endl;
            return;
        }
        Node* nextNode = nodeToDelete->next;
        nodeToDelete->data = nextNode->data;
        nodeToDelete->next = nextNode->next;
        delete nextNode;
        // can you give some dry run for this code?
        // Dry Run Example:
        // Given linked list: 3 -> 4 -> 3 -> 2 -> 4 -> 1
        // Let's say we want to delete the first node with value 3 (the third node in the list).
        // 1. We have a pointer to the node with value 3 (nodeToDelete).
        // 2. We check if nodeToDelete is null or if it's the last node. In this case, it's neither.
        // 3. We create a pointer nextNode that points to the next node (which has value 2).
        // 4. We copy the data from nextNode (2) to nodeToDelete. Now, nodeToDelete's value is 2.
        // 5. We update nodeToDelete's next pointer to skip over nextNode, effectively removing it from the list.
        // 6. Finally, we delete nextNode to free up memory.
        // what is nextNode->next here?
        // In this context, nextNode->next refers to the node that comes after nextNode in the linked list.
        // So, if nextNode is the node with value 2, then nextNode->next would be the node with value 4.
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
 

    return 0;
}