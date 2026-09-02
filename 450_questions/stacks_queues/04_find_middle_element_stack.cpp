/*
    QUESTION    : Design a stack with operations on middle element (getMiddle, deleteMiddle in O(1))
    Company Tags: Amazon, Microsoft
    GfG Link    : https://www.geeksforgeeks.org/design-a-stack-with-find-middle-operation/
*/

#include <iostream>

using namespace std;

// Doubly Linked List Node
struct DLLNode {
    int data;
    DLLNode* prev;
    DLLNode* next;
    DLLNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

/************************************************************ C++ ************************************************************/
// T.C : Push: O(1), Pop: O(1), findMiddle: O(1), deleteMiddle: O(1)
// S.C : O(N) - Doubly Linked List storing stack elements
class SpecialStackDLL {
private:
    DLLNode* head = nullptr;
    DLLNode* mid = nullptr;
    int count = 0;

public:
    void push(int x) {
        DLLNode* newNode = new DLLNode(x);
        newNode->prev = nullptr;
        newNode->next = head;

        if (head != nullptr) {
            head->prev = newNode;
        }

        head = newNode;
        count++;

        // Update mid pointer
        if (count == 1) {
            mid = newNode;
        } else if (count % 2 != 0) {
            mid = mid->prev;
        }
    }

    int pop() {
        if (count == 0) return -1;

        DLLNode* nodeToPop = head;
        int val = nodeToPop->data;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        }

        count--;

        // Update mid pointer
        if (count % 2 == 0) {
            mid = mid->next;
        }

        delete nodeToPop;
        return val;
    }

    int findMiddle() {
        if (count == 0) return -1;
        return mid->data;
    }

    void deleteMiddle() {
        if (count == 0) return;

        DLLNode* nodeToDelete = mid;

        if (mid->prev != nullptr) {
            mid->prev->next = mid->next;
        }
        if (mid->next != nullptr) {
            mid->next->prev = mid->prev;
        }

        if (mid == head) {
            head = mid->next;
        }

        count--;

        if (count % 2 != 0) {
            mid = nodeToDelete->prev;
        } else {
            mid = nodeToDelete->next;
        }

        delete nodeToDelete;
    }
};

/*
 * ============================================================================
 * 1-MINUTE QUICK REVISION
 * ============================================================================
 * - Use a Doubly Linked List with `head`, `mid`, and `count`.
 * - On `push`: if `count % 2 != 0`, `mid = mid->prev`.
 * - On `pop`: if `count % 2 == 0`, `mid = mid->next`.
 * - Enables $O(1)$ push, pop, findMiddle, and deleteMiddle!
 */
