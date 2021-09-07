
#ifndef Q206_UNITTEST_H__
#define Q206_UNITTEST_H__

#include <gtest/gtest.h>

#include <vector>

#include "../src/q0206.hpp"

using namespace std;
using namespace l206;

inline ListNode *getListNode(const vector<int> &__i) {
  if (__i.size() == 0) return nullptr;
  ListNode *res = new ListNode(__i[0]);
  ListNode *p = res;
  for (int i = 1; i < __i.size(); ++i) {
    p->next = new ListNode(__i[i]);
    p = p->next;
  }
  return res;
}

void destroy(ListNode *__p) {
  if (!__p) return;
  destroy(__p->next);
  delete __p;
}

inline bool compare(ListNode *__exp, ListNode *__act) {
  ListNode *p = __exp, *q = __act;
  while (p && q) {
    if (p->val != q->val) return false;
    p = p->next;
    q = q->next;
  }
  return !p && !q;
}

TEST(q206, sample_input01) {
  vector<int> i{1, 2, 3, 4, 5};
  vector<int> e{5, 4, 3, 2, 1};
  Solution solver;

  auto out = solver.reverseList(getListNode(i));
  auto exp = getListNode(e);
  EXPECT_TRUE(compare(exp, out));
  destroy(out);
  destroy(exp);
}

TEST(q206, sample_input02) {
  vector<int> i{1, 2};
  vector<int> e{2, 1};
  Solution solver;

  auto out = solver.reverseList(getListNode(i));
  auto exp = getListNode(e);
  EXPECT_TRUE(compare(exp, out));
  destroy(out);
  destroy(exp);
}

TEST(q206, sample_input03) {
  vector<int> i{};
  vector<int> e{};
  Solution solver;

  auto out = solver.reverseList(getListNode(i));
  auto exp = getListNode(e);
  EXPECT_TRUE(compare(exp, out));
  destroy(out);
  destroy(exp);
}

#endif