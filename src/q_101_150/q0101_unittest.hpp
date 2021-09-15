
#ifndef Q101_UNITTEST_H__
#define Q101_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0101.hpp"
using namespace std;

/**
  * this file is generated by gquestion.py
  *
  * 101. Symmetric Tree
  *
  * Given the root of a binary tree, check whether it
  * is a mirror of itself (i.e., symmetric around its
  * center).
  *
  * Constraints:
  * - The number of nodes in the tree is in the range [1, 1000] .
  * -  -100 <= Node.val <= 100 
  *  “Follow up:“ Could you solve it both recursively and iteratively?
  *
*/

TEST(q101, sample_input01) {
  int null = -1;
  TreeNode *root = TreeNode::generate({1, 2, 2, 3, 4, 4, 3}, null);
  bool exp = true;
  l101::Solution solver;
  EXPECT_EQ(solver.isSymmetric(root), exp);
  TreeNode::release(root);
}

TEST(q101, sample_input02) {
  int null = -1;
  TreeNode *root = TreeNode::generate({1, 2, 2, null, 3, null, 3}, null);
  bool exp = false;
  l101::Solution solver;
  EXPECT_EQ(solver.isSymmetric(root), exp);
  TreeNode::release(root);
}

#endif