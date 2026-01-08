/*
 *Q2.4 Partition; Write code to partition a linked list around a value x, such that all nodes less than x come 
before all nodes greater than or equal tox. If x is contained within the list, the values of x only need 
to be after the elements less than x (see below). The partition element x can appear anywhere in the 
"right partition"; it does not need to appear between the left and right partitions. 
EXAMPLE 
input: 3 -> S -> 8 -> 5 -> 10 -> 2 -> 1 [partition = 5] 
Output: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8 
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

    Node*partition(int x) {
      
        Node* node = head;
        Node* tail = head;
        while (node !=nullptr)
        {
            Node* next = node->next;
            if(node->data>=x)
            {
                tail->next = node; // Logic to move node to end
                tail = node;
            }
            else
            {
                node->next = head; // Logic to move node to front
                head = node;
            }
            node = next;
        }
        tail->next = nullptr;
        return head;
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
 
    int partitionValue = 3;
    list.head = list.partition(partitionValue);
    cout << "Partitioned List around " << partitionValue << ":" << endl;
    list.printList();

    return 0;
}