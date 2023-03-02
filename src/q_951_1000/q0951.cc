// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Flip Equivalent Binary Trees
//
// https://leetcode.com/problems/flip-equivalent-binary-trees/
//
// Question ID: 951
// Difficult  : Medium
// Solve Date : 2021/11/07 15:03

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |951. Flip Equivalent Binary Trees|:
//
// For a binary tree T, we can define a flip operation as follows: choose any
// node, and swap the left and right child subtrees. A binary tree X is flip
// equivalent to a binary tree Y if and only if we can make X equal to Y after
// some number of flip operations. Given the roots of two binary trees |root1|
// and |root2|, return |true| if the two trees are flip equivalent or |false|
// otherwise.  
//

LEETCODE_BEGIN_RESOLVING(951, FlipEquivalentBinaryTrees, Solution);

class Solution {
public:
  bool flipEquiv(TreeNode *root1, TreeNode *root2) {
    if (root1 == nullptr)
      return root2 == nullptr;
    else if (root2 == nullptr)
      return root1 == nullptr;
    else if (root1->val != root2->val)
      return false;
    return (flipEquiv(root1->left, root2->left) &&
            flipEquiv(root1->right, root2->right)) ||
           (flipEquiv(root1->left, root2->right) &&
            flipEquiv(root1->right, root2->left));
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in each tree is in the range |[0, 100]|.
// * Each tree will have unique node values in the range |[0, 99]|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root1 = [1,2,3,4,5,6,null,null,null,7,8], root2 =
//  [1,3,2,null,6,4,5,null,null,null,null,8,7]
// Output: true
//
// We flipped at nodes with values 1, 3, and 5.

LEETCODE_SOLUTION_UNITTEST(951, FlipEquivalentBinaryTrees, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root1 =
      TreeNode::FromVector({1, 2, 3, 4, 5, 6, null, null, null, 7, 8});
  TreeNode *root2 = TreeNode::FromVector(
      {1, 3, 2, null, 6, 4, 5, null, null, null, null, 8, 7});
  bool expect = true;
  bool actual = solution->flipEquiv(root1, root2);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root1, root2);
}

// [Example #2]
//  Input: root1 = [], root2 = []
// Output: true
//

LEETCODE_SOLUTION_UNITTEST(951, FlipEquivalentBinaryTrees, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root1    = TreeNode::FromVector({});
  TreeNode *root2    = TreeNode::FromVector({});
  bool      expect   = true;
  bool      actual   = solution->flipEquiv(root1, root2);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root1, root2);
}

// [Example #3]
//  Input: root1 = [], root2 = [1]
// Output: false
//

LEETCODE_SOLUTION_UNITTEST(951, FlipEquivalentBinaryTrees, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root1    = TreeNode::FromVector({});
  TreeNode *root2    = TreeNode::FromVector({1});
  bool      expect   = false;
  bool      actual   = solution->flipEquiv(root1, root2);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root1, root2);
}
