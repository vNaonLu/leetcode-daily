// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Univalued Binary Tree
//
// https://leetcode.com/problems/univalued-binary-tree/
//
// Question ID: 965
// Difficult  : Easy
// Solve Date : 2022/10/12 13:54

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |965. Univalued Binary Tree|:
//
// A binary tree is uni-valued if every node in the tree has the same value.
// Given the |root| of a binary tree, return |true| if the given tree is
// uni-valued, or |false| otherwise.
//

LEETCODE_BEGIN_RESOLVING(965, UnivaluedBinaryTree, Solution);

class Solution {
public:
  bool isUnivalTree(TreeNode *root) {
    if (nullptr == root) {
      return true;
    }
    auto left = nullptr == root->left ||
                (root->val == root->left->val && isUnivalTree(root->left));
    auto right = nullptr == root->right ||
                 (root->val == root->right->val && isUnivalTree(root->right));
    return left && right;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 100]|.
// * |0 <= Node.val < 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,1,1,1,1,null,1]
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(965, UnivaluedBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 1, 1, 1, 1, null, 1});
  bool      expect   = true;
  bool      actual   = solution->isUnivalTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [2,2,2,5,2]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(965, UnivaluedBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({2, 2, 2, 5, 2});
  bool      expect   = false;
  bool      actual   = solution->isUnivalTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
