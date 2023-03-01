// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Root Equals Sum of Children
//
// https://leetcode.com/problems/root-equals-sum-of-children/
//
// Question ID: 2236
// Difficult  : Easy
// Solve Date : 2022/10/13 13:19

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |2236. Root Equals Sum of Children|:
//
// You are given the |root| of a binary tree that consists of exactly |3| nodes:
// the root, its left child, and its right child. Return |true| if the value of
// the root is equal to the sum of the values of its two children, or |false|
// otherwise.
//

LEETCODE_BEGIN_RESOLVING(2236, RootEqualsSumOfChildren, Solution);

class Solution {
public:
  bool checkTree(TreeNode *root) {
    return root->val == root->left->val + root->right->val;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The tree consists only of the root, its left child, and its right child.
// * |-100 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [10,4,6]
// Output: true
//
// The values of the root, its left child, and its right child are 10, 4, and 6,
// respectively. 10 is equal to 4 + 6, so we return true.

LEETCODE_SOLUTION_UNITTEST(2236, RootEqualsSumOfChildren, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({10, 4, 6});
  bool      expect   = true;
  bool      actual   = solution->checkTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [5,3,1]
// Output: false
//
// The values of the root, its left child, and its right child are 5, 3, and 1,
// respectively. 5 is not equal to 3 + 1, so we return false.

LEETCODE_SOLUTION_UNITTEST(2236, RootEqualsSumOfChildren, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 3, 1});
  bool      expect   = false;
  bool      actual   = solution->checkTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
