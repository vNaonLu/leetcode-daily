// Copyright 2025 Naon Lu
//
// This file describes the solution of
// Construct Binary Tree from Preorder and Postorder Traversal
//
// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/
//
// Question ID: 889
// Difficult  : Medium
// Solve Date : 2025/02/23 13:25

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |889. Construct Binary Tree from Preorder and Postorder
// Traversal|:
//
// Given two integer arrays, |preorder| and |postorder| where |preorder| is the
// preorder traversal of a binary tree of distinct values and |postorder| is the
// postorder traversal of the same tree, reconstruct and return the binary tree.
// If there exist multiple answers, you can return any of them.
//
//

LEETCODE_BEGIN_RESOLVING(889,
                         ConstructBinaryTreeFromPreorderAndPostorderTraversal,
                         Solution);

class Solution {
public:
  TreeNode *constructFromPrePost(vector<int> &preorder,
                                 vector<int> &postorder) {
    int i = 0;
    int j = 0;
    return make(&i, &j, preorder, postorder);
  }

private:
  TreeNode *make(int *i, int *j, const auto &pre, const auto &post) {
    auto *node = new TreeNode(pre[(*i)++]);
    if (node->val != post[*j]) {
      node->left = make(i, j, pre, post);
    }

    if (node->val != post[*j]) {
      node->right = make(i, j, pre, post);
    }

    ++(*j);
    return node;
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should obey the constraints mentioned in LeetCode:
// * |1 <= preorder.length <= 30|
// * |1 <= preorder[i] <= preorder.length|
// * All the values of |preorder| are unique.
// * |postorder.length == preorder.length|
// * |1 <= postorder[i] <= postorder.length|
// * All the values of |postorder| are unique.
// * It is guaranteed that |preorder| and |postorder| are the preorder traversal
// and postorder traversal of the same binary tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: preorder = [1,2,4,5,3,6,7], postorder = [4,5,2,6,7,3,1]
// Output: [1,2,3,4,5,6,7]
//

LEETCODE_SOLUTION_UNITTEST(889,
                           ConstructBinaryTreeFromPreorderAndPostorderTraversal,
                           example_1) {
  auto        solution  = MakeSolution();
  vector<int> preorder  = {1, 2, 4, 5, 3, 6, 7};
  vector<int> postorder = {4, 5, 2, 6, 7, 3, 1};
  TreeNode   *expect    = TreeNode::FromVector({1, 2, 3, 4, 5, 6, 7});
  TreeNode   *actual    = solution->constructFromPrePost(preorder, postorder);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

// [Example #2]
//  Input: preorder = [1], postorder = [1]
// Output: [1]
//

LEETCODE_SOLUTION_UNITTEST(889,
                           ConstructBinaryTreeFromPreorderAndPostorderTraversal,
                           example_2) {
  auto        solution  = MakeSolution();
  vector<int> preorder  = {1};
  vector<int> postorder = {1};
  TreeNode   *expect    = TreeNode::FromVector({1});
  TreeNode   *actual    = solution->constructFromPrePost(preorder, postorder);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}
