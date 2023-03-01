// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Validate Binary Search Tree
//
// https://leetcode.com/problems/validate-binary-search-tree/
//
// Question ID: 98
// Difficult  : Medium
// Solve Date : 2021/09/18 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |98. Validate Binary Search Tree|:
//
// Given the |root| of a binary tree, determine if it is a valid binary search
// tree (BST). A valid BST is defined as follows:
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

LEETCODE_BEGIN_RESOLVING(98, ValidateBinarySearchTree, Solution);

class Solution {
private:
  bool isBST(TreeNode *p, long min, long max) {
    if (!p)
      return true;
    if (p->val <= min || p->val >= max)
      return false;
    return isBST(p->left, min, p->val) && isBST(p->right, p->val, max);
  }

public:
  bool isValidBST(TreeNode *root) {
    return isBST(root, numeric_limits<long>::min(),
                 numeric_limits<long>::max());
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |-2³¹ <= Node.val <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [2,1,3]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(98, ValidateBinarySearchTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 1, 3});
  bool      expect   = true;
  bool      actual   = solution->isValidBST(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [5,1,4,null,null,3,6]
// Output: false
//
// The root node's value is 5 but its right child's value is 4.

LEETCODE_SOLUTION_UNITTEST(98, ValidateBinarySearchTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 1, 4, null, null, 3, 6});
  bool      expect   = false;
  bool      actual   = solution->isValidBST(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
