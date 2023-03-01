// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Right Side View
//
// https://leetcode.com/problems/binary-tree-right-side-view/
//
// Question ID: 199
// Difficult  : Medium
// Solve Date : 2021/10/04 12:31

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |199. Binary Tree Right Side View|:
//
// Given the |root| of a binary tree, imagine yourself standing on the right
// side of it, return the values of the nodes you can see ordered from top to
// bottom.  
//

LEETCODE_BEGIN_RESOLVING(199, BinaryTreeRightSideView, Solution);

class Solution {
private:
  void helper(TreeNode *p, vector<int> &r, int level = 0) {
    if (p == nullptr)
      return;
    if (level >= r.size())
      r.resize(level + 1, 0);
    r[level] = p->val;
    helper(p->left, r, level + 1);
    helper(p->right, r, level + 1);
  }

public:
  vector<int> rightSideView(TreeNode *root) {
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
//  Input: root = [1,2,3,null,5,null,4]
// Output: [1,3,4]
//

LEETCODE_SOLUTION_UNITTEST(199, BinaryTreeRightSideView, example_1) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({1, 2, 3, null, 5, null, 4});
  vector<int> expect   = {1, 3, 4};
  vector<int> actual   = solution->rightSideView(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,null,3]
// Output: [1,3]
//

LEETCODE_SOLUTION_UNITTEST(199, BinaryTreeRightSideView, example_2) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({1, null, 3});
  vector<int> expect   = {1, 3};
  vector<int> actual   = solution->rightSideView(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = []
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(199, BinaryTreeRightSideView, example_3) {
  auto        solution = MakeSolution();
  TreeNode   *root     = TreeNode::FromVector({});
  vector<int> expect   = {};
  vector<int> actual   = solution->rightSideView(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
