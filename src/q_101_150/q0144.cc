// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Preorder Traversal
//
// https://leetcode.com/problems/binary-tree-preorder-traversal/
//
// Question ID: 144
// Difficult  : Easy
// Solve Date : 2021/09/14 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |144. Binary Tree Preorder Traversal|:
//
// Given the |root| of a binary tree, return the preorder traversal of its
// nodes' values.  
//

LEETCODE_BEGIN_RESOLVING(144, BinaryTreePreorderTraversal, Solution);

class Solution {
private:
  void helper(TreeNode *p, vector<int> &re) {
    if (p == nullptr)
      return;
    re.push_back(p->val);
    helper(p->left, re);
    helper(p->right, re);
  }

public:
  vector<int> preorderTraversal(TreeNode *root) {
    vector<int> res;
    helper(root, res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 100]|.
// * |-100 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,null,2,3]
// Output: [1,2,3]
//

LEETCODE_SOLUTION_UNITTEST(144, BinaryTreePreorderTraversal, example_1) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({1, null, 2, 3});
  vector<int> expect   = {1, 2, 3};
  vector<int> actual   = solution->preorderTraversal(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(144, BinaryTreePreorderTraversal, example_2) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({});
  vector<int> expect   = {};
  vector<int> actual   = solution->preorderTraversal(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [1]
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(144, BinaryTreePreorderTraversal, example_3) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({1});
  vector<int> expect   = {1};
  vector<int> actual   = solution->preorderTraversal(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
