#include <gtest/gtest.h>
#include <iostream>
#include <leetcode/treenode.hpp>

using namespace std;

/**
 * This file is generated by leetcode_add.py v1.0
 *
 * 101.
 *      Symmetric Tree
 *
 * ––––––––––––––––––––––––––––– Description –––––––––––––––––––––––––––––
 *
 *   Given the ‘root’ of a binary tree, “check whether it is a mirror of
 *   itself” (i.e., symmetric around its center).
 *
 * ––––––––––––––––––––––––––––– Constraints –––––––––––––––––––––––––––––
 *
 *   • The number of nodes in the tree is in the range ‘[1, 1000]’ .
 *   • ‘-100 ≤ Node.val ≤ 100’
 *
 */

struct q101 : public ::testing::Test {
  // Leetcode answer here
  class Solution {
  private:
    bool solve(TreeNode *p, TreeNode *q) {
      if (nullptr != p && nullptr != q) {
        return p->val == q->val && solve(p->left, q->right) &&
               solve(p->right, q->left);
      } else {
        return nullptr == p && nullptr == q;
      }
    }

  public:
    bool isSymmetric(TreeNode *root) {
      return nullptr == root || solve(root->left, root->right);
    }
  };

  class Solution *solution;
};

TEST_F(q101, sample_input01) {
  solution       = new Solution();
  TreeNode *root = TreeNode::generate({1, 2, 2, 3, 4, 4, 3});
  bool      exp  = true;
  EXPECT_EQ(solution->isSymmetric(root), exp);
  delete solution;
}

TEST_F(q101, sample_input02) {
  solution = new Solution();
  TreeNode *root =
      TreeNode::generate({1, 2, 2, NULL_TREENODE, 3, NULL_TREENODE, 3});
  bool exp = false;
  EXPECT_EQ(solution->isSymmetric(root), exp);
  delete solution;
}