// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Distribute Coins in Binary Tree
//
// https://leetcode.com/problems/distribute-coins-in-binary-tree/
//
// Question ID: 979
// Difficult  : Medium
// Solve Date : 2024/05/18 14:58

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |979. Distribute Coins in Binary Tree|:
//
// You are given the |root| of a binary tree with |n| nodes where each |node| in
// the tree has |node.val| coins. There are |n| coins in total throughout the
// whole tree. In one move, we may choose two adjacent nodes and move one coin
// from one node to another. A move may be from parent to child, or from child
// to parent. Return the minimum number of moves required to make every node
// have exactly one coin.
//
//

LEETCODE_BEGIN_RESOLVING(979, DistributeCoinsInBinaryTree, Solution);

class Solution {
public:
  int distributeCoins(TreeNode *root) {
    int res = 0;
    helper(root, &res);
    return res;
  }

private:
  int helper(TreeNode *p, int *res) {
    if (!p) {
      return 0;
    }

    int left  = helper(p->left, res);
    int right = helper(p->right, res);
    (*res) += abs(left) + abs(right);
    return (p->val - 1) + left + right;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is |n|.
// * |1 <= n <= 100|
// * |0 <= Node.val <= n|
// * The sum of all |Node.val| is |n|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,0,0]
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(979, DistributeCoinsInBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 0, 0});
  int       expect   = 2;
  int       actual   = solution->distributeCoins(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [0,3,0]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(979, DistributeCoinsInBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0, 3, 0});
  int       expect   = 3;
  int       actual   = solution->distributeCoins(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
