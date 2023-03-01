// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Minimum Depth of Binary Tree
//
// https://leetcode.com/problems/minimum-depth-of-binary-tree/
//
// Question ID: 111
// Difficult  : Easy
// Solve Date : 2021/10/11 17:55

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |111. Minimum Depth of Binary Tree|:
//
// Given a binary tree, find its minimum depth.
// The minimum depth is the number of nodes along the shortest path from the
// root node down to the nearest leaf node. Note: A leaf is a node with no
// children.  
//

LEETCODE_BEGIN_RESOLVING(111, MinimumDepthOfBinaryTree, Solution);

class Solution {
public:
  int minDepth(TreeNode *root) {
    if (root == nullptr)
      return 0;
    if (root->left == nullptr) {
      return minDepth(root->right) + 1;
    } else if (root->right == nullptr) {
      return minDepth(root->left) + 1;
    } else {
      int left  = minDepth(root->left);
      int right = minDepth(root->right);
      return min(left, right) + 1;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 10⁵]|.
// * |-1000 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,9,20,null,null,15,7]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(111, MinimumDepthOfBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  int       expect   = 2;
  int       actual   = solution->minDepth(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [2,null,3,null,4,null,5,null,6]
// Output: 5
//

LEETCODE_SOLUTION_UNITTEST(111, MinimumDepthOfBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({2, null, 3, null, 4, null, 5, null, 6});
  int expect = 5;
  int actual = solution->minDepth(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
