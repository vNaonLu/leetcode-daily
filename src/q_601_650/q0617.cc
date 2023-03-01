// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Merge Two Binary Trees
//
// https://leetcode.com/problems/merge-two-binary-trees/
//
// Question ID: 617
// Difficult  : Easy
// Solve Date : 2021/09/12 08:00

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |617. Merge Two Binary Trees|:
//
// You are given two binary trees |root1| and |root2|.
// Imagine that when you put one of them to cover the other, some nodes of the
// two trees are overlapped while the others are not. You need to merge the two
// trees into a new binary tree. The merge rule is that if two nodes overlap,
// then sum node values up as the new value of the merged node. Otherwise, the
// NOT null node will be used as the node of the new tree. Return the merged
// tree. Note: The merging process must start from the root nodes of both trees.
//  
//

LEETCODE_BEGIN_RESOLVING(617, MergeTwoBinaryTrees, Solution);

class Solution {
public:
  TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
    if (root1 != nullptr && root2 != nullptr) {
      root1->val += root2->val;
      root1->left  = mergeTrees(root1->left, root2->left);
      root1->right = mergeTrees(root1->right, root2->right);
      return root1;
    } else if (root2 == nullptr) {
      return root1;
    } else {
      return root2;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in both trees is in the range |[0, 2000]|.
// * |-10⁴ <= Node.val <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
// Output: [3,4,5,5,4,null,7]
//

LEETCODE_SOLUTION_UNITTEST(617, MergeTwoBinaryTrees, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root1    = TreeNode::FromVector({1, 3, 2, 5});
  TreeNode *root2    = TreeNode::FromVector({2, 1, 3, null, 4, null, 7});
  TreeNode *expect   = TreeNode::FromVector({3, 4, 5, 5, 4, null, 7});
  TreeNode *actual   = solution->mergeTrees(root1, root2);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root1, root2, expect, actual);
}

// [Example #2]
//  Input: root1 = [1], root2 = [1,2]
// Output: [2,2]
//

LEETCODE_SOLUTION_UNITTEST(617, MergeTwoBinaryTrees, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root1    = TreeNode::FromVector({1});
  TreeNode *root2    = TreeNode::FromVector({1, 2});
  TreeNode *expect   = TreeNode::FromVector({2, 2});
  TreeNode *actual   = solution->mergeTrees(root1, root2);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root1, root2, expect, actual);
}
