// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Left Leaves
//
// https://leetcode.com/problems/sum-of-left-leaves/
//
// Question ID: 404
// Difficult  : Easy
// Solve Date : 2021/11/04 18:00

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |404. Sum of Left Leaves|:
//
// Given the |root| of a binary tree, return the sum of all left leaves.
// A leaf is a node with no children. A left leaf is a leaf that is the left
// child of another node.  
//

LEETCODE_BEGIN_RESOLVING(404, SumOfLeftLeaves, Solution);

class Solution {
public:
  int sumOfLeftLeaves(TreeNode *root, TreeNode *pre = nullptr) {
    if (root == nullptr)
      return 0;
    if (root->left == nullptr && root->right == nullptr && pre != nullptr &&
        pre->left == root)
      return root->val;
    return sumOfLeftLeaves(root->left, root) +
           sumOfLeftLeaves(root->right, root);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 1000]|.
// * |-1000 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,9,20,null,null,15,7]
// Output: 24
//
// There are two left leaves in the binary tree, with values 9 and 15
// respectively.

LEETCODE_SOLUTION_UNITTEST(404, SumOfLeftLeaves, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  int       expect   = 24;
  int       actual   = solution->sumOfLeftLeaves(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(404, SumOfLeftLeaves, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1});
  int       expect   = 0;
  int       actual   = solution->sumOfLeftLeaves(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
