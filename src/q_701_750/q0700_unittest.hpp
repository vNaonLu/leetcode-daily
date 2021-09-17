
#ifndef Q700_UNITTEST_H__
#define Q700_UNITTEST_H__
#include <gtest/gtest.h>

#include "q0700.hpp"
using namespace std;

/**
  * this file is generated by gquestion.py
  *
  * 700. Search in a Binary Search Tree
  *
  * You are given the root of a binary search tree
  * (BST) and an integer val .
  * Find the node in the BST that the node';s value
  * equals val and return the subtree rooted with that
  * node. If such a node does not exist, return null .
  *
  * Constraints:
  * - The number of nodes in the tree is in the range [1, 5000] .
  * -  1 <= Node.val <= 10^(7) 
  * -  root is a binary search tree.
  * -  1 <= val <= 10^(7) 
  *
*/

TEST(q700, sample_input01) {
  int null = -1;
  TreeNode *root = TreeNode::generate({4, 2, 7, 1, 3}, null);
  int val = 2;
  TreeNode *exp = TreeNode::generate({2, 1, 3}, null);
  l700::Solution solver;
  EXPECT_TRUE(TreeNode::equal(solver.searchBST(root, val), exp));
  TreeNode::release(root);
  TreeNode::release(exp);
}

TEST(q700, sample_input02) {
  int null = -1;
  TreeNode *root = TreeNode::generate({4, 2, 7, 1, 3}, null);
  int val = 5;
  TreeNode *exp = TreeNode::generate({}, null);
  l700::Solution solver;
  EXPECT_TRUE(TreeNode::equal(solver.searchBST(root, val), exp));
  TreeNode::release(root);
  TreeNode::release(exp);
}

#endif