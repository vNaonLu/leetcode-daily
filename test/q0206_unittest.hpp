
#ifndef Q206_UNITTEST_H__
#define Q206_UNITTEST_H__

#include <gtest/gtest.h>

#include <vector>

#include "../src/q0206.hpp"

using namespace std;
using l206::Solution;

TEST(q206, sample_input01) {
  vector<int> i{1, 2, 3, 4, 5};
  vector<int> e{5, 4, 3, 2, 1};
  Solution solver;

  auto out = solver.reverseList(ListNode::generate(i));
  auto exp = ListNode::generate(e);
  EXPECT_TRUE(ListNode::compare(exp, out));
  ListNode::release(out);
  ListNode::release(exp);
}

TEST(q206, sample_input02) {
  vector<int> i{1, 2};
  vector<int> e{2, 1};
  Solution solver;

  auto out = solver.reverseList(ListNode::generate(i));
  auto exp = ListNode::generate(e);
  EXPECT_TRUE(ListNode::compare(exp, out));
  ListNode::release(out);
  ListNode::release(exp);
}

TEST(q206, sample_input03) {
  vector<int> i{};
  vector<int> e{};
  Solution solver;

  auto out = solver.reverseList(ListNode::generate(i));
  auto exp = ListNode::generate(e);
  EXPECT_TRUE(ListNode::compare(exp, out));
  ListNode::release(out);
  ListNode::release(exp);
}

#endif