// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Cousins in Binary Tree
//
// https://leetcode.com/problems/cousins-in-binary-tree/
//
// Question ID: 993
// Difficult  : Easy
// Solve Date : 2021/10/18 12:57

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <queue>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |993. Cousins in Binary Tree|:
//
// Given the |root| of a binary tree with unique values and the values of two
// different nodes of the tree |x| and |y|, return |true| if the nodes
// corresponding to the values |x| and |y| in the tree are cousins, or |false|
// otherwise. Two nodes of a binary tree are cousins if they have the same depth
// with different parents. Note that in a binary tree, the root node is at the
// depth |0|, and children of each depth |k| node are at the depth |k + 1|.  
//

LEETCODE_BEGIN_RESOLVING(993, CousinsInBinaryTree, Solution);

class Solution {
public:
  bool isCousins(TreeNode *root, int x, int y) {
    queue<pair<TreeNode *, TreeNode *>> q;
    TreeNode                           *xparent = nullptr, *yparent = nullptr;
    q.push(make_pair(root, nullptr));
    while (!q.empty() && xparent == nullptr && yparent == nullptr) {
      int node_same_level = q.size();
      while (node_same_level--) {
        auto p = q.front();
        q.pop();
        if (p.first->val == x)
          xparent = p.second;
        else if (p.first->val == y)
          yparent = p.second;
        if (p.first->left)
          q.push(make_pair(p.first->left, p.first));
        if (p.first->right)
          q.push(make_pair(p.first->right, p.first));
      }
    }
    return xparent != nullptr && yparent != nullptr && xparent != yparent;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[2, 100]|.
// * |1 <= Node.val <= 100|
// * Each node has a unique value.
// * |x != y|
// * |x| and |y| are exist in the tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,4], x = 4, y = 3
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(993, CousinsInBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, 4});
  int       x        = 4;
  int       y        = 3;
  bool      expect   = false;
  bool      actual   = solution->isCousins(root, x, y);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(993, CousinsInBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, null, 4, null, 5});
  int       x        = 5;
  int       y        = 4;
  bool      expect   = true;
  bool      actual   = solution->isCousins(root, x, y);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [1,2,3,null,4], x = 2, y = 3
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(993, CousinsInBinaryTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, null, 4});
  int       x        = 2;
  int       y        = 3;
  bool      expect   = false;
  bool      actual   = solution->isCousins(root, x, y);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
