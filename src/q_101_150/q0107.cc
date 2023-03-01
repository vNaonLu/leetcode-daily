// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Level Order Traversal II
//
// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
//
// Question ID: 107
// Difficult  : Medium
// Solve Date : 2023/02/20 10:58

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |107. Binary Tree Level Order Traversal II|:
//
// Given the |root| of a binary tree, return the bottom-up level order traversal
// of its nodes' values. (i.e., from left to right, level by level from leaf to
// root).
//

LEETCODE_BEGIN_RESOLVING(107, BinaryTreeLevelOrderTraversalII, Solution);

class Solution {
private:
  void helper(vector<vector<int>> &res, TreeNode *p, int level = 0) {
    if (p) {
      if (res.size() <= level) {
        res.resize(level + 1);
      }
      res[level].emplace_back(p->val);
      helper(res, p->left, level + 1);
      helper(res, p->right, level + 1);
    }
  }

public:
  vector<vector<int>> levelOrderBottom(TreeNode *root) {
    vector<vector<int>> res;
    helper(res, root);
    reverse(res.begin(), res.end());
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
// Output: [[15,7],[9,20],[3]]
//

LEETCODE_SOLUTION_UNITTEST(107, BinaryTreeLevelOrderTraversalII, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  vector<vector<int>> expect = {
      {15, 7},
      {9, 20},
      {3}
  };
  vector<vector<int>> actual = solution->levelOrderBottom(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1]
// Output: [[1]]
//

LEETCODE_SOLUTION_UNITTEST(107, BinaryTreeLevelOrderTraversalII, example_2) {
  auto                solution = MakeSolution();
  TreeNode           *root     = TreeNode::FromVector({1});
  vector<vector<int>> expect   = {{1}};
  vector<vector<int>> actual   = solution->levelOrderBottom(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(107, BinaryTreeLevelOrderTraversalII, example_3) {
  auto                solution = MakeSolution();
  TreeNode           *root     = TreeNode::FromVector({});
  vector<vector<int>> expect   = {};
  vector<vector<int>> actual   = solution->levelOrderBottom(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
