// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Level Sum of a Binary Tree
//
// https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/
//
// Question ID: 1161
// Difficult  : Medium
// Solve Date : 2023/06/15 14:12

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <numeric>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1161. Maximum Level Sum of a Binary Tree|:
//
// Given the |root| of a binary tree, the level of its root is |1|, the level of
// its children is |2|, and so on. Return the smallest level |x| such that the
// sum of all the values of nodes at level |x| is maximal.
//
//

LEETCODE_BEGIN_RESOLVING(1161, MaximumLevelSumOfABinaryTree, Solution);

class Solution {
public:
  int maxLevelSum(TreeNode *root) {
    vector<int> sums;
    solve(root, sums, 0);
    return distance(sums.begin(), max_element(sums.begin(), sums.end())) + 1;
  }

private:
  void solve(TreeNode *p, vector<int> &sum, int lvl) {
    if (!p) {
      return;
    }
    if (lvl >= sum.size()) {
      sum.resize(lvl + 1, 0);
    }
    sum[lvl] += p->val;
    solve(p->left, sum, lvl + 1);
    solve(p->right, sum, lvl + 1);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |-10⁵ <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,7,0,7,-8,null,null]
// Output: 2
//
// Level 1 sum = 1.
// Level 2 sum = 7 + 0 = 7.
// Level 3 sum = 7 + -8 = -1.
// So we return the level with the maximum sum which is level 2.

LEETCODE_SOLUTION_UNITTEST(1161, MaximumLevelSumOfABinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 7, 0, 7, -8, null, null});
  int       expect   = 2;
  int       actual   = solution->maxLevelSum(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [989,null,10250,98693,-89388,null,null,null,-32127]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(1161, MaximumLevelSumOfABinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector(
      {989, null, 10250, 98693, -89388, null, null, null, -32127});
  int expect = 2;
  int actual = solution->maxLevelSum(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
