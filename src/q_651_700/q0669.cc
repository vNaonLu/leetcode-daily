// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Trim a Binary Search Tree
//
// https://leetcode.com/problems/trim-a-binary-search-tree/
//
// Question ID: 669
// Difficult  : Medium
// Solve Date : 2022/04/15 19:30

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |669. Trim a Binary Search Tree|:
//
// Given the |root| of a binary search tree and the lowest and highest
// boundaries as |low| and |high|, trim the tree so that all its elements lies
// in |[low, high]|. Trimming the tree should not change the relative structure
// of the elements that will remain in the tree (i.e., any node's descendant
// should remain a descendant). It can be proven that there is a unique answer.
// Return the root of the trimmed binary search tree. Note that the root may
// change depending on the given bounds.  
//

LEETCODE_BEGIN_RESOLVING(669, TrimABinarySearchTree, Solution);

class Solution {
private:
  TreeNode *trim_low(TreeNode *root, int target) {
    if (nullptr == root) {
      return nullptr;
    } else if (root->val < target) {
      auto right = root->right;
      delete root;
      return trim_low(right, target);
    } else {
      root->left = trim_low(root->left, target);

      return root;
    }
  }

  TreeNode *trim_high(TreeNode *root, int target) {
    if (nullptr == root) {
      return nullptr;
    } else if (root->val > target) {
      auto left = root->left;
      delete root;
      return trim_high(left, target);
    } else {
      root->right = trim_high(root->right, target);

      return root;
    }
  }

public:
  TreeNode *trimBST(TreeNode *root, int low, int high) {
    root = trim_low(root, low);
    root = trim_high(root, high);

    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |0 <= Node.val <= 10⁴|
// * The value of each node in the tree is unique.
// * |root| is guaranteed to be a valid binary search tree.
// * |0 <= low <= high <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,0,2], low = 1, high = 2
// Output: [1,null,2]
//

LEETCODE_SOLUTION_UNITTEST(669, TrimABinarySearchTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 0, 2});
  int       low      = 1;
  int       high     = 2;
  TreeNode *expect   = TreeNode::FromVector({1, null, 2});
  TreeNode *actual   = solution->trimBST(root, low, high);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [3,0,4,null,2,null,null,1], low = 1, high = 3
// Output: [3,2,null,1]
//

LEETCODE_SOLUTION_UNITTEST(669, TrimABinarySearchTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 0, 4, null, 2, null, null, 1});
  int       low      = 1;
  int       high     = 3;
  TreeNode *expect   = TreeNode::FromVector({3, 2, null, 1});
  TreeNode *actual   = solution->trimBST(root, low, high);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}
