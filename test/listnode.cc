#include <gtest/gtest.h>
#include <leetcode/listnode.hpp>

using namespace std;

TEST(listnode, release) {
  ListNode *p = new ListNode();
  ListNode *q = new ListNode(0);
  EXPECT_EQ(ListNode::release(p, q, p, q), 2);
  ListNode *p3 = new ListNode(3),
           *p2 = new ListNode(2, p3),
           *p1 = new ListNode(1, p2);
  EXPECT_EQ(ListNode::release(p1), 3);
}

TEST(listnode, constructor) {
  ListNode p1;
  EXPECT_EQ(p1.val, 0);
  EXPECT_EQ(p1.next, nullptr);
  ListNode p2(10);
  EXPECT_EQ(p2.val, 10);
  EXPECT_EQ(p2.next, nullptr);
  ListNode p3(20, &p1);
  EXPECT_EQ(p3.val, 20);
  EXPECT_EQ(p3.next, &p1);
}

TEST(listnode, equal) {
  ListNode p2(0), p1(0, &p2), p(0, &p1);
  ListNode q2(0), q1(0, &q2), q(0, &q1);
  EXPECT_TRUE(p == q);
}

TEST(listnode, equal_loop) {
  ListNode p2(0), p1(0, &p2), p(0, &p1);
  p2.next = &p;
  ListNode q2(0), q1(0, &q2), q(0, &q1);
  q2.next = &q;
  EXPECT_TRUE(p == q);
}

TEST(listnode, unequal) {
  ListNode p2(0), p1(1, &p2), p(0, &p1);
  ListNode q2(0), q1(0, &q2), q(0, &q1);
  EXPECT_FALSE(p == q);
}

TEST(listnode, unequal_loop) {
  ListNode p2(0), p1(1, &p2), p(0, &p1);
  p2.next = &p;
  ListNode q2(0), q1(0, &q2), q(0, &q1);
  q2.next = &q1;
  EXPECT_FALSE(p == q);
}

TEST(listnode, data) {
  ListNode p2(0), p1(0, &p2), p(0, &p1);
  vector<ListNode::_listnode_data> _expected;
  _expected.emplace_back(0, 0);
  _expected.emplace_back(0, 1);
  _expected.emplace_back(0, 2);
  EXPECT_TRUE(_expected == p._data());
}

TEST(listnode, data_loop) {
  ListNode p2(0), p1(0, &p2), p(0, &p1);
  p2.next = &p1;
  vector<ListNode::_listnode_data> _expected;
  _expected.emplace_back(0, 0);
  _expected.emplace_back(0, 1);
  _expected.emplace_back(0, 2);
  _expected.emplace_back(0, 1);
  EXPECT_TRUE(_expected == p._data());
}

TEST(listnode, equal_macro) {
  ListNode *p = new ListNode(0);
  p->next = new ListNode(0);
  p->next->next = new ListNode(0);
  EXPECT_TRUE(*p == *p);
  ListNode *q = new ListNode(0);
  q->next = new ListNode(0);
  q->next->next = new ListNode(0);
  EXPECT_TRUE(*q == *q);
  EXPECT_TRUE(*p == *q);
  EXPECT_LISTNODE_EQ(p, q);
  ListNode::release(p, q);
}

TEST(listnode, equal_macro_loop) {
  ListNode *p = new ListNode(0);
  p->next = new ListNode(0);
  p->next->next = new ListNode(0);
  p->next->next->next = p;
  EXPECT_TRUE(*p == *p);
  ListNode *q = new ListNode(0);
  q->next = new ListNode(0);
  q->next->next = new ListNode(0);
  q->next->next->next = q;
  EXPECT_TRUE(*q == *q);
  EXPECT_TRUE(*p == *q);
  EXPECT_LISTNODE_EQ(p, q);
  ListNode::release(p, q);
}

TEST(listnode, equal_macro_loop_not_equal) {
  ListNode *p = new ListNode(0);
  p->next = new ListNode(0);
  p->next->next = new ListNode(0);
  p->next->next->next = p;
  EXPECT_TRUE(*p == *p);
  ListNode *q = new ListNode(0);
  q->next = new ListNode(0);
  q->next->next = new ListNode(0);
  EXPECT_TRUE(*q == *q);
  EXPECT_TRUE(*p == *p);
  EXPECT_FALSE(*p == *q);
  ListNode::release(p, q);
}

TEST(listnode, build_list_empty) {
  vector<ListNode*> _listnodes = {};
  ListNode *p = ListNode::_build_list(_listnodes, -1);
  EXPECT_TRUE(nullptr == p);
}

TEST(listnode, build_list_normal) {
  vector<ListNode*> _listnodes;
  _listnodes.emplace_back(new ListNode(0));
  _listnodes.emplace_back(new ListNode(0));
  _listnodes.emplace_back(new ListNode(0));
  ListNode p2(0), p1(0, &p2), p(0, &p1);
  ListNode *_gen = ListNode::_build_list(_listnodes, -1);
  ASSERT_TRUE(_gen == _listnodes.front());
  EXPECT_TRUE(p == *_gen);
  ListNode::release(_gen);
}

TEST(listnode, build_list_loop) {
  vector<ListNode *> _listnodes;
  _listnodes.emplace_back(new ListNode(0));
  _listnodes.emplace_back(new ListNode(0));
  _listnodes.emplace_back(new ListNode(0));
  ListNode p2(0), p1(0, &p2), p(0, &p1);
  p2.next = &p;
  ListNode *_gen = ListNode::_build_list(_listnodes, 0);
  ASSERT_TRUE(_gen == _listnodes.front());
  EXPECT_TRUE(p == *_gen);
  ListNode::release(_gen);
}

ListNode *__dummy_problem(ListNode *_some_ptr) {
  ListNode dummy(0, _some_ptr);
  return dummy.next;
}

TEST(listnode, dummy_problem) {
  ListNode *p = new ListNode();
  ListNode _cmp;
  ListNode *q = __dummy_problem(p);
  EXPECT_TRUE(p == q);
  EXPECT_NO_THROW(EXPECT_EQ(*q, _cmp));
  EXPECT_NO_THROW(EXPECT_EQ(q->val, 0));
  ListNode::release(p);
}

TEST(listnode, generate) {
  ListNode p2(0), p1(0, &p2), p(0, &p1);
  ListNode *q = ListNode::generate({0, 0, 0});
  EXPECT_TRUE(p == *q);
  ListNode::release(q);
}

TEST(listnode, generate_loop) {
  ListNode p2(0), p1(0, &p2), p(0, &p1);
  p2.next = &p;
  ListNode *q = ListNode::generate({0, 0, 0}, 0);
  EXPECT_TRUE(p == *q);
  ListNode::release(q);
}