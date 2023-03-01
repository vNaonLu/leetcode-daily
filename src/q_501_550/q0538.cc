// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Convert BST to Greater Tree
//
// https://leetcode.com/problems/convert-bst-to-greater-tree/
//
// Question ID: 538
// Difficult  : Medium
// Solve Date : 2022/04/16 10:46

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |538. Convert BST to Greater Tree|:
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

LEETCODE_BEGIN_RESOLVING(538, ConvertBSTToGreaterTree, Solution);

class Solution {
private:
  int helper(TreeNode *p, int curr) {
    if (nullptr == p) {

      return curr;
    } else {
      p->val += helper(p->right, curr);

      return helper(p->left, p->val);
    }
  }

public:
  TreeNode *convertBST(TreeNode *root) {
    helper(root, 0);

    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 10⁴]|.
// * |-10⁴ <= Node.val <= 10⁴|
// * All the values in the tree are unique.
// * |root| is guaranteed to be a valid binary search tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
// Output: [30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
//

LEETCODE_SOLUTION_UNITTEST(538, ConvertBSTToGreaterTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector(
      {4, 1, 6, 0, 2, 5, 7, null, null, null, 3, null, null, null, 8});
  TreeNode *expect = TreeNode::FromVector(
      {30, 36, 21, 36, 35, 26, 15, null, null, null, 33, null, null, null, 8});
  TreeNode *actual = solution->convertBST(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [0,null,1]
// Output: [1,null,1]
//

LEETCODE_SOLUTION_UNITTEST(538, ConvertBSTToGreaterTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0, null, 1});
  TreeNode *expect   = TreeNode::FromVector({1, null, 1});
  TreeNode *actual   = solution->convertBST(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}
