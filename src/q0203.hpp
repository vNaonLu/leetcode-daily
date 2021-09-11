
#ifndef LEETCODE_Q203_H__
#define LEETCODE_Q203_H__
#include <iostream>

#include "leetcode_struct/list_node.hpp"

namespace l203 {
using namespace std;

/**
  * this file is generated by gquestion.py
  *
  * 203. Remove Linked List Elements
  *
  * Given the head of a linked list and an integer
  * val , remove all the nodes of the linked list that
  * has Node.val == val , and return the new head .
  *
  * Constraints:
  * - The number of nodes in the list is in the range [0, 10^(4)] .
  * -  1 <= Node.val <= 50 
  * -  0 <= val <= 50 
  *
*/
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
class Solution {
 public:
  ListNode* removeElements(ListNode* head, int val) {
    ListNode dummy(-1, head);
    ListNode *p = head, *pre = &dummy;

    while (p != nullptr) {
      if (p->val == val) {
        pre->next = p->next;
      } else {
        pre = p;
      }
      p = p->next;
    }

    return dummy.next;
  }
};
}  // namespace l203
#endif