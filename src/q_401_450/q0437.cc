// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Path Sum III
//
// https://leetcode.com/problems/path-sum-iii/
//
// Question ID: 437
// Difficult  : Medium
// Solve Date : 2021/10/17 14:07

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |437. Path Sum III|:
//
// Given the |root| of a binary tree and an integer |targetSum|, return the
// number of paths where the sum of the values along the path equals 
// |targetSum|. The path does not need to start or end at the root or a leaf,
// but it must go downwards (i.e., traveling only from parent nodes to child
// nodes).  
//

LEETCODE_BEGIN_RESOLVING(437, PathSumIII, Solution);

class Solution {
private:
  int helper(const TreeNode *const p, int target, int sum = 0) {
    if (p == nullptr)
      return 0;
    sum += p->val;
    return helper(p->left, target, sum) + helper(p->right, target, sum) +
           (sum == target ? 1 : 0);
  }

public:
  int pathSum(TreeNode *root, int targetSum) {
    if (root == nullptr)
      return 0;
    return helper(root, targetSum) + pathSum(root->left, targetSum) +
           pathSum(root->right, targetSum);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 1000]|.
// * |-10⁹ <= Node.val <= 10⁹|
// * |-1000 <= targetSum <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
// Output: 3
//
// The paths that sum to 8 are shown.

LEETCODE_SOLUTION_UNITTEST(437, PathSumIII, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({10, 5, -3, 3, 2, null, 11, 3, -2, null, 1});
  int targetSum = 8;
  int expect    = 3;
  int actual    = solution->pathSum(root, targetSum);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(437, PathSumIII, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1});
  int targetSum = 22;
  int expect    = 3;
  int actual    = solution->pathSum(root, targetSum);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
