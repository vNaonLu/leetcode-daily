
#ifndef LEETCODE_Q206_H__
#define LEETCODE_Q206_H__

#include <iostream>

namespace l206 {
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

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