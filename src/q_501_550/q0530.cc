// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Absolute Difference in BST
//
// https://leetcode.com/problems/minimum-absolute-difference-in-bst/
//
// Question ID: 530
// Difficult  : Easy
// Solve Date : 2022/11/25 10:52

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |530. Minimum Absolute Difference in BST|:
//
// Given the |root| of a Binary Search Tree (BST), return the minimum absolute
// difference between the values of any two different nodes in the tree.
//

LEETCODE_BEGIN_RESOLVING(530, MinimumAbsoluteDifferenceInBST, Solution);

class Solution {
private:
  TreeNode *prev = nullptr;

  void solve(TreeNode *p, int &res) {
    if (nullptr != p->left) {
      solve(p->left, res);
    }

    if (nullptr != prev) {
      res = min(res, abs(prev->val - p->val));
    }
    prev = p;

    if (nullptr != p->right) {
      solve(p->right, res);
    }
  }

public:
  int getMinimumDifference(TreeNode *root) {
    auto res = numeric_limits<int>::max();
    prev     = nullptr;
    solve(root, res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[2, 10⁴]|.
// * |0 <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [4,2,6,1,3]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(530, MinimumAbsoluteDifferenceInBST, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 2, 6, 1, 3});
  int       expect   = 1;
  int       actual   = solution->getMinimumDifference(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,0,48,null,null,12,49]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(530, MinimumAbsoluteDifferenceInBST, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 0, 48, null, null, 12, 49});
  int       expect   = 1;
  int       actual   = solution->getMinimumDifference(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
