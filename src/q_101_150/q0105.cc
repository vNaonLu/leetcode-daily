// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Construct Binary Tree from Preorder and Inorder Traversal
//
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
//
// Question ID: 105
// Difficult  : Medium
// Solve Date : 2021/10/03 12:47

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <map>
#include <unordered_map>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |105. Construct Binary Tree from Preorder and Inorder
// Traversal|:
//
// Given two integer arrays |preorder| and |inorder| where |preorder| is the
// preorder traversal of a binary tree and |inorder| is the inorder traversal of
// the same tree, construct and return the binary tree.  
//

LEETCODE_BEGIN_RESOLVING(105,
                         ConstructBinaryTreeFromPreorderAndInorderTraversal,
                         Solution);

class Solution {
private:
  unordered_map<int, int> memo;
  TreeNode *helper(vector<int> &pre, vector<int> &in, int in_beg, int in_end,
                   int index) {
    if (in_end < in_beg)
      return nullptr;
    if (index >= pre.size())
      return nullptr;
    int i = memo[pre[index]];
    return new TreeNode(pre[index], helper(pre, in, in_beg, i - 1, index + 1),
                        helper(pre, in, i + 1, in_end, index + i - in_beg + 1));
  }

public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    for (int i = 0; i < inorder.size(); ++i)
      memo[inorder[i]] = i;
    return helper(preorder, inorder, 0, inorder.size() - 1, 0);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= preorder.length <= 3000|
// * |inorder.length == preorder.length|
// * |-3000 <= preorder[i], inorder[i] <= 3000|
// * |preorder| and |inorder| consist of unique values.
// * Each value of |inorder| also appears in |preorder|.
// * |preorder| is guaranteed to be the preorder traversal of the tree.
// * |inorder| is guaranteed to be the inorder traversal of the tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// Output: [3,9,20,null,null,15,7]
//

LEETCODE_SOLUTION_UNITTEST(105,
                           ConstructBinaryTreeFromPreorderAndInorderTraversal,
                           example_1) {
  auto        solution = MakeSolution();
  vector<int> preorder = {3, 9, 20, 15, 7};
  vector<int> inorder  = {9, 3, 15, 20, 7};
  TreeNode   *expect   = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  TreeNode   *actual   = solution->buildTree(preorder, inorder);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

// [Example #2]
//  Input: preorder = [-1], inorder = [-1]
// Output: [-1]
//

LEETCODE_SOLUTION_UNITTEST(105,
                           ConstructBinaryTreeFromPreorderAndInorderTraversal,
                           example_2) {
  auto        solution = MakeSolution();
  vector<int> preorder = {-1};
  vector<int> inorder  = {-1};
  TreeNode   *expect   = TreeNode::FromVector({-1});
  TreeNode   *actual   = solution->buildTree(preorder, inorder);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}
