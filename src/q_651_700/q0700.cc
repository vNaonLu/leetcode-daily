// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Search in a Binary Search Tree
//
// https://leetcode.com/problems/search-in-a-binary-search-tree/
//
// Question ID: 700
// Difficult  : Easy
// Solve Date : 2021/09/17 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |700. Search in a Binary Search Tree|:
//
// You are given the |root| of a binary search tree (BST) and an integer |val|.
// Find the node in the BST that the node's value equals |val| and return the
// subtree rooted with that node. If such a node does not exist, return |null|.
//  
//

LEETCODE_BEGIN_RESOLVING(700, SearchInABinarySearchTree, Solution);

class Solution {
public:
  TreeNode *searchBST(TreeNode *root, int val) {
    while (root != nullptr && root->val != val) {
      if (root->val > val) {
        root = root->left;
      } else if (root->val < val) {
        root = root->right;
      }
    }
    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 5000]|.
// * |1 <= Node.val <= 10⁷|
// * |root| is a binary search tree.
// * |1 <= val <= 10⁷|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [4,2,7,1,3], val = 2
// Output: [2,1,3]
//

LEETCODE_SOLUTION_UNITTEST(700, SearchInABinarySearchTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 2, 7, 1, 3});
  int       val      = 2;
  TreeNode *expect   = TreeNode::FromVector({2, 1, 3});
  TreeNode *actual   = solution->searchBST(root, val);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}

// [Example #2]
//  Input: root = [4,2,7,1,3], val = 5
// Output: []
//

LEETCODE_SOLUTION_UNITTEST(700, SearchInABinarySearchTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 2, 7, 1, 3});
  int       val      = 5;
  TreeNode *expect   = TreeNode::FromVector({});
  TreeNode *actual   = solution->searchBST(root, val);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect);
}
