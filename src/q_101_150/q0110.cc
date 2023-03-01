// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Balanced Binary Tree
//
// https://leetcode.com/problems/balanced-binary-tree/
//
// Question ID: 110
// Difficult  : Easy
// Solve Date : 2021/10/11 18:09

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <map>
#include <unordered_map>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |110. Balanced Binary Tree|:
//
// Given a binary tree, determine if it is height-balanced.
//  
//

LEETCODE_BEGIN_RESOLVING(110, BalancedBinaryTree, Solution);

class Solution {
private:
  unordered_map<TreeNode *, int> memo;

  int height(TreeNode *p) {
    if (nullptr == p) {
      return 0;
    }
    auto find = memo.find(p);
    if (find == memo.end()) {
      return memo[p] = max(height(p->left), height(p->right)) + 1;
    }
    return find->second;
  }

  bool solve(TreeNode *p) {
    if (nullptr == p) {
      return true;
    }
    if (!solve(p->left) || !solve(p->right)) {
      return false;
    }
    auto l_h = height(p->left);
    auto r_h = height(p->right);
    return abs(l_h - r_h) <= 1;
  }

public:
  bool isBalanced(TreeNode *root) {
    memo.clear();
    return solve(root);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 5000]|.
// * |-10⁴ <= Node.val <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,9,20,null,null,15,7]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(110, BalancedBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  bool      expect   = true;
  bool      actual   = solution->isBalanced(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,2,3,3,null,null,4,4]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(110, BalancedBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 2, 3, 3, null, null, 4, 4});
  bool      expect   = false;
  bool      actual   = solution->isBalanced(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = []
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(110, BalancedBinaryTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({});
  bool      expect   = true;
  bool      actual   = solution->isBalanced(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
