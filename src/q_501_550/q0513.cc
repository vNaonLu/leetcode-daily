// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Bottom Left Tree Value
//
// https://leetcode.com/problems/find-bottom-left-tree-value/
//
// Question ID: 513
// Difficult  : Medium
// Solve Date : 2022/10/09 13:12

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |513. Find Bottom Left Tree Value|:
//
// Given the |root| of a binary tree, return the leftmost value in the last row
// of the tree.
//

LEETCODE_BEGIN_RESOLVING(513, FindBottomLeftTreeValue, Solution);

class Solution {
private:
  void solve(TreeNode *p, int *tgt, int *tgt_lvl, int lvl) {
    if (nullptr != p) {
      if (lvl > *tgt_lvl) {
        *tgt_lvl = lvl;
        *tgt     = p->val;
      }

      solve(p->left, tgt, tgt_lvl, lvl + 1);
      solve(p->right, tgt, tgt_lvl, lvl + 1);
    }
  }

public:
  int findBottomLeftValue(TreeNode *root) {
    auto res = (int)0;
    auto lvl = (int)-1;
    solve(root, &res, &lvl, 0);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |-2³¹ <= Node.val <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [2,1,3]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(513, FindBottomLeftTreeValue, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 1, 3});
  int       expect   = 1;
  int       actual   = solution->findBottomLeftValue(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3,4,null,5,6,null,null,7]
// Output: 7
//

LEETCODE_SOLUTION_UNITTEST(513, FindBottomLeftTreeValue, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({1, 2, 3, 4, null, 5, 6, null, null, 7});
  int expect = 7;
  int actual = solution->findBottomLeftValue(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
