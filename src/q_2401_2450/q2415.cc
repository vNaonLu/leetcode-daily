// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Reverse Odd Levels of Binary Tree
//
// https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/
//
// Question ID: 2415
// Difficult  : Medium
// Solve Date : 2024/12/20 22:35

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2415. Reverse Odd Levels of Binary Tree|:
//
// Given the |root| of a perfect binary tree, reverse the node values at each
// odd level of the tree.
//
//  • For example, suppose the node values at level 3 are
//  |[2,1,3,4,7,11,29,18]|, then it should become |[18,29,11,7,4,3,1,2]|.
// Return the root of the reversed tree.
// A binary tree is perfect if all parent nodes have two children and all leaves
// are on the same level. The level of a node is the number of edges along the
// path between it and the root node.
//
//

LEETCODE_BEGIN_RESOLVING(2415, ReverseOddLevelsOfBinaryTree, Solution);

class Solution {
public:
  TreeNode *reverseOddLevels(TreeNode *root) {
    traverse(root->left, root->right, 0);
    return root;
  }

private:
  void traverse(auto *left, auto *right, int level) {
    if (!left || !right) {
      return;
    }

    if (level % 2 == 0) {
      swap(left->val, right->val);
    }

    traverse(left->left, right->right, level + 1);
    traverse(left->right, right->left, level + 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 2¹⁴]|.
// * |0 <= Node.val <= 10⁵|
// * |root| is a perfect binary tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [2,3,5,8,13,21,34]
// Output: [2,5,3,8,13,21,34]
//

LEETCODE_SOLUTION_UNITTEST(2415, ReverseOddLevelsOfBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 3, 5, 8, 13, 21, 34});
  TreeNode *expect   = TreeNode::FromVector({2, 5, 3, 8, 13, 21, 34});
  TreeNode *actual   = solution->reverseOddLevels(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [7,13,11]
// Output: [7,11,13]
//

LEETCODE_SOLUTION_UNITTEST(2415, ReverseOddLevelsOfBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({7, 13, 11});
  TreeNode *expect   = TreeNode::FromVector({7, 11, 13});
  TreeNode *actual   = solution->reverseOddLevels(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #3]
//  Input: root = [0,1,2,0,0,0,0,1,1,1,1,2,2,2,2]
// Output: [0,2,1,0,0,0,0,2,2,2,2,1,1,1,1]
//

LEETCODE_SOLUTION_UNITTEST(2415, ReverseOddLevelsOfBinaryTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({0, 1, 2, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2});
  TreeNode *expect =
      TreeNode::FromVector({0, 2, 1, 0, 0, 0, 0, 2, 2, 2, 2, 1, 1, 1, 1});
  TreeNode *actual = solution->reverseOddLevels(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}
