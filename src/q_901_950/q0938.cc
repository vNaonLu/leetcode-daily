// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Range Sum of BST
//
// https://leetcode.com/problems/range-sum-of-bst/
//
// Question ID: 938
// Difficult  : Easy
// Solve Date : 2021/12/14 18:05

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |938. Range Sum of BST|:
//
// Given the |root| node of a binary search tree and two integers |low| and
// |high|, return the sum of values of all nodes with a value in the inclusive
// range |[low, high]|.  
//

LEETCODE_BEGIN_RESOLVING(938, RangeSumOfBST, Solution);

class Solution {
public:
  int rangeSumBST(TreeNode *root, int low, int high) {
    if (root == nullptr)
      return 0;
    if (root->val < low)
      return rangeSumBST(root->right, low, high);
    else if (root->val > high)
      return rangeSumBST(root->left, low, high);
    else if (root->val == high)
      return root->val + rangeSumBST(root->left, low, high);
    else if (root->val == low)
      return root->val + rangeSumBST(root->right, low, high);
    else
      return root->val + rangeSumBST(root->left, low, high) +
             rangeSumBST(root->right, low, high);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 2 * 10⁴]|.
// * |1 <= Node.val <= 10⁵|
// * |1 <= low <= high <= 10⁵|
// * All |Node.val| are unique.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
// Output: 32
//
// Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.

LEETCODE_SOLUTION_UNITTEST(938, RangeSumOfBST, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({10, 5, 15, 3, 7, null, 18});
  int       low      = 7;
  int       high     = 15;
  int       expect   = 32;
  int       actual   = solution->rangeSumBST(root, low, high);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
// Output: 23
//
// Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.

LEETCODE_SOLUTION_UNITTEST(938, RangeSumOfBST, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root = TreeNode::FromVector({10, 5, 15, 3, 7, 13, 18, 1, null, 6});
  int       low  = 6;
  int       high = 10;
  int       expect = 23;
  int       actual = solution->rangeSumBST(root, low, high);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
