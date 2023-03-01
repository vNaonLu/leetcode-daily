// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Find Largest Value in Each Tree Row
//
// https://leetcode.com/problems/find-largest-value-in-each-tree-row/
//
// Question ID: 515
// Difficult  : Medium
// Solve Date : 2022/01/30 13:24

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <limits>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |515. Find Largest Value in Each Tree Row|:
//
// Given the |root| of a binary tree, return an array of the largest value in
// each row of the tree (0-indexed).  
//

LEETCODE_BEGIN_RESOLVING(515, FindLargestValueInEachTreeRow, Solution);

class Solution {
private:
  void helper(TreeNode *p, vector<int> &v, int curr) {
    if (nullptr == p)
      return;
    if (curr >= v.size())
      v.resize(curr + 1, numeric_limits<int>::min());
    v[curr] = max(v[curr], p->val);
    helper(p->left, v, curr + 1);
    helper(p->right, v, curr + 1);
  }

public:
  vector<int> largestValues(TreeNode *root) {
    vector<int> res;
    helper(root, res, 0);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree will be in the range |[0, 10⁴]|.
// * |-2³¹ <= Node.val <= 2³¹ - 1|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,3,2,5,3,null,9]
// Output: [1,3,9]
//

LEETCODE_SOLUTION_UNITTEST(515, FindLargestValueInEachTreeRow, example_1) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({1, 3, 2, 5, 3, null, 9});
  vector<int> expect   = {1, 3, 9};
  vector<int> actual   = solution->largestValues(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3]
// Output: [1,3]
//

LEETCODE_SOLUTION_UNITTEST(515, FindLargestValueInEachTreeRow, example_2) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({1, 2, 3});
  vector<int> expect   = {1, 3};
  vector<int> actual   = solution->largestValues(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
