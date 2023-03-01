// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Symmetric Tree
//
// https://leetcode.com/problems/symmetric-tree/
//
// Question ID: 101
// Difficult  : Easy
// Solve Date : 2021/09/15 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |101. Symmetric Tree|:
//
// Given the |root| of a binary tree, check whether it is a mirror of itself
// (i.e., symmetric around its center).  
//

LEETCODE_BEGIN_RESOLVING(101, SymmetricTree, Solution);

class Solution {
private:
  bool solve(TreeNode *p, TreeNode *q) {
    if (nullptr != p && nullptr != q) {
      return p->val == q->val && solve(p->left, q->right) &&
             solve(p->right, q->left);
    } else {
      return nullptr == p && nullptr == q;
    }
  }

public:
  bool isSymmetric(TreeNode *root) {
    return nullptr == root || solve(root->left, root->right);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 1000]|.
// * |-100 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,2,3,4,4,3]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(101, SymmetricTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 2, 3, 4, 4, 3});
  bool      expect   = true;
  bool      actual   = solution->isSymmetric(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,2,null,3,null,3]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(101, SymmetricTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 2, null, 3, null, 3});
  bool      expect   = false;
  bool      actual   = solution->isSymmetric(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
