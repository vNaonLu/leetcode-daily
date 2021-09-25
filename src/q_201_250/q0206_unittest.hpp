
#ifndef Q206_UNITTEST_H__
#define Q206_UNITTEST_H__

#include <gtest/gtest.h>

#include <vector>

#include "q0206.hpp"

using namespace std;

TEST(q206, sample_input01) {
  ListNode *head = ListNode::generate({1, 2, 3, 4, 5});
  ListNode *exp = ListNode::generate({5, 4, 3, 2, 1});
  l206::Solution solver;
  EXPECT_LISTNODE_EQ(solver.reverseList(head) ,exp);
}

TEST(q206, sample_input02) {
  ListNode *head = ListNode::generate({1, 2});
  ListNode *exp = ListNode::generate({2, 1});
  l206::Solution solver;
  EXPECT_LISTNODE_EQ(solver.reverseList(head), exp);
}

TEST(q206, sample_input03) {
  ListNode *head = ListNode::generate({});
  ListNode *exp = ListNode::generate({});
  l206::Solution solver;
  EXPECT_LISTNODE_EQ(solver.reverseList(head), exp);
}

#endif