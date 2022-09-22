#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/treenode.hpp>

using namespace std;

/**
 * This file is generated by leetcode_add.py
 *
 * 100.
 *      Same Tree
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given the roots of two binary trees ‘p’ and ‘q’ , write a function to
 *   check if they are the same or
 *   Two binary trees are considered the same if they are structurally
 *   identical, and the nodes have the same value.
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in both trees is in the range ‘[0, 100]’ .
 *   • ‘-10⁴ ≤ Node.val ≤ 10⁴’
 *
 */

struct q100 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
      if (nullptr != p && nullptr != q) {
        return p->val == q->val && isSameTree(p->left, q->left) &&
               isSameTree(p->right, q->right);
      } else {
        return nullptr == p && nullptr == q;
      }
    }
  };

  class Solution *solution;
};

TEST_F(q100, sample_input01) {
  solution      = new Solution();
  TreeNode *p   = TreeNode::generate({1, 2, 3});
  TreeNode *q   = TreeNode::generate({1, 2, 3});
  bool      exp = true;
  bool      act = solution->isSameTree(p, q);
  EXPECT_EQ(act, exp);
  TreeNode::release(p, q);
  delete solution;
}

TEST_F(q100, sample_input02) {
  solution      = new Solution();
  TreeNode *p   = TreeNode::generate({1, 2});
  TreeNode *q   = TreeNode::generate({1, NULL_TREENODE, 2});
  bool      exp = false;
  bool      act = solution->isSameTree(p, q);
  EXPECT_EQ(act, exp);
  TreeNode::release(p, q);
  delete solution;
}

TEST_F(q100, sample_input03) {
  solution      = new Solution();
  TreeNode *p   = TreeNode::generate({1, 2, 1});
  TreeNode *q   = TreeNode::generate({1, 1, 2});
  bool      exp = false;
  bool      act = solution->isSameTree(p, q);
  EXPECT_EQ(act, exp);
  TreeNode::release(p, q);
  delete solution;
}