// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Depth of Binary Tree
//
// https://leetcode.com/problems/maximum-depth-of-binary-tree/
//
// Question ID: 104
// Difficult  : Easy
// Solve Date : 2021/09/15 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |104. Maximum Depth of Binary Tree|:
//
// Given the |root| of a binary tree, return its maximum depth.
// A binary tree's maximum depth is the number of nodes along the longest path
// from the root node down to the farthest leaf node.  
//

LEETCODE_BEGIN_RESOLVING(104, MaximumDepthOfBinaryTree, Solution);

class Solution {
private:
  int helper(TreeNode *p, int h = 0) {
    if (p == nullptr)
      return h;
    return max({h, helper(p->left, h + 1), helper(p->right, h + 1)});
  }

public:
  int maxDepth(TreeNode *root) {
    int res = helper(root);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 10⁴]|.
// * |-100 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,9,20,null,null,15,7]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(104, MaximumDepthOfBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  int       expect   = 3;
  int       actual   = solution->maxDepth(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,null,2]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(104, MaximumDepthOfBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, null, 2});
  int       expect   = 2;
  int       actual   = solution->maxDepth(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
