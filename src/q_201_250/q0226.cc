// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Invert Binary Tree
//
// https://leetcode.com/problems/invert-binary-tree/
//
// Question ID: 226
// Difficult  : Easy
// Solve Date : 2021/09/16 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |226. Invert Binary Tree|:
//
// Given the |root| of a binary tree, invert the tree, and return its root.
//  
//

LEETCODE_BEGIN_RESOLVING(226, InvertBinaryTree, Solution);

class Solution {
public:
  TreeNode *invertTree(TreeNode *root) {
    if (root == nullptr)
      return root;
    TreeNode *tmp = invertTree(root->left);
    root->left    = invertTree(root->right);
    root->right   = tmp;
    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 100]|.
// * |-100 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [4,2,7,1,3,6,9]
// Output: [4,7,2,9,6,3,1]
//

LEETCODE_SOLUTION_UNITTEST(226, InvertBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 2, 7, 1, 3, 6, 9});
  TreeNode *expect   = TreeNode::FromVector({4, 7, 2, 9, 6, 3, 1});
  TreeNode *actual   = solution->invertTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}

// [Example #2]
//  Input: root = [2,1,3]
// Output: [2,3,1]
//

LEETCODE_SOLUTION_UNITTEST(226, InvertBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 1, 3});
  TreeNode *expect   = TreeNode::FromVector({2, 3, 1});
  TreeNode *actual   = solution->invertTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}

// [Example #3]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(226, InvertBinaryTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({});
  TreeNode *expect   = TreeNode::FromVector({});
  TreeNode *actual   = solution->invertTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}
