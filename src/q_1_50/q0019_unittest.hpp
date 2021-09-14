
#ifndef Q19_UNITTEST_H__
#define Q19_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0019.hpp"
using namespace std;

/**
  * this file is generated by gquestion.py

  *
  * 19. Remove Nth Node From End of List
  *
  * Given the head of a linked list, remove the
  * n^(th) node from the end of the list and return its
  * head.
  *
  * Constraints:
  * - The number of nodes in the list is sz .
  * -  1 <= sz <= 30 
  * -  0 <= Node.val <= 100 
  * -  1 <= n <= sz 
  *  “Follow up:“ Could you do this in one pass?
  *
*/

#include <vector>

TEST(q19, sample_input01) {
  auto head = ListNode::generate({1, 2, 3, 4, 5});
  int n = 2;
  auto exp = ListNode::generate({1, 2, 3, 5});
  l19::Solution solver;
  EXPECT_TRUE(ListNode::equal(solver.removeNthFromEnd(head, n), exp));
  ListNode::release(head);
  ListNode::release(exp);
}

TEST(q19, sample_input02) {
  auto head = ListNode::generate({1});
  int n = 1;
  auto exp = ListNode::generate({});
  l19::Solution solver;
  EXPECT_TRUE(ListNode::equal(solver.removeNthFromEnd(head, n), exp));
  ListNode::release(head);
  ListNode::release(exp);
}

TEST(q19, sample_input03) {
  auto head = ListNode::generate({1, 2});
  int n = 1;
  auto exp = ListNode::generate({1});
  l19::Solution solver;
  EXPECT_TRUE(ListNode::equal(solver.removeNthFromEnd(head, n), exp));
  ListNode::release(head);
  ListNode::release(exp);
}

#endif