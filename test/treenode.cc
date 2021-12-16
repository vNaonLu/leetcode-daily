#include <gtest/gtest.h>
#include <leetcode/treenode.hpp>

TEST(treenode, release) {
  TreeNode *p0 = new TreeNode(10);
  TreeNode *q0 = new TreeNode(10);
  EXPECT_EQ(2, TreeNode::release({p0, q0, p0, q0}));
  TreeNode *p3 = new TreeNode(3),
           *p2 = new TreeNode(2),
           *p1 = new TreeNode(1, p2, p3);
  TreeNode *q3 = new TreeNode(3),
           *q2 = new TreeNode(2),
           *q1 = new TreeNode(1, q2, q3);
  EXPECT_EQ(6, TreeNode::release({p1, q1, p2, q2}));
  TreeNode *p6 = new TreeNode(6),
           *p5 = new TreeNode(5, p6, nullptr),
           *p4 = new TreeNode(4, p5, nullptr);
  TreeNode *q6 = new TreeNode(6),
           *q5 = new TreeNode(5, q6, nullptr),
           *q4 = new TreeNode(4, q5, nullptr);
  EXPECT_EQ(6, TreeNode::release({p4, q4, p5, q5}));
  TreeNode *p9 = new TreeNode(9),
           *p8 = new TreeNode(8, nullptr, p9),
           *p7 = new TreeNode(7, nullptr, p8);
  TreeNode *q9 = new TreeNode(9),
           *q8 = new TreeNode(8, nullptr, q9),
           *q7 = new TreeNode(7, nullptr, q8);
  EXPECT_EQ(6, TreeNode::release({p7, q7, p8, q9}));
}

TEST(treenode, constructor) {
  TreeNode single;
  EXPECT_EQ(single.val,   0);
  EXPECT_EQ(single.left,  nullptr);
  EXPECT_EQ(single.right, nullptr);
  TreeNode value(10);
  EXPECT_EQ(value.val,   10);
  EXPECT_EQ(value.left,  nullptr);
  EXPECT_EQ(value.right, nullptr);
  TreeNode L, R, basic(10, &L, &R);
  EXPECT_EQ(basic.val,   10);
  EXPECT_EQ(basic.left,  &L);
  EXPECT_EQ(basic.right, &R);
}

TEST(treenode, equal) {
  TreeNode p0(10);
  TreeNode q0(10);
  EXPECT_TRUE(p0 == q0);
  TreeNode p3(3), p2(2), p1(1, &p2, &p3);
  TreeNode q3(3), q2(2), q1(1, &q2, &q3);
  EXPECT_TRUE(p1 == q1);
  TreeNode p6(6), p5(5, &p6, nullptr), p4(4, &p5, nullptr);
  TreeNode q6(6), q5(5, &q6, nullptr), q4(4, &q5, nullptr);
  EXPECT_TRUE(p4 == q4);
  TreeNode p9(6), p8(5, nullptr, &p9), p7(4, nullptr, &p8);
  TreeNode q9(6), q8(5, nullptr, &q9), q7(4, nullptr, &q8);
  EXPECT_TRUE(p7 == q7);
}

TEST(treenode, unequal) {
  TreeNode p0(11);
  TreeNode q0(10);
  EXPECT_FALSE(p0 == q0);
  TreeNode p3(4), p2(2), p1(1, &p2, &p3);
  TreeNode q3(3), q2(2), q1(1, &q2, &q3);
  EXPECT_FALSE(p1 == q1);
  TreeNode p6(7), p5(5, &p6, nullptr), p4(4, &p5, nullptr);
  TreeNode q6(6), q5(5, &q6, nullptr), q4(4, &q5, nullptr);
  EXPECT_FALSE(p4 == q4);
  TreeNode p9(8), p8(5, nullptr, &p9), p7(4, nullptr, &p8);
  TreeNode q9(6), q8(5, nullptr, &q9), q7(4, nullptr, &q8);
  EXPECT_FALSE(p7 == q7);
}

TEST(treenode, equal_macro) {
  TreeNode *p0 = new TreeNode(10);
  TreeNode *q0 = new TreeNode(10);
  ASSERT_TRUE(*p0 == *q0);
  EXPECT_TREENODE_EQ(p0, q0);
  TreeNode *p3 = new TreeNode(3), 
           *p2 = new TreeNode(2),
           *p1 = new TreeNode(1, p2, p3);
  TreeNode *q3 = new TreeNode(3), 
           *q2 = new TreeNode(2),
           *q1 = new TreeNode(1, q2, q3);
  ASSERT_TRUE(*p1 == *q1);
  EXPECT_TREENODE_EQ(p1, q1);
  TreeNode *p6 = new TreeNode(6),
           *p5 = new TreeNode(5, p6, nullptr),
           *p4 = new TreeNode(4, p5, nullptr);
  TreeNode *q6 = new TreeNode(6),
           *q5 = new TreeNode(5, q6, nullptr),
           *q4 = new TreeNode(4, q5, nullptr);
  ASSERT_TRUE(*p4 == *q4);
  EXPECT_TREENODE_EQ(p4, q4);
  TreeNode *p9 = new TreeNode(9),
           *p8 = new TreeNode(8, nullptr, p9),
           *p7 = new TreeNode(7, nullptr, p8);
  TreeNode *q9 = new TreeNode(9),
           *q8 = new TreeNode(8, nullptr, q9),
           *q7 = new TreeNode(7, nullptr, q8);
  ASSERT_TRUE(*p7 == *q7);
  EXPECT_TREENODE_EQ(p7, q7);
}

TEST(treenode, build_tree_empty) {
  vector<TreeNode *> _treenodes = {};
  TreeNode *p = TreeNode::_build_tree(_treenodes);
  EXPECT_EQ(nullptr, p);
}

TEST(treenode, build_tree) {
  TreeNode *p0 = new TreeNode(10);
  vector<TreeNode *> _init_q0 = {new TreeNode(10)};
  TreeNode *q0 = TreeNode::_build_tree(_init_q0);
  ASSERT_TRUE(*p0 == *q0);
  EXPECT_TREENODE_EQ(p0, q0);
  TreeNode *p3 = new TreeNode(3),
           *p2 = new TreeNode(2),
           *p1 = new TreeNode(1, p2, p3);
  vector<TreeNode *> _init_q1 = {new TreeNode(1), new TreeNode(2), new TreeNode(3)};
  TreeNode *q1 = TreeNode::_build_tree(_init_q1);
  ASSERT_TRUE(*p1 == *q1);
  EXPECT_TREENODE_EQ(p1, q1);
  TreeNode *p6 = new TreeNode(6),
           *p5 = new TreeNode(5, p6, nullptr),
           *p4 = new TreeNode(4, p5, nullptr);
  vector<TreeNode *> _init_q4 = {new TreeNode(4), new TreeNode(5), nullptr, new TreeNode(6)};
  TreeNode *q4 = TreeNode::_build_tree(_init_q4);
  ASSERT_TRUE(*p4 == *q4);
  EXPECT_TREENODE_EQ(p4, q4);
  TreeNode *p9 = new TreeNode(9),
           *p8 = new TreeNode(8, nullptr, p9),
           *p7 = new TreeNode(7, nullptr, p8);
  vector<TreeNode *> _init_q7 = {new TreeNode(7), nullptr, new TreeNode(8), nullptr, new TreeNode(9)};
  TreeNode *q7 = TreeNode::_build_tree(_init_q7);
  ASSERT_TRUE(*p7 == *q7);
  EXPECT_TREENODE_EQ(p7, q7);
}

TEST(treenode, generate_empty) {
  TreeNode *p = TreeNode::generate({});
  EXPECT_EQ(nullptr, p);
  TreeNode *q = TreeNode::generate({NULL_TREENODE});
  EXPECT_EQ(nullptr, q);
}

TEST(treenode, generate) {
  TreeNode *p0 = new TreeNode(10);
  TreeNode *q0 = TreeNode::generate({10});
  ASSERT_TRUE(*p0 == *q0);
  EXPECT_TREENODE_EQ(p0, q0);
  TreeNode *p3 = new TreeNode(3),
           *p2 = new TreeNode(2),
           *p1 = new TreeNode(1, p2, p3);
  TreeNode *q1 = TreeNode::generate({1, 2, 3});
  ASSERT_TRUE(*p1 == *q1);
  EXPECT_TREENODE_EQ(p1, q1);
  TreeNode *p6 = new TreeNode(6),
           *p5 = new TreeNode(5, p6, nullptr),
           *p4 = new TreeNode(4, p5, nullptr);
  TreeNode *q4 = TreeNode::generate({4, 5, NULL_TREENODE, 6});
  ASSERT_TRUE(*p4 == *q4);
  EXPECT_TREENODE_EQ(p4, q4);
  TreeNode *p9 = new TreeNode(9),
           *p8 = new TreeNode(8, nullptr, p9),
           *p7 = new TreeNode(7, nullptr, p8);
  TreeNode *q7 = TreeNode::generate({7, NULL_TREENODE, 8, NULL_TREENODE, 9});
  ASSERT_TRUE(*p7 == *q7);
  EXPECT_TREENODE_EQ(p7, q7);
}