// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Diameter of Binary Tree
//
// https://leetcode.com/problems/diameter-of-binary-tree/
//
// Question ID: 543
// Difficult  : Easy
// Solve Date : 2021/10/11 14:53

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |543. Diameter of Binary Tree|:
//
// Given the |root| of a binary tree, return the length of the diameter of the
// tree. The diameter of a binary tree is the length of the longest path between
// any two nodes in a tree. This path may or may not pass through the |root|.
// The length of a path between two nodes is represented by the number of edges
// between them.  
//

LEETCODE_BEGIN_RESOLVING(543, DiameterOfBinaryTree, Solution);

class Solution {
private:
  int helper(TreeNode *p, int &r) {
    if (p == nullptr)
      return -1;
    int left  = helper(p->left, r);
    int right = helper(p->right, r);
    r         = max(r, left + right + 2);
    return max(left, right) + 1;
  }

public:
  int diameterOfBinaryTree(TreeNode *root) {
    int res = 0;
    helper(root, res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 10⁴]|.
// * |-100 <= Node.val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3,4,5]
// Output: 3
//
// 3 is the length of the path [4,2,1,3] or [5,2,1,3].

LEETCODE_SOLUTION_UNITTEST(543, DiameterOfBinaryTree, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3, 4, 5});
  int       expect   = 3;
  int       actual   = solution->diameterOfBinaryTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,2]
// Output: 1
//

LEETCODE_SOLUTION_UNITTEST(543, DiameterOfBinaryTree, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2});
  int       expect   = 1;
  int       actual   = solution->diameterOfBinaryTree(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
