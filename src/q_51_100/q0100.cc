// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Same Tree
//
// https://leetcode.com/problems/same-tree/
//
// Question ID: 100
// Difficult  : Easy
// Solve Date : 2022/09/22 13:14

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |100. Same Tree|:
//
// Given the roots of two binary trees |p| and |q|, write a function to check if
// they are the same or not. Two binary trees are considered the same if they
// are structurally identical, and the nodes have the same value.
//

LEETCODE_BEGIN_RESOLVING(100, SameTree, Solution);

class Solution {
public:
  bool isSameTree(TreeNode *p, TreeNode *q) {
    if (nullptr != p && nullptr != q) {
      return p->val == q->val && isSameTree(p->left, q->left) &&
             isSameTree(p->right, q->right);
    } else {
      return nullptr == p && nullptr == q;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in both trees is in the range |[0, 100]|.
// * |-10⁴ <= Node.val <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: p = [1,2,3], q = [1,2,3]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(100, SameTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *p        = TreeNode::FromVector({1, 2, 3});
  TreeNode *q        = TreeNode::FromVector({1, 2, 3});
  bool      expect   = true;
  bool      actual   = solution->isSameTree(p, q);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(p, q);
}

// [Example #2]
//  Input: p = [1,2], q = [1,null,2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(100, SameTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *p        = TreeNode::FromVector({1, 2});
  TreeNode *q        = TreeNode::FromVector({1, null, 2});
  bool      expect   = false;
  bool      actual   = solution->isSameTree(p, q);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(p, q);
}

// [Example #3]
//  Input: p = [1,2,1], q = [1,1,2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(100, SameTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *p        = TreeNode::FromVector({1, 2, 1});
  TreeNode *q        = TreeNode::FromVector({1, 1, 2});
  bool      expect   = false;
  bool      actual   = solution->isSameTree(p, q);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(p, q);
}
