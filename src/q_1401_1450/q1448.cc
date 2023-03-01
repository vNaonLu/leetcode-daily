// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Count Good Nodes in Binary Tree
//
// https://leetcode.com/problems/count-good-nodes-in-binary-tree/
//
// Question ID: 1448
// Difficult  : Medium
// Solve Date : 2022/09/01 17:43

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <limits>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1448. Count Good Nodes in Binary Tree|:
//
// Given a binary tree |root|, a node X in the tree is namedgood if in the path
// from root to X there are no nodes with a value greater than X.
//
// Return the number of good nodes in the binary tree.
//
//
//

LEETCODE_BEGIN_RESOLVING(1448, CountGoodNodesInBinaryTree, Solution);

class Solution {
private:
  void helper(TreeNode *p, int &r, int m = numeric_limits<int>::min()) {
    if (!p)
      return;
    if (p->val >= m)
      r++;
    helper(p->left, r, max(m, p->val));
    helper(p->right, r, max(m, p->val));
  }

public:
  int goodNodes(TreeNode *root) {
    int res = 0;
    helper(root, res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the binary tree is in the range |[1, 10^5]|.
// * Each node's value is between |[-10^4, 10^4]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,1,4,3,null,1,5]
// Output: 4
//
// Nodes in blue are good.
// Root Node (3) is always a good node.
// Node 4 -> (3,4) is the maximum value in the path starting from the root.
// Node 5 -> (3,4,5) is the maximum value in the path
// Node 3 -> (3,1,3) is the maximum value in the path.

LEETCODE_SOLUTION_UNITTEST(1448, CountGoodNodesInBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 1, 4, 3, null, 1, 5});
  int       expect   = 4;
  int       actual   = solution->goodNodes(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [3,3,null,4,2]
// Output: 3
//
// Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.

LEETCODE_SOLUTION_UNITTEST(1448, CountGoodNodesInBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 3, null, 4, 2});
  int       expect   = 3;
  int       actual   = solution->goodNodes(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [1]
// Output: 1
//
// Root is considered as good.

LEETCODE_SOLUTION_UNITTEST(1448, CountGoodNodesInBinaryTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1});
  int       expect   = 1;
  int       actual   = solution->goodNodes(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
