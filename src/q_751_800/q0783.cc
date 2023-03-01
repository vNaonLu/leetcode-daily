// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Distance Between BST Nodes
//
// https://leetcode.com/problems/minimum-distance-between-bst-nodes/
//
// Question ID: 783
// Difficult  : Easy
// Solve Date : 2022/10/08 14:05

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |783. Minimum Distance Between BST Nodes|:
//
// Given the |root| of a Binary Search Tree (BST), return the minimum difference
// between the values of any two different nodes in the tree.
//

LEETCODE_BEGIN_RESOLVING(783, MinimumDistanceBetweenBSTNodes, Solution);

class Solution {
private:
  void solve(TreeNode *p, int &prev, int &res) {
    if (nullptr != p) {
      solve(p->left, prev, res);
      if (prev != -1) {
        res = min(res, p->val - prev);
      }
      prev = p->val;
      solve(p->right, prev, res);
    }
  }

public:
  int minDiffInBST(TreeNode *root) {
    auto res  = numeric_limits<int>::max();
    auto prev = -1;
    solve(root, prev, res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[2, 100]|.
// * |0 <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [4,2,6,1,3]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(783, MinimumDistanceBetweenBSTNodes, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 2, 6, 1, 3});
  int       expect   = 1;
  int       actual   = solution->minDiffInBST(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,0,48,null,null,12,49]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(783, MinimumDistanceBetweenBSTNodes, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 0, 48, null, null, 12, 49});
  int       expect   = 1;
  int       actual   = solution->minDiffInBST(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
