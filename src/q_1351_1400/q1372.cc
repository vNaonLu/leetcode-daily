// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Longest ZigZag Path in a Binary Tree
//
// https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/
//
// Question ID: 1372
// Difficult  : Medium
// Solve Date : 2023/04/19 12:03

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1372. Longest ZigZag Path in a Binary Tree|:
//
// You are given the |root| of a binary tree.
// A ZigZag path for a binary tree is defined as follow:
//
//  • Choose any node in the binary tree and a direction (right or left).
//
//  • If the current direction is right, move to the right child of the current
//  node; otherwise, move to the left child.
//
//  • Change the direction from right to left or from left to right.
//
//  • Repeat the second and third steps until you can't move in the tree.
// Zigzag length is defined as the number of nodes visited - 1. (A single node
// has a length of 0). Return the longest ZigZag path contained in that tree.
//
//

LEETCODE_BEGIN_RESOLVING(1372, LongestZigZagPathInABinaryTree, Solution);

class Solution {
public:
  int longestZigZag(TreeNode *root) {
    int res = 0;

    travel(&res, root, true, 0);
    travel(&res, root, false, 0);
    return res;
  }

private:
  void travel(int *res, TreeNode *p, bool is_left, int curr_length) {
    if (!p) {
      return;
    }

    *res = max(*res, curr_length);
    if (is_left) {
      travel(res, p->left, false, curr_length + 1);
      travel(res, p->right, true, 1);
    } else {
      travel(res, p->right, true, curr_length + 1);
      travel(res, p->left, false, 1);
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 5 * 10⁴]|.
// * |1 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1,null,1]
// Output: 3
//
// Longest ZigZag path in blue nodes (right -> left -> right).

LEETCODE_SOLUTION_UNITTEST(1372, LongestZigZagPathInABinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({1, null, 1, 1, 1, null, null, 1, 1, null, 1, null,
                            null, null, 1, null, 1});
  int expect = 3;
  int actual = solution->longestZigZag(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,1,1,null,1,null,null,1,1,null,1]
// Output: 4
//
// Longest ZigZag path in blue nodes (left -> right -> left -> right).

LEETCODE_SOLUTION_UNITTEST(1372, LongestZigZagPathInABinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({1, 1, 1, null, 1, null, null, 1, 1, null, 1});
  int expect = 4;
  int actual = solution->longestZigZag(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1372, LongestZigZagPathInABinaryTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1});
  int       expect   = 0;
  int       actual   = solution->longestZigZag(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
