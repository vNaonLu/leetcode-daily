#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/listnode.hpp>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 203.
 *      Remove Linked List Elements
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given the ‘head’ of a linked list and an integer ‘val’ , remove all
 *   the nodes of the linked list that has ‘Node.val = val’ , and return
 *   “the new head” .
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the list is in the range ‘[0, 10⁴]’ .
 *   • ‘1 ≤ Node.val ≤ 50’
 *   • ‘0 ≤ val ≤ 50’
 *
 */

struct q203 : public ::testing::Test {
  // Leetcode answer here
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

  class Solution *solution;
};

TEST_F(q203, sample_input01) {
  solution = new Solution();
  ListNode* head = ListNode::generate({1, 2, 6, 3, 4, 5, 6});
  int val = 6;
  ListNode* exp = ListNode::generate({1, 2, 3, 4, 5});
  EXPECT_LISTNODE_EQ(solution->removeElements(head, val), exp);
  delete solution;
}

TEST_F(q203, sample_input02) {
  solution = new Solution();
  ListNode* head = ListNode::generate({});
  int val = 1;
  ListNode* exp = ListNode::generate({});
  EXPECT_LISTNODE_EQ(solution->removeElements(head, val), exp);
  delete solution;
}

TEST_F(q203, sample_input03) {
  solution = new Solution();
  ListNode* head = ListNode::generate({7, 7, 7, 7});
  int val = 7;
  ListNode* exp = ListNode::generate({});
  EXPECT_LISTNODE_EQ(solution->removeElements(head, val), exp);
  delete solution;
}