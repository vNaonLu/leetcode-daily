
#ifndef LEETCODE_Q206_H__
#define LEETCODE_Q206_H__
#include <iostream>
#include <leetcode/list_node.hpp>

namespace l206 {
class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    ListNode *p = head, *prev = nullptr;
    while (p) {
      ListNode* q = p->next;
      p->next = prev;
      prev = p;
      p = q;
    }
    return prev;
  }
};
}  // namespace l206

#endif