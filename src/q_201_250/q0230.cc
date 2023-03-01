// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Kth Smallest Element in a BST
//
// https://leetcode.com/problems/kth-smallest-element-in-a-bst/
//
// Question ID: 230
// Difficult  : Medium
// Solve Date : 2021/10/05 12:25

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <stack>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |230. Kth Smallest Element in a BST|:
//
// Given the |root| of a binary search tree, and an integer |k|, return the
// |kᵗʰ| smallest value (1-indexed) of all the values of the nodes in the tree.
//  
//

LEETCODE_BEGIN_RESOLVING(230, KthSmallestElementInABST, Solution);

class Solution {
public:
  int kthSmallest(TreeNode *root, int k) {
    stack<TreeNode *> traverse;
    while (true) {
      while (root != nullptr) {
        traverse.push(root);
        root = root->left;
      }
      root = traverse.top();
      traverse.pop();
      if (--k == 0)
        return root->val;
      root = root->right;
    }
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is |n|.
// * |1 <= k <= n <= 10⁴|
// * |0 <= Node.val <= 10⁴|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [3,1,4,null,2], k = 1
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(230, KthSmallestElementInABST, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({3, 1, 4, null, 2});
  int       k        = 1;
  int       expect   = 1;
  int       actual   = solution->kthSmallest(root, k);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [5,3,6,2,4,null,null,1], k = 3
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(230, KthSmallestElementInABST, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 3, 6, 2, 4, null, null, 1});
  int       k        = 3;
  int       expect   = 3;
  int       actual   = solution->kthSmallest(root, k);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
