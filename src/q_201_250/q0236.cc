// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Lowest Common Ancestor of a Binary Tree
//
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
//
// Question ID: 236
// Difficult  : Medium
// Solve Date : 2021/10/06 13:27

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |236. Lowest Common Ancestor of a Binary Tree|:
//
// Given a binary tree, find the lowest common ancestor (LCA) of two given nodes
// in the tree. According to the [definition of LCA on Wikipedia]: “The lowest
// common ancestor is defined between two nodes |p| and |q| as the lowest node
// in |T| that has both |p| and |q| as descendants (where we allow a node to be
// a descendant of itself).”  
//

LEETCODE_BEGIN_RESOLVING(236, LowestCommonAncestorOfABinaryTree, Solution);

class Solution {
private:
  bool findPath(vector<TreeNode *> &path, TreeNode *p, TreeNode *t) {
    if (p == nullptr) {

      return false;
    } else if (p == t) {
      path.emplace_back(p);

      return true;
    } else {
      path.emplace_back(p);

      return findPath(path, p->left, t) || findPath(path, p->right, t) ||
             (path.pop_back(), false);
    }
  }

public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    vector<TreeNode *> path_p, path_q;

    if (findPath(path_p, root, p) && findPath(path_q, root, q)) {
      auto p_it = path_p.begin(), q_it = path_q.begin();

      while (p_it != path_p.end() && q_it != path_q.end()) {
        if (*(p_it++) != *(q_it++)) {
          return *(p_it - 2);
        }
      }

      return p_it == path_p.end() ? *(--p_it) : *(--q_it);
    }

    return nullptr;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[2, 10⁵]|.
// * |-10⁹ <= Node.val <= 10⁹|
// * All |Node.val| are unique.
// * |p != q|
// * |p| and |q| will exist in the tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
// Output: 3
//
// The LCA of nodes 5 and 1 is 3.

LEETCODE_SOLUTION_UNITTEST(236, LowestCommonAncestorOfABinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({3, 5, 1, 6, 2, 0, 8, null, null, 7, 4});
  TreeNode *p      = root->GetChild(1);
  TreeNode *q      = root->GetChild(6);
  TreeNode *expect = root->GetChild(0);
  TreeNode *actual = solution->lowestCommonAncestor(root, p, q);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, p, q, expect, actual);
}

// [Example #2]
//  Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
// Output: 5
//
// The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself
// according to the LCA definition.

LEETCODE_SOLUTION_UNITTEST(236, LowestCommonAncestorOfABinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({3, 5, 1, 6, 2, 0, 8, null, null, 7, 4});
  TreeNode *p      = root->GetChild(1);
  TreeNode *q      = root->GetChild(5);
  TreeNode *expect = root->GetChild(1);
  TreeNode *actual = solution->lowestCommonAncestor(root, p, q);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, p, q, expect, actual);
}

// [Example #3]
//  Input: root = [1,2], p = 1, q = 2
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(236, LowestCommonAncestorOfABinaryTree, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2});
  TreeNode *p      = root->GetChild(0);
  TreeNode *q      = root->GetChild(1);
  TreeNode *expect = root->GetChild(0);
  TreeNode *actual = solution->lowestCommonAncestor(root, p, q);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, p, q, expect, actual);
}
