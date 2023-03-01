// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Sum of Root To Leaf Binary Numbers
//
// https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/
//
// Question ID: 1022
// Difficult  : Easy
// Solve Date : 2022/01/11 18:04

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1022. Sum of Root To Leaf Binary Numbers|:
//
// You are given the |root| of a binary tree where each node has a value |0| or
// |1|. Each root-to-leaf path represents a binary number starting with the most
// significant bit.
//
//  • For example, if the path is |0 -> 1 -> 1 -> 0 -> 1|, then this could
//  represent |01101| in binary, which is |13|.
// For all leaves in the tree, consider the numbers represented by the path from
// the root to that leaf. Return the sum of these numbers. The test cases are
// generated so that the answer fits in a 32-bits integer.  
//

LEETCODE_BEGIN_RESOLVING(1022, SumOfRootToLeafBinaryNumbers, Solution);

class Solution {
private:
  int binaryNumber(TreeNode *p, int current = 0) {
    if (nullptr == p)
      return current;
    current <<= 1;
    current += p->val;
    if (nullptr == p->left)
      return binaryNumber(p->right, current);
    else if (nullptr == p->right)
      return binaryNumber(p->left, current);
    else
      return binaryNumber(p->left, current) + binaryNumber(p->right, current);
  }

public:
  int sumRootToLeaf(TreeNode *root) { return binaryNumber(root); }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 1000]|.
// * |Node.val| is |0| or |1|.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [1,0,1,0,1,0,1]
// Output: 22
//
// (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22

LEETCODE_SOLUTION_UNITTEST(1022, SumOfRootToLeafBinaryNumbers, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, 0, 1, 0, 1, 0, 1});
  int       expect   = 22;
  int       actual   = solution->sumRootToLeaf(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [0]
// Output: 0
//

LEETCODE_SOLUTION_UNITTEST(1022, SumOfRootToLeafBinaryNumbers, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({0});
  int       expect   = 0;
  int       actual   = solution->sumRootToLeaf(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
