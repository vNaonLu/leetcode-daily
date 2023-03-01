// Copyright 2023 Naon Lu
//
// This file describes the solution of
// Construct Binary Tree from Inorder and Postorder Traversal
//
// https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
//
// Question ID: 106
// Difficult  : Medium
// Solve Date : 2021/11/21 13:23

#include "leetcode/tree_node.h"
#include <iosfwd>
#include <vector>

// -- This header must be included after others --
#include "leetcode/testing/solution_test_helper.h"

using namespace std;
using namespace lcd;

// Description of |106. Construct Binary Tree from Inorder and Postorder
// Traversal|:
//
// Given two integer arrays |inorder| and |postorder| where |inorder| is the
// inorder traversal of a binary tree and |postorder| is the postorder traversal
// of the same tree, construct and return the binary tree.  
//

LEETCODE_BEGIN_RESOLVING(106,
                         ConstructBinaryTreeFromInorderAndPostorderTraversal,
                         Solution);

class Solution {
private:
  vector<int> inord, postord;
  TreeNode   *helper(int l, int r, int &cur) {
    if (l > r)
      return nullptr;
    int  i = find(inord.begin(), inord.end(), postord[cur--]) - inord.begin();
    auto right = helper(i + 1, r, cur);
    auto left  = helper(l, i - 1, cur);
    return new TreeNode(inord[i], left, right);
  }

public:
  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    inord   = inorder;
    postord = postorder;
    int cur = postorder.size() - 1;
    return helper(0, postorder.size() - 1, cur);
  }
};

LEETCODE_END_RESOLVING(Solution);

///////////////////////////////////////////////////////////////////////////////
// The following is test data for unit test.
// Note that inputs should be obey the constraints mentioned in LeetCode:
// * |1 <= inorder.length <= 3000|
// * |postorder.length == inorder.length|
// * |-3000 <= inorder[i], postorder[i] <= 3000|
// * |inorder| and |postorder| consist of unique values.
// * Each value of |postorder| also appears in |inorder|.
// * |inorder| is guaranteed to be the inorder traversal of the tree.
// * |postorder| is guaranteed to be the postorder traversal of the tree.
///////////////////////////////////////////////////////////////////////////////

// [Example #1]
//  Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
// Output: [3,9,20,null,null,15,7]
//

LEETCODE_SOLUTION_UNITTEST(106,
                           ConstructBinaryTreeFromInorderAndPostorderTraversal,
                           example_1) {
  auto        solution  = MakeSolution();
  vector<int> inorder   = {9, 3, 15, 20, 7};
  vector<int> postorder = {9, 15, 7, 20, 3};
  TreeNode   *expect    = TreeNode::FromVector({3, 9, 20, null, null, 15, 7});
  TreeNode   *actual    = solution->buildTree(inorder, postorder);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}

// [Example #2]
//  Input: inorder = [-1], postorder = [-1]
// Output: [-1]
//

LEETCODE_SOLUTION_UNITTEST(106,
                           ConstructBinaryTreeFromInorderAndPostorderTraversal,
                           example_2) {
  auto        solution  = MakeSolution();
  vector<int> inorder   = {-1};
  vector<int> postorder = {-1};
  TreeNode   *expect    = TreeNode::FromVector({-1});
  TreeNode   *actual    = solution->buildTree(inorder, postorder);
  LCD_EXPECT_EQ(expect, actual);
  TreeNode::Release(expect, actual);
}
