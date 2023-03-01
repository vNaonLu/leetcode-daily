// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Lowest Common Ancestor of a Binary Search Tree
//
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
//
// Question ID: 235
// Difficult  : Medium
// Solve Date : 2021/09/18 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |235. Lowest Common Ancestor of a Binary Search Tree|:
//
// Given a binary search tree (BST), find the lowest common ancestor (LCA) node
// of two given nodes in the BST. According to the [definition of LCA on
// Wikipedia]: “The lowest common ancestor is defined between two nodes |p| and
// |q| as the lowest node in |T| that has both |p| and |q| as descendants (where
// we allow a node to be a descendant of itself).”  
//

LEETCODE_BEGIN_RESOLVING(235, LowestCommonAncestorOfABinarySearchTree,
                         Solution);

class Solution {
private:
  bool isChild(TreeNode *root, TreeNode *p) {
    if (root == p)
      return true;
    else if (root == nullptr)
      return false;
    else
      return isChild(root->right, p) || isChild(root->left, p);
  }

public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (root == p || root == q)
      return root;
    auto p_exsit_right = isChild(root->right, p);
    auto q_exsit_right = isChild(root->right, q);
    if (p_exsit_right && q_exsit_right)
      return lowestCommonAncestor(root->right, p, q);
    else if (!p_exsit_right && !q_exsit_right)
      return lowestCommonAncestor(root->left, p, q);
    else
      return root;
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
// * |p| and |q| will exist in the BST.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
// Output: 6
//
// The LCA of nodes 2 and 8 is 6.

LEETCODE_SOLUTION_UNITTEST(235, LowestCommonAncestorOfABinarySearchTree,
                           example_1) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #2]
//  Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
// Output: 2
//
// The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself
// according to the LCA definition.

LEETCODE_SOLUTION_UNITTEST(235, LowestCommonAncestorOfABinarySearchTree,
                           example_2) {
  GTEST_SKIP() << "Unittest Not Implemented";
}

// [Example #3]
//  Input: root = [2,1], p = 2, q = 1
// Output: 2
//

LEETCODE_SOLUTION_UNITTEST(235, LowestCommonAncestorOfABinarySearchTree,
                           example_3) {
  GTEST_SKIP() << "Unittest Not Implemented";
}
