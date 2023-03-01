// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Postorder Traversal
//
// https://leetcode.com/problems/binary-tree-postorder-traversal/
//
// Question ID: 145
// Difficult  : Easy
// Solve Date : 2021/09/14 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |145. Binary Tree Postorder Traversal|:
//
// Given the |root| of a binary tree, return the postorder traversal of its
// nodes' values.  
//

LEETCODE_BEGIN_RESOLVING(145, BinaryTreePostorderTraversal, Solution);

class Solution {
private:
  void helper(TreeNode *p, vector<int> &re) {
    if (p == nullptr)
      return;
    helper(p->left, re);
    helper(p->right, re);
    re.push_back(p->val);
  }

public:
  vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    helper(root, res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of the nodes in the tree is in the range |[0, 100]|.
// * |-100 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,null,2,3]
// Output: [3,2,1]
//

LEETCODE_SOLUTION_UNITTEST(145, BinaryTreePostorderTraversal, example_1) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({1, null, 2, 3});
  vector<int> expect   = {3, 2, 1};
  vector<int> actual   = solution->postorderTraversal(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(145, BinaryTreePostorderTraversal, example_2) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({});
  vector<int> expect   = {};
  vector<int> actual   = solution->postorderTraversal(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [1]
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(145, BinaryTreePostorderTraversal, example_3) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({1});
  vector<int> expect   = {1};
  vector<int> actual   = solution->postorderTraversal(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
