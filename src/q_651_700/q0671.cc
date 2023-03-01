// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Second Minimum Node In a Binary Tree
//
// https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/
//
// Question ID: 671
// Difficult  : Easy
// Solve Date : 2022/10/19 09:00

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |671. Second Minimum Node In a Binary Tree|:
//
// Given a non-empty special binary tree consisting of nodes with the
// non-negative value, where each node in this tree has exactly |two| or |zero|
// sub-node. If the node has two sub-nodes, then this node's value is the
// smaller value among its two sub-nodes. More formally, the property |root.val
// = min(root.left.val, root.right.val)|always holds. Given such a binary tree,
// you need to output the second minimum value in the set made of all the nodes'
// value in the whole tree. If no such second minimum value exists, output -1
// instead.
//

LEETCODE_BEGIN_RESOLVING(671, SecondMinimumNodeInABinaryTree, Solution);

class Solution {
private:
  void find(TreeNode *p, long &res, long min) {
    if (nullptr != p) {
      if (min < p->val && p->val < res) {
        res = p->val;
      } else if (min == p->val) {
        find(p->left, res, min);
        find(p->right, res, min);
      }
    }
  }

public:
  int findSecondMinimumValue(TreeNode *root) {
    auto res = numeric_limits<long>::max();
    find(root, res, nullptr == root ? -1 : root->val);
    return res < numeric_limits<long>::max() ? res : -1;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 25]|.
// * |1 <= Node.val <= 2³¹ - 1|
// * |root.val == min(root.left.val, root.right.val)|for each internal node of
// the tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [2,2,5,null,null,5,7]
// Output: 5
//
// The smallest value is 2, the second smallest value is 5.

LEETCODE_SOLUTION_UNITTEST(671, SecondMinimumNodeInABinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 2, 5, null, null, 5, 7});
  int       expect   = 5;
  int       actual   = solution->findSecondMinimumValue(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [2,2,2]
// Output: -1
//
// The smallest value is 2, but there isn't any second smallest value.

LEETCODE_SOLUTION_UNITTEST(671, SecondMinimumNodeInABinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 2, 2});
  int       expect   = -1;
  int       actual   = solution->findSecondMinimumValue(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
