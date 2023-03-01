// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Path Sum II
//
// https://leetcode.com/problems/path-sum-ii/
//
// Question ID: 113
// Difficult  : Medium
// Solve Date : 2021/10/04 12:40

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |113. Path Sum II|:
//
// Given the |root| of a binary tree and an integer |targetSum|, return all
// root-to-leaf paths where the sum of the node values in the path equals
// |targetSum|. Each path should be returned as a list of the node values, not
// node references. A root-to-leaf path is a path starting from the root and
// ending at any leaf node. A leaf is a node with no children.  
//

LEETCODE_BEGIN_RESOLVING(113, PathSumII, Solution);

class Solution {
private:
  void helper(TreeNode *p, vector<vector<int>> &r, vector<int> &cur,
              const int &t, int sum = 0) {
    if (p == nullptr)
      return;
    sum += p->val;
    cur.push_back(p->val);
    if (sum == t && p->left == nullptr && p->right == nullptr) {
      r.push_back(cur);
    } else {
      helper(p->left, r, cur, t, sum);
      helper(p->right, r, cur, t, sum);
    }
    sum -= p->val;
    cur.pop_back();
  }

public:
  vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
    vector<vector<int>> res;
    vector<int>         tmp;
    helper(root, res, tmp, targetSum);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 5000]|.
// * |-1000 <= Node.val <= 1000|
// * |-1000 <= targetSum <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
// Output: [[5,4,11,2],[5,8,4,5]]
//
// There are two paths whose sum equals targetSum:
// 5 + 4 + 11 + 2 = 22
// 5 + 8 + 4 + 5 = 22

LEETCODE_SOLUTION_UNITTEST(113, PathSumII, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1});
  int                 targetSum = 22;
  vector<vector<int>> expect    = {
      {5, 4, 11, 2},
      {5, 8,  4, 5}
  };
  vector<vector<int>> actual = solution->pathSum(root, targetSum);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3], targetSum = 5
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(113, PathSumII, example_2) {
  auto                solution  = MakeSolution();
  TreeNode           *root      = TreeNode::FromVector({1, 2, 3});
  int                 targetSum = 5;
  vector<vector<int>> expect    = {};
  vector<vector<int>> actual    = solution->pathSum(root, targetSum);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [1,2], targetSum = 0
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(113, PathSumII, example_3) {
  auto                solution  = MakeSolution();
  TreeNode           *root      = TreeNode::FromVector({1, 2});
  int                 targetSum = 0;
  vector<vector<int>> expect    = {};
  vector<vector<int>> actual    = solution->pathSum(root, targetSum);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
