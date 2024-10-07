// Copyright 2024 Naon Lu
//
// This file describes the solution of
// Maximum Binary Tree II
//
// https://leetcode.com/problems/maximum-binary-tree-ii/
//
// Question ID: 998
// Difficult  : Medium
// Solve Date : 2024/10/07 21:37

#include "leetcode/tree_node.h"
#include <iosfwd>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |998. Maximum Binary Tree II|:
//
// A maximum tree is a tree where every node has a value greater than any other
// value in its subtree. You are given the |root| of a maximum binary tree and
// an integer |val|. Just as in the [previous problem], the given tree was
// constructed from a list |a| ( |root = Construct(a)|) recursively with the
// following |Construct(a)| routine:
//
//  • If |a| is empty, return |null|.
//
//  • Otherwise, let |a[i]| be the largest element of |a|. Create a |root| node
//  with the value |a[i]|.
//
//  • The left child of |root| will be |Construct([a[0], a[1], ..., a[i - 1]])|.
//
//  • The right child of |root| will be |Construct([a[i + 1], a[i + 2], ...,
//  a[a.length - 1]])|.
//
//  • Return |root|.
// Note that we were not given |a| directly, only a root node |root =
// Construct(a)|. Suppose |b| is a copy of |a| with the value |val| appended to
// it. It is guaranteed that |b| has unique values. Return |Construct(b)|.
//
//

LEETCODE_BEGIN_RESOLVING(998, MaximumBinaryTreeII, Solution);

class Solution {
public:
  TreeNode *insertIntoMaxTree(TreeNode *root, int val) {
    if (!root) {
      return new TreeNode(val);
    }
    if (root->val < val) {
      auto *p = new TreeNode(val);
      p->left = root;
      return p;
    }

    root->right = insertIntoMaxTree(root->right, val);
    return root;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * The number of nodes in the tree is in the range |[1, 100]|.
// * |1 <= Node.val <= 100|
// * All the values of the tree are unique.
// * |1 <= val <= 100|
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: root = [4,1,3,null,null,2], val = 5
// Output: [5,4,null,1,3,null,null,2]
//

LEETCODE_SOLUTION_UNITTEST(998, MaximumBinaryTreeII, example_1) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({4, 1, 3, null, null, 2});
  int       val      = 5;
  TreeNode *expect   = TreeNode::FromVector({5, 4, null, 1, 3, null, null, 2});
  TreeNode *actual   = solution->insertIntoMaxTree(root, val);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #2]
//  Input: root = [5,2,4,null,1], val = 3
// Output: [5,2,4,null,1,null,3]
//

LEETCODE_SOLUTION_UNITTEST(998, MaximumBinaryTreeII, example_2) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 2, 4, null, 1});
  int       val      = 3;
  TreeNode *expect   = TreeNode::FromVector({5, 2, 4, null, 1, null, 3});
  TreeNode *actual   = solution->insertIntoMaxTree(root, val);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}

// [Example #3]
//  Input: root = [5,2,3,null,1], val = 4
// Output: [5,2,4,null,1,3]
//

LEETCODE_SOLUTION_UNITTEST(998, MaximumBinaryTreeII, example_3) {
  auto      solution = MakeSolution();
  TreeNode *root     = TreeNode::FromVector({5, 2, 3, null, 1});
  int       val      = 4;
  TreeNode *expect   = TreeNode::FromVector({5, 2, 4, null, 1, 3});
  TreeNode *actual   = solution->insertIntoMaxTree(root, val);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(root, expect, actual);
}
