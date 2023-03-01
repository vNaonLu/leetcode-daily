// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Deepest Leaves Sum
//
// https://leetcode.com/problems/deepest-leaves-sum/
//
// Question ID: 1302
// Difficult  : Medium
// Solve Date : 2022/05/15 12:59

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1302. Deepest Leaves Sum|:
//
// Given the |root| of a binary tree, return the sum of values of its deepest
// leaves.
//

LEETCODE_BEGIN_RESOLVING(1302, DeepestLeavesSum, Solution);

class Solution {
private:
  void helper(vector<int> &sum, TreeNode *p, int level) {
    if (nullptr != p) {
      if (level >= sum.size()) {
        sum.resize(level + 1);
      }

      sum[level] += p->val;

      helper(sum, p->left, level + 1);
      helper(sum, p->right, level + 1);
    }
  }

public:
  int deepestLeavesSum(TreeNode *root) {
    vector<int> sums;
    helper(sums, root, 0);

    return sums.back();
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |1 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
// Output: 15
//

LEETCODE_SOLUTION_UNITTEST(1302, DeepestLeavesSum, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector(
      {1, 2, 3, 4, 5, null, 6, 7, null, null, null, null, 8});
  int expect = 15;
  int actual = solution->deepestLeavesSum(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
// Output: 19
//

LEETCODE_SOLUTION_UNITTEST(1302, DeepestLeavesSum, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector(
      {6, 7, 8, 2, 7, 1, 3, 9, null, 1, 4, null, null, null, 5});
  int expect = 19;
  int actual = solution->deepestLeavesSum(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
