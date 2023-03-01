// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Path Sum
//
// https://leetcode.com/problems/path-sum/
//
// Question ID: 112
// Difficult  : Easy
// Solve Date : 2021/09/16 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |112. Path Sum|:
//
// Given the |root| of a binary tree and an integer |targetSum|, return |true|
// if the tree has a root-to-leaf path such that adding up all the values along
// the path equals |targetSum|. A leaf is a node with no children.  
//

LEETCODE_BEGIN_RESOLVING(112, PathSum, Solution);

class Solution {
public:
  bool hasPathSum(TreeNode *root, int targetSum) {
    if (root == nullptr) {
      return false;
    } else {
      int next = targetSum - root->val;
      if (root->left == nullptr && root->right == nullptr) {
        return next == 0;
      } else if (root->left == nullptr) {
        return hasPathSum(root->right, next);
      } else if (root->right == nullptr) {
        return hasPathSum(root->left, next);
      } else {
        return hasPathSum(root->left, next) || hasPathSum(root->right, next);
      }
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 5000]|.
// * |-1000 <= Node.val <= 1000|
// * |-1000 <= targetSum <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
// Output: true
//
// The root-to-leaf path with the target sum is shown.

LEETCODE_SOLUTION_UNITTEST(112, PathSum, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector(
      {5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1});
  int  targetSum = 22;
  bool expect    = true;
  bool actual    = solution->hasPathSum(root, targetSum);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3], targetSum = 5
// Output: false
//
// There two root-to-leaf paths in the tree:
// (1 --> 2): The sum is 3.
// (1 --> 3): The sum is 4.
// There is no root-to-leaf path with sum = 5.

LEETCODE_SOLUTION_UNITTEST(112, PathSum, example_2) {
  auto      solution  = MakeSolution();
  TreeNode *root      = TreeNode::FromVector({1, 2, 3});
  int       targetSum = 5;
  bool      expect    = false;
  bool      actual    = solution->hasPathSum(root, targetSum);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [], targetSum = 0
// Output: false
//
// Since the tree is empty, there are no root-to-leaf paths.

LEETCODE_SOLUTION_UNITTEST(112, PathSum, example_3) {
  auto      solution  = MakeSolution();
  TreeNode *root      = TreeNode::FromVector({});
  int       targetSum = 0;
  bool      expect    = false;
  bool      actual    = solution->hasPathSum(root, targetSum);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
