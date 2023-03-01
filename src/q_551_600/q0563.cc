// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Binary Tree Tilt
//
// https://leetcode.com/problems/binary-tree-tilt/
//
// Question ID: 563
// Difficult  : Easy
// Solve Date : 2021/12/08 17:51

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |563. Binary Tree Tilt|:
//
// Given the |root| of a binary tree, return the sum of every tree node's tilt.
// The tilt of a tree node is the absolute difference between the sum of all
// left subtree node values and all right subtree node values. If a node does
// not have a left child, then the sum of the left subtree node values is
// treated as |0|. The rule is similar if the node does not have a right child.
//  
//

LEETCODE_BEGIN_RESOLVING(563, BinaryTreeTilt, Solution);

class Solution {
private:
  int helper(TreeNode *p, int &res) {
    if (nullptr == p)
      return 0;
    int L = helper(p->left, res), R = helper(p->right, res);
    res += abs(L - R);
    return p->val + L + R;
  }

public:
  int findTilt(TreeNode *root) {
    int res = 0;
    helper(root, res);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[0, 10⁴]|.
// * |-1000 <= Node.val <= 1000|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,2,3]
// Output: 1
//
// Tilt of node 2 : |0-0| = 0 (no children)
// Tilt of node 3 : |0-0| = 0 (no children)
// Tilt of node 1 : |2-3| = 1 (left subtree is just left child, so sum is 2;
// right subtree is just right child, so sum is 3) Sum of every tilt : 0 + 0 + 1
// = 1

LEETCODE_SOLUTION_UNITTEST(563, BinaryTreeTilt, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 2, 3});
  int       expect   = 1;
  int       actual   = solution->findTilt(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [4,2,9,3,5,null,7]
// Output: 15
//
// Tilt of node 3 : |0-0| = 0 (no children)
// Tilt of node 5 : |0-0| = 0 (no children)
// Tilt of node 7 : |0-0| = 0 (no children)
// Tilt of node 2 : |3-5| = 2 (left subtree is just left child, so sum is 3;
// right subtree is just right child, so sum is 5) Tilt of node 9 : |0-7| = 7
// (no left child, so sum is 0; right subtree is just right child, so sum is 7)
// Tilt of node 4 : |(3+5+2)-(9+7)| = |10-16| = 6 (left subtree values are 3, 5,
// and 2, which sums to 10; right subtree values are 9 and 7, which sums to 16)
// Sum of every tilt : 0 + 0 + 0 + 2 + 7 + 6 = 15

LEETCODE_SOLUTION_UNITTEST(563, BinaryTreeTilt, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 2, 9, 3, 5, null, 7});
  int       expect   = 15;
  int       actual   = solution->findTilt(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #3]
//  Input: root = [21,7,14,1,1,2,2,3,3]
// Output: 9
//

LEETCODE_SOLUTION_UNITTEST(563, BinaryTreeTilt, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({21, 7, 14, 1, 1, 2, 2, 3, 3});
  int       expect   = 9;
  int       actual   = solution->findTilt(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
