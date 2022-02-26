#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/listnode.hpp>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 86.
 *     Partition List
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given the ‘head’ of a linked list and a value ‘x’ , partition it such
 *   that all nodes “less than” ‘x’ come before nodes “greater than or
 *   equal” to ‘x’
 *   You should “preserve” the original relative order of the nodes in each
 *   of the two partitions.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the list is in the range ‘[0, 200]’ .
 *   • ‘-100 ≤ Node.val ≤ 100’
 *   • ‘-200 ≤ x ≤ 200’
 *
 */

struct q86 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
   public:
    ListNode* partition(ListNode* head, int x) {
      ListNode less(0, nullptr),
               greater(0, nullptr),
               *lp = &less,
               *gp = &greater;
      while (nullptr != head) {
        if (head->val >= x) {
          gp->next = new ListNode(head->val);
          gp = gp->next;
        } else {
          lp->next = new ListNode(head->val);
          lp = lp->next;
        }
        head = head->next;
      }
      lp->next = greater.next;
      return less.next;
    }
  };

  class Solution *solution;
};

TEST_F(q86, sample_input01) {
  solution = new Solution();
  ListNode* head = ListNode::generate({1, 4, 3, 2, 5, 2});
  int x = 3;
  ListNode* exp = ListNode::generate({1, 2, 2, 4, 3, 5});
  ListNode* act = solution->partition(head, x);
  EXPECT_LISTNODE_EQ(act, exp);
  ListNode::release(head, exp, act);
  delete solution;
}

TEST_F(q86, sample_input02) {
  solution = new Solution();
  ListNode* head = ListNode::generate({2, 1});
  int x = 2;
  ListNode* exp = ListNode::generate({1, 2});
  ListNode* act = solution->partition(head, x);
  EXPECT_LISTNODE_EQ(act, exp);
  ListNode::release(head, exp, act);
  delete solution;
}