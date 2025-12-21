#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

class Solution{
    public:

    int findTheLenghtOfLoop(Node * head){
        Node* slow = head;
        Node* fast = head;

        while(fast != NULL && fast->next != NULL){
            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast){
                //loop detected
                int count =1;
                Node* temp = slow;
                while(temp->next != slow){
                    count++;
                    temp = temp->next;
                }
                return count;
            }
        }
        return 0; //no loop   

    }
};
int main(){

    //1->2->3->4->2
        
    Node* head = new Node();
    head->data =1;

    Node* two = new Node();
    two->data=2;

    head->next = two;

    Node* three = new Node();
    three->data=3;

    two->next = three;

    
    Node* four = new Node();
    four->data=4;

    four->next = two;
    three->next = four;
    

    Solution sol;

    cout<<sol.findTheLenghtOfLoop(head);
    

}