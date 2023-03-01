// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Add One Row to Tree
//
// https://leetcode.com/problems/add-one-row-to-tree/
//
// Question ID: 623
// Difficult  : Medium
// Solve Date : 2022/05/26 18:26

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |623. Add One Row to Tree|:
//
// Given the |root| of a binary tree and two integers |val| and |depth|, add a
// row of nodes with value |val| at the given depth |depth|. Note that the
// |root| node is at depth |1|. The adding rule is:
//
//  • Given the integer |depth|, for each not null tree node |cur| at the depth
//  |depth - 1|, create two tree nodes with value |val| as |cur|'s left subtree
//  root and right subtree root.
//
//  • |cur|'s original left subtree should be the left subtree of the new left
//  subtree root.
//
//  • |cur|'s original right subtree should be the right subtree of the new
//  right subtree root.
//
//  • If |depth == 1| that means there is no depth |depth - 1| at all, then
//  create a tree node with value |val| as the new root of the whole original
//  tree, and the original tree is the new root's left subtree.
//

LEETCODE_BEGIN_RESOLVING(623, AddOneRowToTree, Solution);

class Solution {
public:
  TreeNode *addOneRow(TreeNode *root, int val, int depth) {
    if (depth == 1) {
      return new TreeNode(val, root, nullptr);
    }

    if (root == nullptr) {
      return nullptr;
    } else if (depth == 2) {
      auto p      = new TreeNode(val, root->left, nullptr),
           q      = new TreeNode(val, nullptr, root->right);
      root->left  = p;
      root->right = q;

      return root;
    } else {
      addOneRow(root->left, val, depth - 1);
      addOneRow(root->right, val, depth - 1);

      return root;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * The depth of the tree is in the range |[1, 10⁴]|.
// * |-100 <= Node.val <= 100|
// * |-10⁵ <= val <= 10⁵|
// * |1 <= depth <= the depth of tree + 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [4,2,6,3,1,5], val = 1, depth = 2
// Output: [4,1,1,2,null,null,6,3,1,5]
//

LEETCODE_SOLUTION_UNITTEST(623, AddOneRowToTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 2, 6, 3, 1, 5});
  int       val      = 1;
  int       depth    = 2;
  TreeNode *expect = TreeNode::FromVector({4, 1, 1, 2, null, null, 6, 3, 1, 5});
  TreeNode *actual = solution->addOneRow(root, val, depth);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [4,2,null,3,1], val = 1, depth = 3
// Output: [4,2,null,1,1,3,null,null,1]
//

LEETCODE_SOLUTION_UNITTEST(623, AddOneRowToTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 2, null, 3, 1});
  int       val      = 1;
  int       depth    = 3;
  TreeNode *expect = TreeNode::FromVector({4, 2, null, 1, 1, 3, null, null, 1});
  TreeNode *actual = solution->addOneRow(root, val, depth);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}
