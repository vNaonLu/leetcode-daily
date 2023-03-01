// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Level Order Traversal
//
// https://leetcode.com/problems/binary-tree-level-order-traversal/
//
// Question ID: 102
// Difficult  : Medium
// Solve Date : 2021/09/15 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |102. Binary Tree Level Order Traversal|:
//
// Given the |root| of a binary tree, return the level order traversal of its
// nodes' values. (i.e., from left to right, level by level).  
//

LEETCODE_BEGIN_RESOLVING(102, BinaryTreeLevelOrderTraversal, Solution);

class Solution {
private:
  void helper(TreeNode *p, vector<vector<int>> &r, int level) {
    if (p == nullptr)
      return;
    if (level >= r.size())
      r.resize(level + 1);
    r[level].push_back(p->val);
    helper(p->left, r, level + 1);
    helper(p->right, r, level + 1);
  }

public:
  vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> res;
    helper(root, res, 0);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 2000]|.
// * |-1000 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[9,20],[15,7]]
//

LEETCODE_SOLUTION_UNITTEST(102, BinaryTreeLevelOrderTraversal, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  vector<vector<int>> expect = {
      {3},
      {9, 20},
      {15, 7}
  };
  vector<vector<int>> actual = solution->levelOrder(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1]
// Output: [[1]]
//

LEETCODE_SOLUTION_UNITTEST(102, BinaryTreeLevelOrderTraversal, example_2) {
  auto                solution = MakeSolution();
  TreeNode           *root     = TreeNode::FromVector({1});
  vector<vector<int>> expect   = {{1}};
  vector<vector<int>> actual   = solution->levelOrder(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(102, BinaryTreeLevelOrderTraversal, example_3) {
  auto                solution = MakeSolution();
  TreeNode           *root     = TreeNode::FromVector({});
  vector<vector<int>> expect   = {};
  vector<vector<int>> actual   = solution->levelOrder(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
