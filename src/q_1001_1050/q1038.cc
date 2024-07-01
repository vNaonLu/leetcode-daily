// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Binary Search Tree to Greater Sum Tree
//
// https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/
//
// Question ID: 1038
// Difficult  : Medium
// Solve Date : 2024/06/25 21:15

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1038. Binary Search Tree to Greater Sum Tree|:
//
// Given the |root| of a Binary Search Tree (BST), convert it to a Greater Tree
// such that every key of the original BST is changed to the original key plus
// the sum of all keys greater than the original key in BST. As a reminder, a
// binary search tree is a tree that satisfies these constraints:
//
//  • The left subtree of a node contains only nodes with keys less than the
//  node's key.
//
//  • The right subtree of a node contains only nodes with keys greater than the
//  node's key.
//
//  • Both the left and right subtrees must also be binary search trees.
//
//

LEETCODE_BEGIN_RESOLVING(1038, BinarySearchTreeToGreaterSumTree, Solution);

class Solution {
public:
  TreeNode *bstToGst(TreeNode *root) {
    int                sum = 0;
    vector<TreeNode *> stack;
    TreeNode          *node = root;
    while (node || !stack.empty()) {
      while (node) {
        stack.emplace_back(node);
        node = node->right;
      }

      node = stack.back();
      stack.pop_back();
      sum += node->val;
      node->val = sum;
      node      = node->left;
    }
    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 100]|.
// * |0 <= Node.val <= 100|
// * All the values in the tree are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
// Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
//

LEETCODE_SOLUTION_UNITTEST(1038, BinarySearchTreeToGreaterSumTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector(
      {4, 1, 6, 0, 2, 5, 7, null, null, null, 3, null, null, null, 8});
  TreeNode *expect = TreeNode::FromVector(
      {30, 36, 21, 36, 35, 26, 15, null, null, null, 33, null, null, null, 8});
  TreeNode *actual = solution->bstToGst(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [0,null,1]
// Output: [1,null,1]
//

LEETCODE_SOLUTION_UNITTEST(1038, BinarySearchTreeToGreaterSumTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0, null, 1});
  TreeNode *expect   = TreeNode::FromVector({1, null, 1});
  TreeNode *actual   = solution->bstToGst(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}
