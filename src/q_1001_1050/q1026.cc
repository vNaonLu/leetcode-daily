// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Maximum Difference Between Node and Ancestor
//
// https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/
//
// Question ID: 1026
// Difficult  : Medium
// Solve Date : 2021/12/31 14:34

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |1026. Maximum Difference Between Node and Ancestor|:
//
// Given the |root| of a binary tree, find the maximum value |v| for which there
// exist different nodes |a| and |b| where |v = |a.val - b.val|| and |a| is an
// ancestor of |b|. A node |a| is an ancestor of |b| if either: any child of |a|
// is equal to |b| or any child of |a| is an ancestor of |b|.  
//

LEETCODE_BEGIN_RESOLVING(1026, MaximumDifferenceBetweenNodeAndAncestor,
                         Solution);

class Solution {
private:
  int  res;
  void diff(TreeNode *p, int cmax, int cmin) {
    if (nullptr == p)
      return;
    res  = max({res, abs(cmax - p->val), abs(cmin - p->val)});
    cmax = max(cmax, p->val);
    cmin = min(cmin, p->val);
    diff(p->left, cmax, cmin);
    diff(p->right, cmax, cmin);
  }

public:
  int maxAncestorDiff(TreeNode *root) {
    res = 0;
    diff(root, root->val, root->val);
    return res;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[2, 5000]|.
// * |0 <= Node.val <= 10⁵|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
// Output: 7
//
// We have various ancestor-node differences, some of which are given below :
// |8 - 3| = 5
// |3 - 7| = 4
// |8 - 1| = 7
// |10 - 13| = 3
// Among all possible differences, the maximum value of 7 is obtained by |8 - 1|
// = 7.

LEETCODE_SOLUTION_UNITTEST(1026, MaximumDifferenceBetweenNodeAndAncestor,
                           example_1) {
  auto      solution = MakeSolution();
  TreeNode *root =
      TreeNode::FromVector({8, 3, 10, 1, 6, null, 14, null, null, 4, 7, 13});
  int expect = 7;
  int actual = solution->maxAncestorDiff(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}

// [Example #2]
//  Input: root = [1,null,2,null,0,3]
// Output: 3
//

LEETCODE_SOLUTION_UNITTEST(1026, MaximumDifferenceBetweenNodeAndAncestor,
                           example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({1, null, 2, null, 0, 3});
  int       expect   = 3;
  int       actual   = solution->maxAncestorDiff(root);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root);
}
