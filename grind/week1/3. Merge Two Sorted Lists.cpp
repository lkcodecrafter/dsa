#include<iostream>
using namespace std;

/*

Input: list1 = [1,2,4], 
	   list2 = [1,3,4]
Output: [1,1,2,3,4,4]

*/

struct ListNode {
 int val;
 ListNode *next;
 ListNode() : val(0), next(nullptr) {}
 ListNode(int x) : val(x), next(nullptr) {}
 ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include <iostream>
using namespace std;

/*

Input: list1 = [1,2,4],
       list2 = [1,3,4]
Output: [1,1,2,3,4,4]

*/

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

        ListNode* dummy = new ListNode();
        ListNode* temp = dummy;

        while (list1 && list2) {

            if (list1->val < list2->val) {

                temp->next = list1;
                list1 = list1->next;
            }

            else {

                temp->next = list2;
                list2 = list2->next;
            }

            temp = temp->next;
        }
        if (list1) {
            temp->next = list1;
        }

        if (list2) {
            temp->next = list2;
        }

        return dummy->next;
    }
};